#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

#define INITIAL_CAPACITY 2
#define BUFFER_SIZE 1024

struct _Dictionary{
    char **array;
    long size;
    long array_capacity;
};

Dictionary *dictionary_create() {
  
  Dictionary *dictionary_array = (Dictionary*)malloc(sizeof(Dictionary));
  if (dictionary_array == NULL) {
    fprintf(stderr, "generic_array_create: unable to allocate memory for the ordered array");
    exit(EXIT_FAILURE);
  }
  dictionary_array->array = (char**)malloc(INITIAL_CAPACITY * sizeof(char*));
  if (dictionary_array->array == NULL) {
    fprintf(stderr, "generic_array_create: unable to allocate memory for the internal array");
    exit(EXIT_FAILURE);
  }
  
  dictionary_array->size = 0;
  dictionary_array->array_capacity = INITIAL_CAPACITY;
  return dictionary_array;
}

void dictionary_add(Dictionary *dictionary_array, char *word){
  if (dictionary_array == NULL) {
    fprintf(stderr, "add_ordered_array_element: generic_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (dictionary_array->array == NULL) {
      fprintf(stderr,"dictionary_array: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
  }


  if (dictionary_array->size >= dictionary_array->array_capacity) {
    dictionary_array->array_capacity = 2 * dictionary_array->array_capacity;
    dictionary_array->array = (char**)realloc(dictionary_array->array, (unsigned long)dictionary_array->array_capacity * sizeof(char*));
    if (dictionary_array->array == NULL) {
      fprintf(stderr,"generic_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
  }
  dictionary_array->array[dictionary_array->size] = malloc((strlen(word)+1) * sizeof(char));
  strcpy(dictionary_array->array[dictionary_array->size], word);
  dictionary_array->size++;
}

long dictionary_array_size(Dictionary *dictionary_array) {
  if (dictionary_array == NULL) {
    fprintf(stderr, "dictionary_array: generic_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return dictionary_array->size;
}

void load_dictionary(const char *dictionary, Dictionary *dictionary_array){
    FILE *fp;
    char *buffer;
    buffer = malloc(BUFFER_SIZE * sizeof(char));

    fp = fopen(dictionary, "r");
    if (fp == NULL) {
        fprintf(stderr, "dictionary: unable to open the dictionary file");
        exit(EXIT_FAILURE);
    }

    while(fscanf(fp, "%s", buffer) != EOF){
      dictionary_add(dictionary_array, buffer);
    }
    fclose(fp);
    free(buffer);
}

long dictionary_is_present(Dictionary *dictionary_array, char *key){
  return dictionary_search(dictionary_array, 0, dictionary_array->size - 1, key) != -1;
}

long dictionary_search(Dictionary *dictionary_array, long low, long high, char *key){
    if (high >= low){
        long mid = low + (high - low) / 2;
        
        if (strcmp(dictionary_array->array[mid], key) == 0) return (long)mid;
       
        if (strcmp(dictionary_array->array[mid], key) > 0) return dictionary_search(dictionary_array, low, mid - 1, key);
 
        return dictionary_search(dictionary_array, mid + 1, high, key);
    }
    return -1;
}

char* dictionary_get_elem(Dictionary *dictionary_array, long i) {
  if (dictionary_array == NULL) {
    fprintf(stderr, "dictionary_get_elem: generic_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= dictionary_array->size) {
    fprintf(stderr, "dictionary_get_elem: Index %lu is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  return dictionary_array->array[i];
}

void dictionary_array_free(Dictionary *dictionary_array) {
  long size = dictionary_array->size;
  for (long i = 0; i < size; i++) {
    free(dictionary_array->array[i]);
  }
  //free(dictionary_array->array);
  free(dictionary_array);
}
