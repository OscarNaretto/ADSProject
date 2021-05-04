#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include "edit_distance_lib.h"
#include "dictionary.h"


#define MAX_WORD_LENGTH 30
#define MAX_WORDS_NUMBER 100

void correction(const char *correctme, Dictionary *dictionary_array, int **recursive_calls_table){
    int minimo = INT_MAX, distanza, uppercase = 1;
    char *str;
    char *correzione;
    char correzione_minima[MAX_WORDS_NUMBER][MAX_WORD_LENGTH];
    char *best_correction;
    int correzione_minima_index = 0;
    int ch;
    unsigned long dct_index;
    size_t str_size;
    FILE *out, *tobechecked, *word_corrections;

    correzione = malloc((MAX_WORD_LENGTH) * sizeof(char));
    best_correction = malloc((MAX_WORD_LENGTH) * sizeof(char));
    str = malloc((MAX_WORD_LENGTH) * sizeof(char));

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

    word_corrections = fopen("wordcorrections.txt", "w");
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
        } else {
            //uso un controllo su flag per assicurarmi che la stringa non sia vuota
            if (strlen(str) != 0){
                //allora ho una nuova stringa da valutare, oltre che della punteggiatura
                //devo leggere il file dizionario e ciclare per ogni parola presente in esso
                str[0] = (char)tolower(str[0]);
                printf("Analizzo %s\n", str);

                if (dictionary_is_present(dictionary_array, str) == -1){
                    //setto la matrice a -1 per corretto funzionamento
                    for (int i = 0; i < (int)strlen(str); i++){
                        for (int j = 0; j < MAX_WORD_LENGTH; j++){
                            recursive_calls_table[i][j] = -1;
                        }
                    }
                    for (dct_index = 0; dct_index < dictionary_array_size(dictionary_array); dct_index++){
                        strcpy(correzione, dictionary_get_elem(dictionary_array, dct_index));
                        distanza = edit_distance_dynamic(str, correzione, (int)strlen(str), (int)strlen(correzione), recursive_calls_table);
                        
                        //non calcola più correttamente edit distance

                        if (distanza < minimo){                      
                            //reset dell'array di stringhe
                            bzero(correzione_minima, sizeof(correzione_minima));
                            correzione_minima_index = 0; 
                        }
                        strcpy(correzione_minima[correzione_minima_index], correzione);
                        minimo = distanza;
                        correzione_minima_index++;
                    }
                    
                    strcpy(best_correction, correzione_minima[best_correction_index(correzione_minima, str, correzione_minima_index)]);
                    fprintf(word_corrections, "%s -> ", str);
                    for (int i = 0; i < correzione_minima_index; i++){
                        fprintf(word_corrections, "%s ", correzione_minima[i]);
                    }
                    fprintf(word_corrections, "\n");
                            
                } else {
                    strcpy(best_correction, str);
                }
                if (uppercase == 1){
                    best_correction[0] = (char)toupper(best_correction[0]);
                    uppercase = 0;
                }
                fputs(best_correction, out);
                minimo = INT_MAX;
                bzero(str, strlen(str));
                str_size = 0;
                bzero(correzione_minima, sizeof(correzione_minima)); 
            }
            fputc(ch, out);
            if (ch == '.'){
                uppercase = 1;
            }
        }
    }
    fclose(out);
    fclose(tobechecked);
    fclose(word_corrections);
}

void init(const char *correctme, const char *dictionary){
    clock_t start_t, end_t;
    int **recursive_calls_table;
    recursive_calls_table = (int **)malloc(MAX_WORD_LENGTH * sizeof(int*));  
    for (int i = 0; i < MAX_WORD_LENGTH; i++){
        recursive_calls_table[i] = malloc(MAX_WORD_LENGTH * sizeof(int));
    }

    Dictionary *dictionary_array = dictionary_create();
    load_dictionary(dictionary, dictionary_array);

    start_t = clock();
    correction(correctme, dictionary_array, recursive_calls_table);
    end_t = clock();
    printf("Correction took: ~%f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

    for (int i = 0; i < MAX_WORD_LENGTH; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);

    
    dictionary_array_free(dictionary_array);
}

int main(int argc, char const *argv[]){
    if (argc < 3){
        printf("Errore nel passaggio dei parametri a linea di comando\n");
        printf("Istruzioni per l'utilizzo, seguite l'ordine di caricamento :\n");
        printf("1- Caricare testo da valutare e correggere.\n2- Caricare il dizionario.\n");

        exit(EXIT_FAILURE);
    }

    //  Da fare:
    //- valutare altre strutture dati, giusto per volersi male. Limitato però a edit_distance_dynamic
    //- aggiustare directory passate per argomento tramite make. segfault11 da vedere
    //- unit - test

    init(argv[1], argv[2]);
}
