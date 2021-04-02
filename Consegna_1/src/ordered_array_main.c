//include da aggiungere, valutare codice da riciclare per confronti strutture generiche. Scrivere dichiarazioni in .h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordered_array.h"


#define N 100    //dimensione vettore di appoggio merge
#define K 4     //costante di confronto per il passaggio da mergesort a insertionsort


#define BUFFER_SIZE 1024


int binarySearch(OrderedArray *ordered_array, void *item, int low, int high);

typedef struct _record {
  char *id_field;
  char *string_field;
  int integer_field;
  float float_field;
} Record;

/*
 * It takes as input two pointers to Record.
 * It returns 1 if the integer field of the first record is smaller than
 * the integer field of the second one (0 otherwise)
*/
static int precedes_record_int_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->integer_field < rec2_p->integer_field;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 if the float field of the first record is smaller than
 * the float field of the second one (0 otherwise)
*/
static int precedes_record_float_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->float_field < rec2_p->float_field;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 iff the string field of the first record is smaller than
 * the string field of the second one (0 otherwise)
 */
static int precedes_record_string_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_string: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_string: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return strcmp(rec1_p->string_field, rec2_p->string_field) < 0;
}

static  void free_array(OrderedArray *array) {
  unsigned long size = ordered_array_size(array);
  for (unsigned long i = 0; i < size; ++i) {
    Record *array_element = (Record*)ordered_array_get(array, i);
    free(array_element->id_field);  
    free(array_element->string_field);    //free corretti?
    free(array_element);
  }
  ordered_array_free_memory(array);
}

static  void print_array(OrderedArray *array) {
  unsigned long size = ordered_array_size(array);

  Record *array_element;
  printf("\nORDERED ARRAY OF RECORDS\n");

  for (unsigned long i = 0; i < size; ++i) {
    array_element = (Record*)ordered_array_get(array, i);
    printf("%s, %d\n", array_element->string_field, array_element->integer_field);
  }
}

// print on file
void print_file_array(OrderedArray *array) {
    FILE *ordered;
    ordered = fopen("../ordered.csv", "w");
    unsigned long size = ordered_array_size(array);

    if (array == NULL) {
        fprintf(stderr, "print_file_array: array parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    if (ordered == NULL){
      ordered = stdout;
      printf("Not able to access file. Using stdout instead\n");
    }
        
    Record *array_element;
    if (ordered_array_is_empty(array)) {
        fprintf(ordered, "Empty array\n");
    } else {
        for (unsigned long i = 0; i < size; i++) {
            array_element = (Record*)ordered_array_get(array, i);
            fprintf(ordered, "%s, %s, %d, %.9f\n", array_element->id_field, array_element->string_field, array_element->integer_field, array_element->float_field);
        }
    }
}

static void load_array(const char *file_name, OrderedArray *array) {
  char buffer[BUFFER_SIZE];
  FILE *fp;

  printf("\nLoading data from file...\n");
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file");
    exit(EXIT_FAILURE);
  }

  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    Record *record_p = malloc(sizeof(Record));
    if (record_p == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the read record");
      exit(EXIT_FAILURE);
    }

    char *id_field_in_read_line_p = strtok(buffer, ",");
    char *string_field_in_read_line_p = strtok(buffer, ",");
    char *integer_field_in_read_line_p = strtok(buffer, ","); //buffer instead of NULL? 
    char *float_field_in_read_line_p = strtok(NULL, ",");     //NULL should be used for the ending token


    record_p->string_field = malloc((strlen(string_field_in_read_line_p)+1) * sizeof(char));
    if (record_p->string_field == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
    }
    
    strcpy(record_p->id_field, id_field_in_read_line_p);
    strcpy(record_p->string_field, string_field_in_read_line_p);
    record_p->integer_field = atoi(integer_field_in_read_line_p);
    record_p->float_field = atof(float_field_in_read_line_p);
    ordered_array_add(array, (void*)record_p);
  }
  fclose(fp);
  printf("\nData loaded\n");
}

static void test_with_comparison_function(const char *file_name, int (*compare)(void*, void*)) {
  OrderedArray *array = ordered_array_create(compare);
  load_array(file_name, array);
  //sorting method here
  
  //print_array(array);   
  print_file_array(array);    //print on FILE
  free_array(array);
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