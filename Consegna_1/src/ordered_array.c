#include <stdlib.h>
#include <stdio.h>
#include "ordered_array.h"

//Initial capacity for the array
#define INITIAL_CAPACITY 2

static unsigned long get_index_to_insert(OrderedArray *ordered_array, void *element);
static void insert_element(OrderedArray *ordered_array, void *element, unsigned long index);

//It represents the internal structure of this implementation of ordered arrays
struct _OrderedArray {
  void **array;
  unsigned long size;
  unsigned long array_capacity;
  int (*precedes)(void*, void*);
};

OrderedArray *ordered_array_create(int (*precedes)(void*, void*)) {
  if (precedes == NULL) {
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
  ordered_array->precedes = precedes;
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
    ordered_array->array_capacity = 2 * ordered_array->array_capacity; // Why multiply by 2?
    ordered_array->array = (void**)realloc(ordered_array->array, ordered_array->array_capacity * sizeof(void*));
    if (ordered_array->array == NULL) {
      fprintf(stderr,"ordered_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
  }
  //unsigned long index = get_index_to_insert(ordered_array, element);
  //insert_element(ordered_array, element, index);
  ordered_array->array[ordered_array->size] = element;
  ordered_array->size++;
}


/*inserts the specified element in the specified ordered array at the specified index position
static void insert_element(OrderedArray *ordered_array, void *element, unsigned long index) {
  for (unsigned long i = ordered_array->size; i > index; --i)
    ordered_array->array[i] = ordered_array->array[i-1];
  ordered_array->array[index] = element;
} */



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

void merge(OrderedArray *ordered_array, int p, int q, int r){
    printf("Merging\n");
    
    int k = 0, i, j, v2[N];
    i = p;
    j = q + 1;

    while (i<=q && j<=r){
        if(v1[i] < v1[j]){
            v2[k] = v1[i];
            i++;
        }else{
            v2[k] = v1[j];
            j++;
        }
        k++;
    }
    
    while(i <= q){
        v2[k] = v1[i];
        i++;
        k++;
    }
    
    while(j <= r){
        v2[k] = v1[j];
        j++;
        k++;
    }
    
    k = p;
    while(k <= r){
        v1[k] = v2[k-p];
        k++;
    }
}


int binarySearch(OrderedArray *ordered_array, void *item, int low, int high) {

    if (high <= low) {
        if (ordered_array->precedes(ordered_array->array[low], item)){
            return low + 1;
        } else {
            return low;
        }
    }

    int mid = (low + high)/2;
  
    if(item == a[mid]){
        return mid+1;
    } else if(item > a[mid]){
        return binarySearch(a, item, mid+1, high);
    }
    
    return binarySearch(a, item, low, mid-1);  
}



s
void algoritmo(OrderedArray *ordered_array, int low, int high){

    if (high - low + 1 <= K){
        printf("Sorting\n");

        for (int i = low + 1; i  < high + 1; i++){
            int j = i - 1;
            Record selected = ordered_array->array[i];

            //posizione in cui deve essere inserito selezionato
            int index = binarySearch(a, selected, low, j);

            //ciclo per spostare l'elemento cosi da fare 
            //spazio per l'elemento da inserire
            while (j >= index){
                a[j+1] = a[j];
                j--;
            }
            a[index] = selected; 
        }
    }else{
        int mid;
        if (low < high) {
            mid = (low+high)/2;
            printf("Division\n");
            algoritmo(a, low, mid);
            printf("Division\n");
            algoritmo(a, mid+1, high);
            merge(a, low, mid, high);
        }
    }

}

