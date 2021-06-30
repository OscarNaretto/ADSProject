#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include "edit_distance_lib.h"
#include "dictionary.h"

#define MAX_CORRECTIONS_NUMBER 30
#define BUFFER_SIZE 1024

void word_corrections_print(char *str, char **minimum_corrections_array, int minimum_corrections_size){
    FILE *word_corrections;
    word_corrections = fopen("wordcorrections.txt", "a");    
    if (word_corrections == NULL) {
        fprintf(stderr, "main: unable to open the file that has to be checked");
        exit(EXIT_FAILURE);
    }

    fprintf(word_corrections, "%s -> ", str);
    for (int i = 0; i < minimum_corrections_size; i++){
        fprintf(word_corrections, "%s ", minimum_corrections_array[i]);
    }
    fprintf(word_corrections, "\n");
    fclose(word_corrections);
}

void get_list(Dictionary *dictionary_array, char *buffer){
    int size = 0, min_distance = INT_MAX, distance;
    char *words_list[MAX_CORRECTIONS_NUMBER];
    
    for (int dct_index = 0; dct_index < dictionary_array_size(dictionary_array); dct_index++){            
        distance = edit_distance_dynamic_wrapper(buffer, dictionary_get_elem(dictionary_array, dct_index));
        if (distance == min_distance){
            words_list[size] = dictionary_get_elem(dictionary_array, dct_index);
            size++;
        } else if (distance < min_distance) {
            words_list[0] = dictionary_get_elem(dictionary_array, dct_index);
            size = 1;
            min_distance = distance;
        }
    }
    word_corrections_print(buffer, words_list, size);
}

void extractor(const char *correctme, Dictionary *dictionary_array){
    char buffer[BUFFER_SIZE];

    FILE *tobechecked;
    tobechecked = fopen(correctme, "r");
    if (tobechecked == NULL) {
        fprintf(stderr, "main: unable to open the file that has to be checked");
        exit(EXIT_FAILURE);
    }

    while(fscanf(tobechecked,"%s",buffer)!=EOF){
        buffer[0] = (char)tolower(buffer[0]);
        char *lastc = &buffer[strlen(buffer)-1];
        if(*lastc=='.'||*lastc==','||*lastc=='!'||*lastc=='?'||*lastc==39) { *lastc='\0'; }
        if (!dictionary_is_present(dictionary_array, buffer)){
            printf("\n chiamo getlist \n");
            get_list(dictionary_array, buffer);
        }
    }
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
    extractor(correctme, dictionary_array);

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
        printf("1- Inserire il path del file di testo da valutare\n ");
        printf("2- Inserire il path del dizionario.\n");
        printf("Facoltativo: inserire il numero massimo di correzioni desiderate. Di default è 5\n");
        printf("Esempio: ./main correctme.txt dictionary.txt 30\n");

        exit(EXIT_FAILURE);
    } else if (argc == 4){
        
    }

    init(argv[1], argv[2]);
}
