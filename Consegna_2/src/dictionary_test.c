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
    dictionary_array_free(dictionary_array);
}
/*
static void test_not_present(){ // da vedere
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array,"one");
    dictionary_add(dictionary_array,"two");
    dictionary_add(dictionary_array,"three");
    printf("%d",dictionary_is_present(dictionary_array,"for"));
    //TEST_ASSERT_EQUAL_INT(0,dictionary_is_present(dictionary_array,"for"));
    dictionary_array_free(dictionary_array);
}*/

static void test_search(){
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array,"one");
    dictionary_add(dictionary_array,"two");
    TEST_ASSERT_EQUAL_INT(0,dictionary_search(dictionary_array,0,dictionary_array_size(dictionary_array),"one")); 
    dictionary_array_free(dictionary_array);
}

static void test_search_two(){
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array,"one");
    dictionary_add(dictionary_array,"two");
    dictionary_add(dictionary_array,"three");
    dictionary_add(dictionary_array,"for");
    TEST_ASSERT_EQUAL_INT(2,dictionary_search(dictionary_array,0,dictionary_array_size(dictionary_array),"three")); 
    dictionary_array_free(dictionary_array);
}

static void test_get_element(){
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array,"one");
    dictionary_add(dictionary_array,"two");
    dictionary_add(dictionary_array,"three");
    dictionary_add(dictionary_array,"for");
    TEST_ASSERT_EQUAL_STRING("for",dictionary_get_elem(dictionary_array,3)); 
    dictionary_array_free(dictionary_array);

}

int main(){
    UNITY_BEGIN();

    RUN_TEST(test_dictionary_array_size_zero_el);
    RUN_TEST(test_dictionary_array_size_one_el);
    RUN_TEST(test_dictionary_array_size_two_el);
    RUN_TEST(test_present);
    //RUN_TEST(test_not_present);
    RUN_TEST(test_search);
    RUN_TEST(test_search_two);
    RUN_TEST(test_get_element);
    
    return UNITY_END();
}