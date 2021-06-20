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
#define BUFFER_SIZE 1024


//Print MAX_CORRECTIONS_NUMBER word corrections per word, in a fixed output file (we chose fixed directory in order not to ask another argument from cli)
void word_corrections_print(char *str, char minimum_corrections_array[MAX_WORDS_NUMBER][MAX_WORD_LENGTH], int minimum_corrections_size){
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

void correction(const char *correctme, Dictionary *dictionary_array){
    int min_distance = INT_MAX, distance, minimum_corrections_size = 0;
    char buffer[BUFFER_SIZE];
    char correzione[MAX_WORD_LENGTH], minimum_corrections_array[MAX_WORDS_NUMBER][MAX_WORD_LENGTH];
    unsigned long dct_index;
    FILE *tobechecked;

    

    tobechecked = fopen(correctme, "r");
    if (tobechecked == NULL) {
        fprintf(stderr, "main: unable to open the file that has to be checked");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, BUFFER_SIZE, tobechecked) != NULL) {
        char *str = strtok(buffer, ",.!? ");
        while (str != NULL){
            printf("%s\n", str);
            if (!dictionary_is_present(dictionary_array, str)){
                for (dct_index = 0; dct_index < dictionary_array_size(dictionary_array); dct_index++){
                    strcpy(correzione, dictionary_get_elem(dictionary_array, dct_index));
                    distance = edit_distance_dynamic_wrapper(str, correzione);
                    if (distance <= min_distance){   
                        if (distance < min_distance){
                            bzero(minimum_corrections_array, sizeof(minimum_corrections_array));
                            minimum_corrections_size = 0; 
                            min_distance = distance;
                        }     
                        strcpy(minimum_corrections_array[minimum_corrections_size], correzione);
                        minimum_corrections_size++;
                    }
                }
                word_corrections_print(str, minimum_corrections_array, minimum_corrections_size);
            }
            min_distance = INT_MAX;
            bzero(minimum_corrections_array, sizeof(minimum_corrections_array));
            str = strtok(NULL, ",.!? ");
        }
    }








    /*while((ch = (char)fgetc(tobechecked)) != EOF){
        if (isalpha(ch)){
            strncat(str, &ch, 1);
        } else {
            if (strlen(str) != 0){
                str[0] = (char)tolower(str[0]);
                if (!dictionary_is_present(dictionary_array, str)){
                    for (dct_index = 0; dct_index < dictionary_array_size(dictionary_array); dct_index++){
                        strcpy(correzione, dictionary_get_elem(dictionary_array, dct_index));
                        distance = edit_distance_dynamic_wrapper(str, correzione);
                        if (distance <= min_distance){   
                            if (distance < min_distance){
                                bzero(minimum_corrections_array, sizeof(minimum_corrections_array));
                                minimum_corrections_size = 0; 
                                min_distance = distance;
                            }     
                            strcpy(minimum_corrections_array[minimum_corrections_size], correzione);
                            minimum_corrections_size++;
                        }
                    }
                    word_corrections_print(str, minimum_corrections_array, minimum_corrections_size);
                }
                min_distance = INT_MAX;
                bzero(str, strlen(str));
                bzero(minimum_corrections_array, sizeof(minimum_corrections_array)); 
            }  
        }
    }*/
    fclose(tobechecked);
}

void init(const char *correctme, const char *dictionary){
    clock_t init_t, start_t, end_t;
    FILE *word_corrections;

    init_t = start_t = clock();
    Dictionary *dictionary_array = dictionary_create();
    load_dictionary(dictionary, dictionary_array);
    end_t = clock();
    printf("Dictionary loaded correctly, took: ~%f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

    //cleaning wordcorrections file from last execution, if present
    word_corrections = fopen("wordcorrections.txt", "w");
    fclose(word_corrections);   

    start_t = clock();
    correction(correctme, dictionary_array);
    end_t = clock();
    printf("Correction written correctly, took: ~%f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    
    start_t = clock();
    
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
