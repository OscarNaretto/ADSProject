#include <stdlib.h>
#include "unity.h"
#include "ordered_array.h"


static int precedes_int(void *i1_p, void *i2_p) {
  int *int1_p = (int*)i1_p;
  int *int2_p = (int*)i2_p;
  return *int1_p < *int2_p;
}

//il numero di elementi del array appena creato dovrà essere zero

  static void test_ordered_array_is_empty_zero_el() {
  OrderedArray *ordered_array_int = ordered_array_create(precedes_int); // creo un array
  TEST_ASSERT_TRUE(ordered_array_is_empty(ordered_array_int));
  ordered_array_free_memory(ordered_array_int); // libero l'array dalla memoria 
}

    static void test_ordered_array_is_empty_one_el() {
    int i = -12;
    OrderedArray *ordered_array_int = ordered_array_create(precedes_int);
    ordered_array_add(ordered_array_int, &i);// aggiungo l'elemento 
    TEST_ASSERT_FALSE(ordered_array_is_empty(ordered_array_int));
    ordered_array_free_memory(ordered_array_int);
}

    static void test_ordered_array_size_one_el() {
    int i1 = -12;
    OrderedArray *ordered_array_int = ordered_array_create(precedes_int);
    ordered_array_add(ordered_array_int, &i1);
    TEST_ASSERT_EQUAL_INT(1, ordered_array_size(ordered_array_int));
    ordered_array_free_memory(ordered_array_int);
}


    static void test_ordered_array_size_two_el() {
    int i1 = -12;
    int i2 = 2;
    OrderedArray *ordered_array_int = ordered_array_create(precedes_int);
    ordered_array_add(ordered_array_int, &i1);
    ordered_array_add(ordered_array_int, &i2);
    TEST_ASSERT_EQUAL_INT(2, ordered_array_size(ordered_array_int));
    ordered_array_free_memory(ordered_array_int);
}

static void test_ordered_array_add_get_one_el() {
  int i1 = -12;
  OrderedArray *ordered_array_int = ordered_array_create(precedes_int);
  ordered_array_add(ordered_array_int, &i1);
  TEST_ASSERT_EQUAL_PTR(&i1, ordered_array_get(ordered_array_int, 0)); // asserische che i puntatori puntino nella stessa posizione di memoria
  ordered_array_free_memory(ordered_array_int);
}


static void test_ordered_array_add_get_three_el() {
  int i1 = -12;
  int i2 = 0;
  int i3 = 4;
  int* exp_arr[] = {&i1, &i2, &i3};

  OrderedArray *ordered_array_int = ordered_array_create(precedes_int);
  ordered_array_add(ordered_array_int, &i1);
  ordered_array_add(ordered_array_int, &i2);
  ordered_array_add(ordered_array_int, &i3);

  int **act_arr = malloc(3*sizeof(int*));
  for (unsigned long i=0; i < 3; ++i) {
    act_arr[i] = (int*)ordered_array_get(ordered_array_int, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, act_arr, 3);//(I,j,z) sono i parametri di entrabi gli array , z sono gli elemnti da controllare
  free(act_arr);
  ordered_array_free_memory(ordered_array_int);
}


static void test_algorithm(){
    int i1 = 2;
    int i2 = 0;
    int i3 = 4;
    int i4 = 23;
    int i5 = 10;

    OrderedArray *ordered_array_int = ordered_array_create(precedes_int);
    ordered_array_add(ordered_array_int, &i4);
    ordered_array_add(ordered_array_int, &i2);
    ordered_array_add(ordered_array_int, &i1);
    ordered_array_add(ordered_array_int, &i5);
    ordered_array_add(ordered_array_int, &i3);
    sortingAlgorithm(ordered_array_int,precedes_int, 0, ordered_array_size(ordered_array_int) - 1);
    TEST_ASSERT_EQUAL_PTR(&i2,ordered_array_get(ordered_array_int, 0));
    TEST_ASSERT_EQUAL_PTR(&i1,ordered_array_get(ordered_array_int, 1));
    TEST_ASSERT_EQUAL_PTR(&i3,ordered_array_get(ordered_array_int, 2));
    TEST_ASSERT_EQUAL_PTR(&i5,ordered_array_get(ordered_array_int, 3)); 
    TEST_ASSERT_EQUAL_PTR(&i4,ordered_array_get(ordered_array_int, 4));
    ordered_array_free_memory(ordered_array_int);
}


static void test_algorithm_reversed(){
    int i1 = 2;
    int i2 = 0;
    int i3 = 4;
    int i4 = 23;
    int i5 = 10;

    OrderedArray *ordered_array_int = ordered_array_create(precedes_int);
    ordered_array_add(ordered_array_int, &i3);
    ordered_array_add(ordered_array_int, &i5);
    ordered_array_add(ordered_array_int, &i1);
    ordered_array_add(ordered_array_int, &i2);
    ordered_array_add(ordered_array_int, &i4);
    sortingAlgorithm(ordered_array_int,precedes_int, 0, ordered_array_size(ordered_array_int) - 1);
    TEST_ASSERT_EQUAL_PTR(&i2,ordered_array_get(ordered_array_int, 0));
    TEST_ASSERT_EQUAL_PTR(&i1,ordered_array_get(ordered_array_int, 1));
    TEST_ASSERT_EQUAL_PTR(&i3,ordered_array_get(ordered_array_int, 2));
    TEST_ASSERT_EQUAL_PTR(&i5,ordered_array_get(ordered_array_int, 3)); 
    TEST_ASSERT_EQUAL_PTR(&i4,ordered_array_get(ordered_array_int, 4));
    ordered_array_free_memory(ordered_array_int);
}




int main(){
    UNITY_BEGIN();
    RUN_TEST(test_ordered_array_is_empty_zero_el);
    RUN_TEST(test_ordered_array_is_empty_zero_el);
    RUN_TEST(test_ordered_array_is_empty_one_el);
    RUN_TEST(test_ordered_array_size_one_el);
    RUN_TEST(test_ordered_array_size_two_el);
    RUN_TEST(test_ordered_array_add_get_one_el);
    //RUN_TEST(test_ordered_array_add_get_three_el);
    RUN_TEST(test_algorithm);
    RUN_TEST(test_algorithm_reversed);
    return UNITY_END();
}

