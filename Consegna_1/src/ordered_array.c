#include <stdlib.h>
#include <stdio.h>
#include "ordered_array.h"

//Initial capacity for the array
#define INITIAL_CAPACITY 2
//costante di confronto per il passaggio da mergesort a insertionsort

unsigned long k_value = 10; 

//It represents the internal structure of this implementation of ordered arrays
struct _OrderedArray {
  void **array;
  unsigned long size;
  unsigned long array_capacity;
  int (*compare)(void*, void*);
};

OrderedArray *ordered_array_create(int (*compare)(void*, void*)) {
  if (compare == NULL) {
    fprintf(stderr, "ordered_array_create: precedes parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  OrderedArray *ordered_array = (OrderedArray*)malloc(sizeof(OrderedArray));
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the ordered array");
    exit(EXIT_FAILURE);
  }
  ordered_array->array = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
  if (ordered_array->array == NULL) {
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the internal array");
    exit(EXIT_FAILURE);
  }
  ordered_array->size = 0;
  ordered_array->array_capacity = INITIAL_CAPACITY;
  ordered_array->compare = compare;
  return ordered_array;
}

int ordered_array_is_empty(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_is_empty: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return ordered_array->size == 0;
}

unsigned long ordered_array_size(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_size: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return ordered_array->size;
}

void ordered_array_add(OrderedArray *ordered_array, void *element) {
  if (ordered_array == NULL) {
    fprintf(stderr, "add_ordered_array_element: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (element == NULL) {
    fprintf(stderr, "add_ordered_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  if (ordered_array->size >= ordered_array->array_capacity) {
    ordered_array->array_capacity = 2 * ordered_array->array_capacity;
    ordered_array->array = (void**)realloc(ordered_array->array, ordered_array->array_capacity * sizeof(void*));
    if (ordered_array->array == NULL) {
      fprintf(stderr,"ordered_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
  }
  ordered_array->array[ordered_array->size] = element;
  ordered_array->size++;
}

void *ordered_array_get(OrderedArray *ordered_array, unsigned long i) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= ordered_array->size) {
    fprintf(stderr, "ordered_array_get: Index %lu is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  return ordered_array->array[i];
}

void ordered_array_free_memory(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_free_memory: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(ordered_array->array);
  free(ordered_array);
}

void merge(OrderedArray *ordered_array, int (*compare)(void*, void*), unsigned long p, unsigned long q, unsigned long r){
    
    unsigned long k = 0, i = p, j = q + 1;

    OrderedArray *tmp_array = ordered_array_create(compare);

    while (i<=q && j<=r){
        if(ordered_array->compare(ordered_array->array[i], ordered_array->array[j])){
            ordered_array_add(tmp_array, ordered_array->array[i]);
            i++;
        }else{
            ordered_array_add(tmp_array, ordered_array->array[j]);
            j++;
        }
    }
    
    while(i <= q){
        ordered_array_add(tmp_array, ordered_array->array[i]);
        i++;
    }
    
    while(j <= r){
        ordered_array_add(tmp_array, ordered_array->array[j]);
        j++;
    }
  
    k = p;
    while(k <= r){
        ordered_array->array[k] = tmp_array->array[k-p];
        k++;
    }
    ordered_array_free_memory(tmp_array);
}

unsigned long binarySearch(OrderedArray *ordered_array, void *item, unsigned long low, unsigned long high) {

    if (high <= low) {
        if (ordered_array->compare(ordered_array->array[low], item)){
            return low + 1;
        } else {
            return low;
        }
    }

    unsigned long mid = (low + high)/2;
    if (ordered_array->compare(ordered_array->array[mid], item)){
        return binarySearch(ordered_array, item, mid+1, high);
    }
    return binarySearch(ordered_array, item, low, mid-1);  
}

void sorting_algorithm(OrderedArray *ordered_array, int (*compare)(void*, void*), unsigned long low, unsigned long high){

    if (high - low + 1 <= k_value){

        for (unsigned long i = low + 1; i  < high + 1; i++){
            unsigned long j = i - 1;
            OrderedArray *tmp_array = ordered_array_create(compare);
            tmp_array->array[0] = ordered_array->array[i];

            //posizione in cui deve essere inserito selezionato
            unsigned long index = binarySearch(ordered_array, tmp_array->array[0], low, j);

            //ciclo per spostare l'elemento cosi da fare 
            //spazio per l'elemento da inserire
            while (j >= index){
                ordered_array->array[j+1] = ordered_array->array[j];
                j--;
            }
            ordered_array->array[index] = tmp_array->array[0]; 

            ordered_array_free_memory(tmp_array);
        }
    }else{
        unsigned long mid;
        if (low < high) {
            mid = (low+high)/2;
            sorting_algorithm(ordered_array, compare, low, mid);
            sorting_algorithm(ordered_array, compare, mid+1, high);
            merge(ordered_array, compare, low, mid, high);
        }
    }
}

void set_k_value(const char *k_value_char){
  k_value = atoi(k_value_char);
}
