#include <stdlib.h>
#include "unity.h"
#include "generic_array.h"

static int precedes_int(void *i1_p, void *i2_p) {
  int *int1_p = (int*)i1_p;
  int *int2_p = (int*)i2_p;
  return *int1_p < *int2_p;
}

static int succedes_int(void *i1_p, void *i2_p) {
  int *int1_p = (int*)i1_p;
  int *int2_p = (int*)i2_p;
  return *int1_p > *int2_p;
}

static void test_precedes_int(){
  int i1 = 1;
  int i2 = 7;
  TEST_ASSERT_TRUE(precedes_int(&i1,&i2));
}

static void test_precedes_int_reverse(){
  int i1 = 7;
  int i2 = 1;
  TEST_ASSERT_FALSE(precedes_int(&i1,&i2))
}

static void test_succedes_int(){
  int i1 = 1;
  int i2 = 7;
  TEST_ASSERT_TRUE(succedes_int(&i2,&i1));
}

static void test_succedes_int_reverse(){
  int i1 = 1;
  int i2 = 7;
  TEST_ASSERT_FALSE(succedes_int(&i1,&i2));
}

  static void test_generic_array_is_empty_zero_el() {
  GenericArray *generic_array_int = generic_array_create(precedes_int); 
  TEST_ASSERT_TRUE(generic_array_is_empty(generic_array_int));
  generic_array_free_memory(generic_array_int);  
  }

    static void test_generic_array_is_empty_one_el() {
    int i = -12;
    GenericArray *generic_array_int = generic_array_create(precedes_int);
    generic_array_add(generic_array_int, &i);   
    TEST_ASSERT_FALSE(generic_array_is_empty(generic_array_int));
    generic_array_free_memory(generic_array_int);
}

  static void test_generic_array_size_zero_el() {
    GenericArray *generic_array_int = generic_array_create(precedes_int);
    TEST_ASSERT_EQUAL_INT(0, generic_array_size(generic_array_int));
    generic_array_free_memory(generic_array_int);
}

    static void test_generic_array_size_one_el() {
    int i1 = -12;
    GenericArray *generic_array_int = generic_array_create(precedes_int);
    generic_array_add(generic_array_int, &i1);
    TEST_ASSERT_EQUAL_INT(1, generic_array_size(generic_array_int));
    generic_array_free_memory(generic_array_int);
}

    static void test_generic_array_size_two_el() {
    int i1 = -12;
    int i2 = 2;
    GenericArray *generic_array_int = generic_array_create(precedes_int);
    generic_array_add(generic_array_int, &i1);
    generic_array_add(generic_array_int, &i2);
    TEST_ASSERT_EQUAL_INT(2, generic_array_size(generic_array_int));
    generic_array_free_memory(generic_array_int);
}

static void test_generic_array_add_get_one_el() {
  int i1 = -12;
  GenericArray *generic_array_int = generic_array_create(precedes_int);
  generic_array_add(generic_array_int, &i1);
  TEST_ASSERT_EQUAL_PTR(&i1, generic_array_get(generic_array_int, 0)); // asserische che i puntatori puntino nella stessa posizione di memoria
  generic_array_free_memory(generic_array_int);
}

