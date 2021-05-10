#include <stdlib.h>
#include "unity.h"
#include "dictionary.h"



static void test_dictionary_array_size_zero_el(){
    Dictionary *dictionary_array = dictionary_create();
    TEST_ASSERT_EQUAL_INT(0, dictionary_array_size(dictionary_array));
    dictionary_array_free(dictionary_array);
}

static void test_dictionary_array_size_one_el(){
    Dictionary *dictionary_array = dictionary_create();
    dictionary_add(dictionary_array, "one");
    TEST_ASSERT_EQUAL_INT(1, dictionary_array_size(dictionary_array));
    dictionary_array_free(dictionary_array);
}

static void test_dictionary_array_size_two_el(){
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array, "one");
    dictionary_add(dictionary_array, "two");
    TEST_ASSERT_EQUAL_INT(2, dictionary_array_size(dictionary_array));
    dictionary_array_free(dictionary_array);
}

static void test_present(){ // da vedere
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array,"one");
    dictionary_add(dictionary_array,"two");
    TEST_ASSERT_EQUAL_INT(1,dictionary_is_present(dictionary_array,"one")); // 1 perchè elemento è presente
}

static void test_not_present(){ // da vedere
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array,"one");
    dictionary_add(dictionary_array,"two");
    dictionary_add(dictionary_array,"three");
    TTEST_ASSERT_EQUAL_INT(0,dictionary_is_present(dictionary_array,"for"));
    dictionary_array_free(dictionary_array);
}


int main(){
    UNITY_BEGIN();

    RUN_TEST(test_dictionary_array_size_zero_el);
    RUN_TEST(test_dictionary_array_size_one_el);
    RUN_TEST(test_dictionary_array_size_two_el);
    RUN_TEST(test_present);
    RUN_TEST(test_not_present);

    return UNITY_END();
}