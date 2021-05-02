#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORD_LENGTH 100
#define MAX_WORDS_NUMBER 1000 //da vedere


int min(int a, int b, int c) {
	if(a <= b && a <= c) return a;
	if(b <= c){
        return b;
    } else {
        return c;
    }
}

//parte dall'inizio della stringa, per comodità di lettura
int edit_distance(char *string1, char *string2){
    int no_op;
    if (strlen(string1) == 0) return strlen(string2);
    if (strlen(string2) == 0) return strlen(string1);

    if (string1[0] == string2[0]){
        no_op = edit_distance(string1+1, string2+1);
    } else {
        no_op = INT_MAX;
    }
    return min(1 + edit_distance(string1, string2+1), 1 + edit_distance(string1+1, string2), no_op);
}

//parte dal fondo della stringa attraverso le lenght, per implementare la tabella in cui salvare i risultati. Similarità all'approccio iterativo
int edit_distance_dynamic(char *string1, char *string2, int length1, int length2, int **recursive_calls_table){
    int no_op;
    if (length1 == 0) return length2;
    if (length2 == 0) return length1;

    if (recursive_calls_table[length1 - 1][length2 - 1] != -1) return recursive_calls_table[length1 - 1][length2 - 1];

    if (string1[length1 - 1] == string2[length2 - 1]) {
        no_op = recursive_calls_table[length1 - 1][length2 - 1] = edit_distance_dynamic(string1, string2, length1 - 1, length2 - 1, recursive_calls_table);
    } else {
        no_op = INT_MAX;
    }

    return recursive_calls_table[length1 - 1][length2 - 1] = min(1 + edit_distance_dynamic(string1, string2, length1, length2 - 1, recursive_calls_table), 1 + edit_distance_dynamic(string1, string2, length1 - 1, length2, recursive_calls_table), no_op);
}

int best_correction_index(char correzione_minima[MAX_WORDS_NUMBER][MAX_WORD_LENGTH], char *str, int correzione_minima_index){
    for (int i = 0; i < correzione_minima_index; i++){
        if (strlen(str) == strlen(correzione_minima[i])){
            return i;
        }
    }
    return correzione_minima_index - 1;
}

void correction(const char *correctme, const char *dictionary, int **recursive_calls_table){
    int minimo = INT_MAX, distanza, searching = 1, uppercase = 1;
    char str[MAX_WORD_LENGTH];
    char correzione[MAX_WORD_LENGTH];
    char correzione_minima[MAX_WORDS_NUMBER][MAX_WORD_LENGTH];
    char best_correction[MAX_WORD_LENGTH];
    int correzione_minima_index = 0;
    int ch, newstr;
    size_t str_size;
    FILE *dct, *out, *tobechecked;

    dct = fopen(dictionary, "r");
    if (dct == NULL) {
        fprintf(stderr, "main: unable to open the dictionary file");
        exit(EXIT_FAILURE);
    }
    out = fopen("corrected.txt", "w");
    if (out == NULL) {
        fprintf(stderr, "main: unable to create the corrected output file");
        exit(EXIT_FAILURE);
    }
    tobechecked = fopen(correctme, "r");
    if (out == NULL) {
        fprintf(stderr, "main: unable to open the file that has to be checked");
        exit(EXIT_FAILURE);
    }
    while((ch = fgetc(tobechecked)) != EOF){
        //le stringhe verranno controllate e corrette utilizzando edit_distance_dynamic, i delimitatori verranno semplicemente trascritti
        //carico quindi tutti i caratteri alfabetici sulla stringa str
        if (isalpha(ch)){
            str[str_size] = (char)ch;
            str_size++;
            newstr = 1; //posibile sostituirlo con strlen per non scrivere ogni volta memoria. Controllare
        } else {
            //uso un controllo su flag per assicurarmi che la stringa non sia vuota
            if (newstr == 1){
                //allora ho una nuova stringa da valutare, oltre che della punteggiatura
                //devo leggere il file dizionario e ciclare per ogni parola presente in esso
                str[0] = tolower(str[0]);
                printf("Analizzo %s\n", str);
                while(fscanf(dct, "%s", correzione) != EOF && searching){
                    //setto la matrice a -1 per corretto funzionamento
                    for (int i = 0; i < strlen(str); i++){
                        for (int j = 0; j < MAX_WORD_LENGTH; j++){
                            recursive_calls_table[i][j] = -1;
                        }
                    }

                    distanza = edit_distance_dynamic(str, correzione, strlen(str), strlen(correzione), recursive_calls_table);
                    if (distanza < minimo){
                        if (distanza == 0){
                            searching = 0;
                        }
                        //reset dell'arry di stringhe
                        bzero(correzione_minima, sizeof(correzione_minima));
                        correzione_minima_index = 0;
                        
                        strcpy(correzione_minima[correzione_minima_index], correzione);
                        minimo = distanza;
                        correzione_minima_index++;
                    } else if (distanza == minimo){
                        strcpy(correzione_minima[correzione_minima_index], correzione);
                        minimo = distanza;
                        correzione_minima_index++;
                    }
                }
                strcpy(best_correction, correzione_minima[best_correction_index(correzione_minima, str, correzione_minima_index)]);
                if (uppercase == 1){
                    best_correction[0] = toupper(best_correction[0]);
                    uppercase = 0;
                }

                fputs(best_correction, out);

                minimo = INT_MAX;
                newstr = 0;
                memset(str,0,strlen(str));
                str_size = 0;
                searching = 1;
                bzero(correzione_minima, sizeof(correzione_minima));

                fseek(dct,0,SEEK_SET);
            }
            fputc(ch, out);
            if (ch == '.'){
                uppercase = 1;
            }
        }
    }
    fclose(dct);
    fclose(out);
    fclose(tobechecked);
}

void init(const char *correctme, const char *dictionary){
    clock_t start_t, end_t;
    int **recursive_calls_table;
    recursive_calls_table = (int **)malloc(MAX_WORD_LENGTH * sizeof(int*));  
    for (int i = 0; i < MAX_WORD_LENGTH; i++){
        recursive_calls_table[i] = malloc(MAX_WORD_LENGTH * sizeof(int));
    }
    
  
    start_t = clock();
    correction(correctme, dictionary, recursive_calls_table);
    end_t = clock();
    printf("Correction took: ~%f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

    free(recursive_calls_table);
}

int main(int argc, char const *argv[]){
    if (argc < 3){
        printf("Errore nel passaggio dei parametri a linea di comando\n");
        printf("Istruzioni per l'utilizzo: ");

        exit(EXIT_FAILURE);
    }

    //  Da fare:
    //- array dinamico per dizionario? Grossi valori, implementazione meh
    //- valutare altre strutture dati, giusto per volersi male. Limitato però a edit_distance_dynamic
    //- istruzioni per l'input da terminale
    //- makefile
    //- aggiustare directory passate per argomento
    //- unit - test

    init(argv[1], argv[2]);
}