static void test_generic_array_add_get_three_el() {
  int i1 = -12;
  int i2 = 0;
  int i3 = 4;
  int* exp_arr[] = {&i1, &i2, &i3};

  GenericArray *generic_array_int = generic_array_create(precedes_int);
  generic_array_add(generic_array_int, &i2);
  generic_array_add(generic_array_int, &i3);
  generic_array_add(generic_array_int, &i1);
  sorting_algorithm(generic_array_int, precedes_int, 0, generic_array_size(generic_array_int) - 1);

  int **act_arr = malloc(3*sizeof(int*));
  for (unsigned long i=0; i < 3; ++i) {
    act_arr[i] = (int*)generic_array_get(generic_array_int, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, act_arr, 3);//(I,j,z) sono i parametri di entrabi gli array , z sono gli elemnti da controllare
  free(act_arr);
  generic_array_free_memory(generic_array_int);
}

static void test_sorting_algorithm(){
    int i1 = 2;
    int i2 = 0;
    int i3 = 4;
    int i4 = 23;
    int i5 = 10;

    GenericArray *generic_array_int = generic_array_create(precedes_int);
    generic_array_add(generic_array_int, &i4);
    generic_array_add(generic_array_int, &i2);
    generic_array_add(generic_array_int, &i1);
    generic_array_add(generic_array_int, &i5);
    generic_array_add(generic_array_int, &i3);
    sorting_algorithm(generic_array_int,precedes_int, 0, generic_array_size(generic_array_int) - 1);
    TEST_ASSERT_EQUAL_PTR(&i2,generic_array_get(generic_array_int, 0));
    TEST_ASSERT_EQUAL_PTR(&i1,generic_array_get(generic_array_int, 1));
    TEST_ASSERT_EQUAL_PTR(&i3,generic_array_get(generic_array_int, 2));
    TEST_ASSERT_EQUAL_PTR(&i5,generic_array_get(generic_array_int, 3)); 
    TEST_ASSERT_EQUAL_PTR(&i4,generic_array_get(generic_array_int, 4));
    generic_array_free_memory(generic_array_int);
}

static void test_sorting_algorithm_reversed(){
    int i1 = 2;
    int i2 = 0;
    int i3 = 4;
    int i4 = 23;
    int i5 = 10;

    GenericArray *generic_array_int = generic_array_create(precedes_int);
    generic_array_add(generic_array_int, &i3);
    generic_array_add(generic_array_int, &i5);
    generic_array_add(generic_array_int, &i1);
    generic_array_add(generic_array_int, &i2);
    generic_array_add(generic_array_int, &i4);
    sorting_algorithm(generic_array_int,precedes_int, 0, generic_array_size(generic_array_int) - 1);
    TEST_ASSERT_EQUAL_PTR(&i2,generic_array_get(generic_array_int, 0));
    TEST_ASSERT_EQUAL_PTR(&i1,generic_array_get(generic_array_int, 1));
    TEST_ASSERT_EQUAL_PTR(&i3,generic_array_get(generic_array_int, 2));
    TEST_ASSERT_EQUAL_PTR(&i5,generic_array_get(generic_array_int, 3)); 
    TEST_ASSERT_EQUAL_PTR(&i4,generic_array_get(generic_array_int, 4));
    generic_array_free_memory(generic_array_int);
}

static void test_algorithm_equal_two_elements(){
    int i1 = 2;
    int i2 = 4;
    int i3 = 4;
    int i4 = 23;
    int i5 = 10;

    GenericArray *generic_array_int = generic_array_create(precedes_int);
    generic_array_add(generic_array_int, &i4);
    generic_array_add(generic_array_int, &i2);
    generic_array_add(generic_array_int, &i1);
    generic_array_add(generic_array_int, &i5);
    generic_array_add(generic_array_int, &i3);
    sorting_algorithm(generic_array_int,precedes_int, 0, generic_array_size(generic_array_int) - 1);
    TEST_ASSERT_EQUAL_PTR(&i1,generic_array_get(generic_array_int, 0));
    TEST_ASSERT_EQUAL_PTR(&i3,generic_array_get(generic_array_int, 1));
    TEST_ASSERT_EQUAL_PTR(&i2,generic_array_get(generic_array_int, 2));
    TEST_ASSERT_EQUAL_PTR(&i5,generic_array_get(generic_array_int, 3)); 
    TEST_ASSERT_EQUAL_PTR(&i4,generic_array_get(generic_array_int, 4));
    generic_array_free_memory(generic_array_int);
}



static void test_algorithm_equal_three_elements(){
    int i1 = 2;
    int i2 = 4;
    int i3 = 4;
    int i4 = 4;
    int i5 = 10;

    GenericArray *generic_array_int = generic_array_create(precedes_int);
    generic_array_add(generic_array_int, &i4);
    generic_array_add(generic_array_int, &i2);
    generic_array_add(generic_array_int, &i1);
    generic_array_add(generic_array_int, &i5);
    generic_array_add(generic_array_int, &i3);
    sorting_algorithm(generic_array_int,precedes_int, 0, generic_array_size(generic_array_int) - 1);
    TEST_ASSERT_EQUAL_PTR(&i1,generic_array_get(generic_array_int, 0));
    TEST_ASSERT_EQUAL_PTR(&i3,generic_array_get(generic_array_int, 1));
    TEST_ASSERT_EQUAL_PTR(&i2,generic_array_get(generic_array_int, 2));
    TEST_ASSERT_EQUAL_PTR(&i4,generic_array_get(generic_array_int, 3)); 
    TEST_ASSERT_EQUAL_PTR(&i5,generic_array_get(generic_array_int, 4));
    generic_array_free_memory(generic_array_int);
}


static void test_algorithm_equal_full_elements(){
    int i1 = 4;
    int i2 = 4;
    int i3 = 4;

    GenericArray *generic_array_int = generic_array_create(precedes_int);
    generic_array_add(generic_array_int, &i3);
    generic_array_add(generic_array_int, &i1);
    generic_array_add(generic_array_int, &i2);
    sorting_algorithm(generic_array_int,precedes_int, 0, generic_array_size(generic_array_int) - 1);
    TEST_ASSERT_EQUAL_PTR(&i2,generic_array_get(generic_array_int, 0));
    TEST_ASSERT_EQUAL_PTR(&i1,generic_array_get(generic_array_int, 1));
    TEST_ASSERT_EQUAL_PTR(&i3,generic_array_get(generic_array_int, 2)); 
    generic_array_free_memory(generic_array_int);
}




int main(){
    UNITY_BEGIN();
    RUN_TEST(test_precedes_int);
    RUN_TEST(test_precedes_int_reverse);
    RUN_TEST(test_succedes_int);
    RUN_TEST(test_succedes_int_reverse);
    RUN_TEST(test_generic_array_is_empty_zero_el);
    RUN_TEST(test_generic_array_is_empty_one_el);
    RUN_TEST(test_generic_array_size_zero_el);
    RUN_TEST(test_generic_array_size_one_el);
    RUN_TEST(test_generic_array_size_two_el);
    RUN_TEST(test_generic_array_add_get_one_el);
    RUN_TEST(test_generic_array_add_get_three_el);
    RUN_TEST(test_sorting_algorithm);
    RUN_TEST(test_sorting_algorithm_reversed);
    RUN_TEST(test_algorithm_equal_two_elements);
    RUN_TEST(test_algorithm_equal_three_elements);
    RUN_TEST(test_algorithm_equal_full_elements);
    return UNITY_END();
}
