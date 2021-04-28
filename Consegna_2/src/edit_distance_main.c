#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define BUFFER_SIZE 1024



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

void correction(const char *correctme, const char *dictionary, int **recursive_calls_table){
    int minimo = INT_MAX, distanza;
    char str[MAX_WORD_LENGTH];
    char correzione[MAX_WORD_LENGTH];
    char correzione_minima[MAX_WORD_LENGTH];
    char buffer[BUFFER_SIZE];
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
    //leggo riga per riga e carico nella stringa buffer
    while((ch = fgetc(tobechecked)) != EOF){
        //le stringhe verranno controllate e corrette utilizzando la distanza, i delimitatori verranno semplicemente trascritti

        //valutare inserimento di array correzione_minima per mantenere le stringhe con edit_distance = minimo e scegliere criterio di valutazione aggiuntivo
        
        //carico tutti i caratteri sulla stringa str
        if (isalpha(ch)){
            str[str_size] = (char)ch;
            str_size++;
            newstr = 1;
        } else {
            //a questo punto ho la stringa salvata in str e punteggiatura o spazio in ch.
            //uso un controllo su flag per assicurarmi che la stringa non sia vuota

            if (newstr == 1){
                //allora ho una nuova stringa da valutare, oltre che della punteggiatura
                //devo leggere il file dizionario e ciclare per ogni parola presente in esso

                while(fscanf(dct, "%s", correzione) != EOF){
                    //setto la matrice a -1 per corretto funzionamento
                    for (int i=0; i<strlen(str);i++){
                        for (int j=0;j<MAX_WORD_LENGTH; j++){
                            recursive_calls_table[i][j] = -1;
                        }
                    }

                    distanza = edit_distance_dynamic(str, correzione, strlen(str), strlen(correzione), recursive_calls_table);
                    
                    if (distanza <= minimo){
                        strcpy(correzione_minima, correzione);
                        minimo = distanza;
                    }
                }
                
                fputs(correzione_minima, out);

                minimo = INT_MAX;
                newstr = 0;
                memset(str,0,strlen(str));
                str_size = 0;

                fseek(dct,0,SEEK_SET);
            }
            fputc(ch, out);
        }
    }
    fclose(dct);
    fclose(out);
    fclose(tobechecked);
}

void init(const char *correctme, const char *dictionary){
    int **recursive_calls_table;
    recursive_calls_table = (int **)malloc(MAX_WORD_LENGTH * sizeof(int*));  
    for (int i = 0; i < MAX_WORD_LENGTH; i++){
        recursive_calls_table[i] = malloc(MAX_WORD_LENGTH * sizeof(int));
    }
    
    //measure time here
    correction(correctme, dictionary, recursive_calls_table);

    free(recursive_calls_table);
}

int main(int argc, char const *argv[]){
    if (argc < 3){
        fprintf(stderr, "Errore nel passaggio dei parametri a linea di comando");
        exit(EXIT_FAILURE);
    }


    //Da fare:
    //- correzione del comportamento in prossimità delle maiuscole. Usare flag per start/dopo punto oppure cercare funzione
    //- controllo tempo esecuzione
    //- array di parole con lunghezza minima invece che singola parola
    //- criterio di scelta da array. possibile idea (non perfetta): lunghezza
    //- valutare altre strutture dati, giusto per volersi male. Limitato però a edit_distance_dynamic
    //- istruzioni per l'input da terminale
    //- makefile
    //- unit - test


    init(argv[1], argv[2]);

    return EXIT_SUCCESS;
}