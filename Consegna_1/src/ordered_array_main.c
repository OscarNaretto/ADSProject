//include da aggiungere, valutare codice da riciclare per confronti strutture generiche. Scrivere dichiarazioni in .h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "ordered_array.h"

#define BUFFER_SIZE 1024

typedef struct _record {
  char *id_field;
  char *string_field;
  int integer_field;
  float float_field;
} Record;

void sorting_algorithm(OrderedArray *ordered_array, int (*compare)(void*, void*), int low, unsigned long high);

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

  //valutare se posizionare precedentemente le maiuscole o no. Nel caso, to lower

  return strcmp(rec1_p->string_field, rec2_p->string_field) < 0;
}

static  void free_array(OrderedArray *array) {
  unsigned long size = ordered_array_size(array);
  for (unsigned long i = 0; i < size; i++) {
    Record *array_element = (Record*)ordered_array_get(array, i);
    free(array_element->id_field);  
    free(array_element->string_field);
    free(array_element);
  }
  ordered_array_free_memory(array);
}

// print on file
void print_file_array(OrderedArray *array, const char *output_file) {
    FILE *ordered;
    
    ordered = fopen(output_file, "w"); //tmp solution
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
    char *string_field_in_read_line_p = strtok(NULL, ",");
    char *integer_field_in_read_line_p = strtok(NULL, ",");
    char *float_field_in_read_line_p = strtok(NULL, "\n");

    record_p->id_field = malloc((strlen(id_field_in_read_line_p)+1) * sizeof(char));
    record_p->string_field = malloc((strlen(string_field_in_read_line_p)+1) * sizeof(char));

    if (record_p->id_field == NULL || record_p->string_field == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the id field or string field of the read record");
      exit(EXIT_FAILURE);
    }
    
    strcpy(record_p->id_field, id_field_in_read_line_p);
    strcpy(record_p->string_field, string_field_in_read_line_p);
    record_p->integer_field = atoi(integer_field_in_read_line_p);
    record_p->float_field = atof(float_field_in_read_line_p);
    ordered_array_add(array, (void*)record_p);
  }
  fclose(fp);
}

static void test_with_comparison_function(const char *input_file, const char *output_file, int (*compare)(void*, void*)) {
  OrderedArray *array = ordered_array_create(compare);
  clock_t start_t, end_t, init_t;

  start_t = init_t = clock();
  load_array(input_file, array);
  end_t = clock();
  printf("\nData loaded; took %f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
  sorting_algorithm(array, compare, 0, ordered_array_size(array) - 1);
  end_t = clock();
  printf("Data sorted; took %f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
  print_file_array(array, output_file);
  end_t = clock();
  printf("Data saved; took %f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
  printf("Saved in ordered.csv, located at %s\n", output_file);
  
  start_t = clock();
  free_array(array);
  end_t = clock();
  printf("Data structure freed; took %f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  printf("Total execution time: ~%f sec\n", (double)(end_t - init_t) / CLOCKS_PER_SEC);
}

int main(int argc, char const *argv[]) {
  
  if (argc < 3) {
    printf("Invalid arguments\n\n");
    printf("Terminal usage: pass input_file_path and output_file_path as arguments\n");
    printf("Example: ./main records.csv ../ordered.csv\n\n");
    printf("Make usage: make run input=input_file_path output=output_file_path\n");
    exit(EXIT_FAILURE);
  }

  printf("Select the sorting field via proper parameter\n");
  printf("- String --> S/s\n");
  printf("- Integer --> I/i\n");
  printf("- Floating point --> F/f\n");
  printf("\n- Exit --> any\n");
  char control;
  scanf(" %c", &control);
  control = tolower(control);

  switch (control) {
    case 's':
      printf("Sorting by String field\n");
      test_with_comparison_function(argv[1], argv[2], precedes_record_string_field);
      break;
      
    case 'i':
      printf("Sorting by Integer field\n");
      test_with_comparison_function(argv[1], argv[2], precedes_record_int_field);
      break;

    case 'f':
      printf("Sorting by Floating point field\n");
      test_with_comparison_function(argv[1], argv[2], precedes_record_float_field);
      break;
      
    default:
      printf("Goodbye\n");
      break;
    }
    
  return EXIT_SUCCESS;
}
