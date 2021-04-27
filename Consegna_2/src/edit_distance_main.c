#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

int main(int argc, char const *argv[]){

    int i, j;
    char string1[] = "pioppo";
    char string2[] = "pioppo";
   
    int length1 = strlen(string1);
    int length2 = strlen(string2);
    
    //necessaria migliore soluzione
    recursive_calls_table = (int **)malloc(length1 * sizeof(int *));  
    for (i = 0; i < length1; i++){
        recursive_calls_table[i] = malloc(MAX_WORD_LENGTH * sizeof(int));
        for (j = 0; j < length2; j++){
            recursive_calls_table[i][j] = -1;
        }
    }

    int res = edit_distance_dynamic(string1, string2, length1, length2, recursive_calls_table);
    //int res = edit_distance(string1, string2);
    printf("Risultato: %d\n", res);
    free(recursive_calls_table);

    return EXIT_SUCCESS;
}

void init(char *correctme, char *dictionary){
    int **recursive_calls_table;
    recursive_calls_table = (int **)malloc(strlen(MAX_WORD_LENGTH) * sizeof(int *));  
    for (int i = 0; i < strlen(MAX_WORD_LENGTH); i++){
        recursive_calls_table[i] = malloc(MAX_WORD_LENGTH * sizeof(int));
    }

    char = parola;
    init_correction(parola, dictionary);






    free(recursive_calls_table);
}
int correction(char *str, char *dictionary, char **recursive_calls_table){
    int minimo = INT_MAX, distanza;
    char correzione[MAX_WORD_LENGTH];
    char correzione_minima[MAX_WORD_LENGTH];
    char buffer[BUFFER_SIZE];
    FILE *dct;

    dct = fopen(dictionary, "r");
    if (dct == NULL) {
        fprintf(stderr, "main: unable to open the dictionary file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < strlen(str); i++){
        for (int j = 0; j < strlen(correzione); j++){
            recursive_calls_table[i][j] = -1;
        }
    }

    //leggo riga per riga e carico nella stringa buffer
    while(fgets(buffer, BUFFER_SIZE, dct) != NULL){

        //ora devo spezzare la riga in token stringa, usando i delimitatori
        //le stringhe verranno controllate e corrette utilizzando la distanza, i delimitatori verranno semplicemente trascritti

        //valutare inserimento di array correzione_minima per mantenere le stringhe con edit_distance = minimo e scegliere criterio di valutazione aggiuntivo



        while (buffer != NULL){ //condizione da controllare

            //qui estraggo un token per volta fino al delimitatore
            //da valutare come gestire questa parte. DIFFICILE! 
            //Possibili soluzioni: usare isalpha con fgetc al posto di fgets fino a un non delimitatore, caricare in stringa e farne edit_distance. Copiare invece il singolo carattere del delimitatore
            distanza = edit_distance_dynamic(str, correzione, strlen(str), strlen(correzione), recursive_calls_table);
            if (distanza < minimo){
                strcpy(correzione_minima, correzione);
            }



            //scrivo qui la stringa o il delimitatore




        }
    }
    fclose(dct);
    //scrittore(correzione_minima);   //meglio includerlo nel while del file dct
}