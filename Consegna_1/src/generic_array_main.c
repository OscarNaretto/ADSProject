#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "generic_array.h"

#define BUFFER_SIZE 1024

typedef struct _record {
  char *id_field;
  char *string_field;
  int integer_field;
  double float_field;
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
 * It returns 1 if the integer field of the first record is bigger than
 * the integer field of the second one (0 otherwise)
*/
static int succedes_record_int_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "succedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "succedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->integer_field > rec2_p->integer_field;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 if the float field of the first record is smaller than
 * the float field of the second one (0 otherwise)
*/
static int precedes_record_float_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_float_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_float_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->float_field < rec2_p->float_field;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 if the float field of the first record is bigger than
 * the float field of the second one (0 otherwise)
*/
static int succedes_record_float_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "succedes_record_float_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "succedes_record_float_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return rec1_p->float_field > rec2_p->float_field;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 iff the string field of the first record is smaller than
 * the string field of the second one (0 otherwise)
 */
static int precedes_record_string_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_string_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_string_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;
  return strcmp(rec1_p->string_field, rec2_p->string_field) < 0;
}

/*
 * It takes as input two pointers to Record.
 * It returns 1 iff the string field of the first record is bigger than
 * the string field of the second one (0 otherwise)
 */
static int succedes_record_string_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "succedes_record_string_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "succedes_record_string_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Record *rec1_p = (Record*)r1_p;
  Record *rec2_p = (Record*)r2_p;

  return strcmp(rec1_p->string_field, rec2_p->string_field) > 0;
}

static  void free_array(GenericArray *array) {
  unsigned long size = generic_array_size(array);
  for (unsigned long i = 0; i < size; i++) {
    Record *array_element = (Record*)generic_array_get(array, i);
    free(array_element->id_field);  
    free(array_element->string_field);
    free(array_element);
  }
  generic_array_free_memory(array);
}

void print_file_array(GenericArray *array, char *output_file) {
    FILE *ordered;
    
    ordered = fopen(output_file, "w");
    unsigned long size = generic_array_size(array);

    if (array == NULL) {
        fprintf(stderr, "print_file_array: array parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    if (ordered == NULL){
      ordered = stdout;
      printf("Not able to access output file. Using stdout instead\n");
    }
        
    Record *array_element;
    if (generic_array_is_empty(array)) {
        fprintf(ordered, "Empty array\n");
    } else {
        for (unsigned long i = 0; i < size; i++) {
            array_element = (Record*)generic_array_get(array, i);
            fprintf(ordered, "%s, %s, %d, %.9f\n", array_element->id_field, array_element->string_field, array_element->integer_field, array_element->float_field);
        }
    }
    fclose(ordered);
}

static void load_array(const char *file_name, GenericArray *array) {
  char buffer[BUFFER_SIZE];
  FILE *fp;

  printf("\nLoading data from file...\n");
  fp = fopen(file_name, "r");

  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the input file");
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
    generic_array_add(array, (void*)record_p);
  }
  fclose(fp);
}

static void data_elaboration_method(const char *input_file, char *output_file, int (*compare)(void*, void*)) {
  GenericArray *array = generic_array_create(compare);
  clock_t start_t, end_t, init_t;
  
  start_t = init_t = clock();
  load_array(input_file, array);
  end_t = clock();
  printf("\nData loaded; took %f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
  sorting_algorithm(array, compare, 0, generic_array_size(array) - 1);
  end_t = clock();
  printf("Data sorted; took %f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
  print_file_array(array, output_file);
  end_t = clock();
  printf("Data saved; took %f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
  printf("Saved in %s\n", output_file);
  
  start_t = clock();
  free_array(array);
  end_t = clock();
  printf("Data structure freed; took %f sec\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  printf("Total execution time: ~%f sec\n", (double)(end_t - init_t) / CLOCKS_PER_SEC);
}

int main(int argc, char const *argv[]) {
  
  if (argc == 4){
    set_k_value(argv[3]);
  } else if (argc < 3) {
    printf("Invalid arguments\n\n");
    printf("Terminal usage:\n - pass input_file_path as first argument\n - pass output_directory_path as second argument (output files will be named after their sorting field type)\n - (OPTIONAL)pass k_value as third argument");
    printf("Example: ./Main records.csv ../\n\n");
    printf("Make usage: make run #OPTIONAL#K=int_k_value\n\n");
    exit(EXIT_FAILURE);
  }
  char string_path[strlen(argv[2]) + 1], int_path[strlen(argv[2]) + 1], float_path[strlen(argv[2]) + 1];
  strcpy(string_path, argv[2]);
  strcpy(int_path, argv[2]);
  strcpy(float_path, argv[2]);

  printf("Goodmorning\n\nSelect sorting order with the proper parameter:\n");
  printf("- Increasing --> I/i\n");
  printf("- Decreasing --> D/d\n");

  char order;
  scanf(" %c", &order);
  order = (char)tolower(order);
  if (order != 'i' && order != 'd'){
    printf("Invalid parameter, closing current session\n");
    exit(EXIT_FAILURE);
  }

  printf("Select the sorting field with the proper parameter:\n");
  printf("- String --> S/s\n");
  printf("- Integer --> I/i\n");
  printf("- Floating point --> F/f\n");
  printf("- All of three, separately --> A/a\n");
  printf("\n- Exit --> any\n");

  char control;
  scanf(" %c", &control);
  control = (char)tolower(control);

  switch (control) {
    case 's':
      printf("Sorting by String field\n");
      if (order == 'i'){
        data_elaboration_method(argv[1], strcat(string_path, "/string_test.csv"), precedes_record_string_field);
      } else {
        data_elaboration_method(argv[1], strcat(string_path, "/string_test.csv"), succedes_record_string_field);
      }
      break;
      
    case 'i':
      printf("Sorting by Integer field\n");
      if (order == 'i'){
        data_elaboration_method(argv[1], strcat(int_path, "/int_test.csv"), precedes_record_int_field);
      } else {
        data_elaboration_method(argv[1], strcat(int_path, "/int_test.csv"), succedes_record_int_field);
      }
      break;

    case 'f':
      printf("Sorting by Floating point field\n");
      if (order == 'i'){
        data_elaboration_method(argv[1], strcat(float_path, "/float_test.csv"), precedes_record_float_field);
      } else {
        data_elaboration_method(argv[1], strcat(float_path, "/float_test.csv"), succedes_record_float_field);
      }
      break;
    
    case 'a':
      printf("Sorting by all fields in three different files\n");
      if (order == 'i'){
        data_elaboration_method(argv[1], strcat(string_path, "/string_test.csv"), precedes_record_string_field);
        data_elaboration_method(argv[1], strcat(int_path, "/int_test.csv"), precedes_record_int_field);
        data_elaboration_method(argv[1], strcat(float_path, "/float_test.csv"), precedes_record_float_field);
      } else {
        data_elaboration_method(argv[1], strcat(string_path, "/string_test.csv"), succedes_record_string_field);
        data_elaboration_method(argv[1], strcat(int_path, "/int_test.csv"), succedes_record_int_field);
        data_elaboration_method(argv[1], strcat(float_path, "/float_test.csv"), succedes_record_float_field);
      }
      break;
    
    default:
      printf("Goodbye\n");
      break;
    }

  return EXIT_SUCCESS;
}
