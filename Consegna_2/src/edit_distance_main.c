#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include "edit_distance_lib.h"
#include "dictionary.h"

#define MAX_WORD_LENGTH 20
#define MAX_WORDS_NUMBER 30
#define MAX_CORRECTIONS_NUMBER 5

//Print MAX_CORRECTIONS_NUMBER word corrections per word, in a fixed output file (we chose fixed directory in order not to ask another argument from cli)
void word_corrections_print(char str[MAX_WORD_LENGTH], char minimum_corrections_array[MAX_WORDS_NUMBER][MAX_WORD_LENGTH], int minimum_corrections_size){
    FILE *word_corrections;
    word_corrections = fopen("wordcorrections.txt", "a");    
    if (word_corrections == NULL) {
        fprintf(stderr, "main: unable to open the file that has to be checked");
        exit(EXIT_FAILURE);
    }

    fprintf(word_corrections, "%s -> ", str);
    for (int i = 0; i < MAX_CORRECTIONS_NUMBER && i < minimum_corrections_size; i++){
        fprintf(word_corrections, "%s ", minimum_corrections_array[i]);
    }
    fprintf(word_corrections, "\n");
    fclose(word_corrections);
}

void correction(const char *correctme, Dictionary *dictionary_array, int **recursive_calls_table){
    int min_distance = INT_MAX, distance, uppercase = 1, minimum_corrections_size = 0;
    char str[MAX_WORD_LENGTH], correzione[MAX_WORD_LENGTH], minimum_corrections_array[MAX_WORDS_NUMBER][MAX_WORD_LENGTH], best_correction[MAX_WORD_LENGTH], ch;
    unsigned long dct_index;
    FILE *out, *tobechecked;
    ch = '\0';
    str[0] = '\0'; 

    out = fopen("corrected.txt", "w");
    if (out == NULL) {
        fprintf(stderr, "main: unable to create the corrected output file");
        exit(EXIT_FAILURE);
    }
    tobechecked = fopen(correctme, "r");
    if (tobechecked == NULL) {
        fprintf(stderr, "main: unable to open the file that has to be checked");
        exit(EXIT_FAILURE);
    }

    //iterating the file char by char
    while((ch = (char)fgetc(tobechecked)) != EOF){
        //strings will be checked and corrected using edit_distance_dynamic, delimiters will be simply transcribed
        //str is used as a char accumulator until we find a delimiter in char
        if (isalpha(ch)){
            strncat(str, &ch, 1);
        } else {
            //strlen(str) check is necessary in order to avoid duplicated str output after more than one delimiter
            if (strlen(str) != 0){
                str[0] = (char)tolower(str[0]);
                if (!dictionary_is_present(dictionary_array, str)){
                    //for each str, we iterate the whole dictionary, after checking if str is a mistake
                    for (dct_index = 0; dct_index < dictionary_array_size(dictionary_array); dct_index++){
                        //reset of recursive_calls_table used for memoization
                        for (int i = 0; i < (int)strlen(str); i++){
                            for (int j = 0; j < MAX_WORD_LENGTH; j++){
                                recursive_calls_table[i][j] = -1;
                            }
                        }
                        strcpy(correzione, dictionary_get_elem(dictionary_array, dct_index));
                        distance = edit_distance_dynamic(str, correzione, (int)strlen(str), (int)strlen(correzione), recursive_calls_table);

                        //if min_distance is the same as before, we add the new word to the array
                        //if min_distance changed, we reset the array
                        if (distance < min_distance){                      
                            bzero(minimum_corrections_array, sizeof(minimum_corrections_array));
                            minimum_corrections_size = 0; 
                            min_distance = distance;

                            strcpy(minimum_corrections_array[minimum_corrections_size], correzione);
                            minimum_corrections_size++;
                        } else if (distance == min_distance){
                            strcpy(minimum_corrections_array[minimum_corrections_size], correzione);
                            minimum_corrections_size++;
                        }
                    }
                    //copying the best correction from all the words with equal edit distance
                    strcpy(best_correction, minimum_corrections_array[best_correction_index(minimum_corrections_array, str, minimum_corrections_size)]);
                    word_corrections_print(str, minimum_corrections_array, minimum_corrections_size);
                } else {
                    strcpy(best_correction, str);
                }
                //handle of uppercase
                if (uppercase == 1){
                    best_correction[0] = (char)toupper(best_correction[0]);
                    uppercase = 0;
                }
                //reset of the used variables
                fputs(best_correction, out);
                min_distance = INT_MAX;
                bzero(str, strlen(str));
                bzero(minimum_corrections_array, sizeof(minimum_corrections_array)); 
            }
            fputc(ch, out);
            if (ch == '.'){
                uppercase = 1;
            }
        }
    }
    fclose(out);
    fclose(tobechecked);
}

void init(const char *correctme, const char *dictionary){
    clock_t init_t, start_t, end_t;
    int **recursive_calls_table;
    FILE *word_corrections;
    //recursive_calls_table is used for memoization in correction()
    recursive_calls_table = (int **)malloc(MAX_WORD_LENGTH * sizeof(int*));  
    for (int i = 0; i < MAX_WORD_LENGTH; i++){
        recursive_calls_table[i] = malloc(MAX_WORD_LENGTH * sizeof(int));
    }

    init_t = start_t = clock();
    Dictionary *dictionary_array = dictionary_create();
    load_dictionary(dictionary, dictionary_array);
    end_t = clock();
    printf("Dictionary loaded correctly, took: ~%f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

    //cleaning wordcorrections file from last execution, if present
    word_corrections = fopen("wordcorrections.txt", "w");
    fclose(word_corrections);   

    start_t = clock();
    correction(correctme, dictionary_array, recursive_calls_table);
    end_t = clock();
    printf("Correction written correctly, took: ~%f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    
    start_t = clock();
    for (int i = 0; i < MAX_WORD_LENGTH; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
    dictionary_array_free(dictionary_array);
    end_t = clock();
    printf("Memory freed correctly, took: ~%f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

    printf("Whole execution took: ~%f sec\n\n", (double)(end_t - init_t) / CLOCKS_PER_SEC);
    printf("corrected.txt contains corrected input, wordcorrections.txt contains %d corrected words for each input mistake, within minimun edit_distance\n", MAX_CORRECTIONS_NUMBER);

}

int main(int argc, char const *argv[]){
    if (argc < 3){
        printf("Errore nel passaggio dei parametri a linea di comando\n");
        printf("Istruzioni per l'utilizzo, seguire l'ordine di caricamento :\n");
        printf("1- Caricare testo da valutare e correggere.\n2- Caricare il dizionario.\n Esempio: ./main correctme.txt dictionary.txt \n");

        exit(EXIT_FAILURE);
    }

    init(argv[1], argv[2]);
}
