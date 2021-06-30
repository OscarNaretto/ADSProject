#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include "edit_distance_lib.h"
#include "dictionary.h"

#define BUFFER_SIZE 1024
int max_corrections_number = 30;

char output_path[BUFFER_SIZE];

void word_corrections_print(char *str, char **minimum_corrections_array, int minimum_corrections_size){
    FILE *word_corrections;
    word_corrections = fopen(output_path, "a");    
    if (word_corrections == NULL) {
        word_corrections = stdout;
    }

    fprintf(word_corrections, "%s -> ", str);
    for (int i = 0; i < minimum_corrections_size; i++){
        fprintf(word_corrections, "%s ", minimum_corrections_array[i]);
    }
    fprintf(word_corrections, "\n");
    fclose(word_corrections);
}

void get_word_list(Dictionary *dictionary_array, char *buffer){
    int size = 0, min_distance = INT_MAX, distance, list_is_full = 0;
    char *words_list[max_corrections_number];
    
    for (long dct_index = 0; dct_index < dictionary_array_size(dictionary_array); dct_index++){            
        distance = edit_distance_dynamic_wrapper(buffer, dictionary_get_elem(dictionary_array, dct_index));
        if (size >= max_corrections_number){
                list_is_full = 1;
        }
        if (distance == min_distance && !list_is_full){
            words_list[size] = dictionary_get_elem(dictionary_array, dct_index);
            size++;
        } else if (distance < min_distance) {
            words_list[0] = dictionary_get_elem(dictionary_array, dct_index);
            size = 1;
            min_distance = distance;
            list_is_full = 0;
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
        char *lastc = &buffer[strlen(buffer) -1];
        if(*lastc=='.'|| *lastc==','|| *lastc=='!'|| *lastc=='?'|| *lastc==':' || *lastc==';') { *lastc='\0'; }
        if (!dictionary_is_present(dictionary_array, buffer)){
            get_word_list(dictionary_array, buffer);
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
    word_corrections = fopen(output_path, "w");
    if (word_corrections == NULL) {
        word_corrections = stdout;
        printf("Not able to access output file. Using stdout instead\n");    
    }
    fclose(word_corrections);   

    start_t = clock();
    extractor(correctme, dictionary_array);

    end_t = clock();
    printf("Corrections written correctly, took: ~%f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    
    start_t = clock();
    
    dictionary_array_free(dictionary_array);
    end_t = clock();
    printf("Memory freed correctly, took: ~%f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

    printf("Whole execution took: ~%f sec\n\n", (double)(end_t - init_t) / CLOCKS_PER_SEC);
    printf("%s contains a maximum of %d corrected words for each input mistake, within minimun edit_distance\n\n", output_path, max_corrections_number);
}

void set_max_corrections_number(const char *max_corrections_number_char){
  max_corrections_number = atoi(max_corrections_number_char);
}

int main(int argc, char const *argv[]){
    if (argc == 5){
        set_max_corrections_number(argv[4]);
    } else if (argc < 4){
        printf("Invalid arguments\n\n");
        printf("Terminal usage:\n - pass input_file_path as first argument\n - pass dictionary_file_path as second argument\n - pass output_file_path as second argument\n - (OPTIONAL)pass max_corrections_number as third argument; default is 5");
        printf("Example: ./main correctme.txt dictionary.txt corrections.txt 30\n");
        exit(EXIT_FAILURE);
    } 
    printf("\n\nGoodmorning\n");
    strcpy(output_path, argv[3]);
    init(argv[1], argv[2]);
}
