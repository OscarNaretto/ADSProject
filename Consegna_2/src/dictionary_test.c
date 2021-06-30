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
    dictionary_add(dictionary_array, "aaa");
    TEST_ASSERT_EQUAL_INT(1, dictionary_array_size(dictionary_array));
    dictionary_array_free(dictionary_array);
}

static void test_dictionary_array_size_two_el(){
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array, "aaa");
    dictionary_add(dictionary_array, "bbb");
    TEST_ASSERT_EQUAL_INT(2, dictionary_array_size(dictionary_array));
    dictionary_array_free(dictionary_array);
}

static void test_present(){ 
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array,"aaa");
    dictionary_add(dictionary_array,"bbb");
    dictionary_add(dictionary_array,"ccc");
    TEST_ASSERT_EQUAL_INT(1,dictionary_is_present(dictionary_array,"bbb"));
    dictionary_array_free(dictionary_array);
}

static void test_not_present(){
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array,"aaa");
    dictionary_add(dictionary_array,"bbb");
    dictionary_add(dictionary_array,"ccc");
    TEST_ASSERT_EQUAL_INT(0,dictionary_is_present(dictionary_array,"fas"));
    dictionary_array_free(dictionary_array);
}

static void test_search(){
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array,"aaa");
    dictionary_add(dictionary_array,"bbb");
    TEST_ASSERT_EQUAL_INT(0,dictionary_search(dictionary_array,0,dictionary_array_size(dictionary_array),"aaa")); 
    dictionary_array_free(dictionary_array);
}

static void test_search_two(){
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array,"aaa");
    dictionary_add(dictionary_array,"bbb");
    dictionary_add(dictionary_array,"ccc");
    dictionary_add(dictionary_array,"ddd");
    TEST_ASSERT_EQUAL_INT(2,dictionary_search(dictionary_array,0,dictionary_array_size(dictionary_array),"ccc")); 
    dictionary_array_free(dictionary_array);
}

static void test_get_element(){
    Dictionary * dictionary_array = dictionary_create();
    dictionary_add(dictionary_array,"aaa");
    dictionary_add(dictionary_array,"bbb");
    dictionary_add(dictionary_array,"ccc");
    dictionary_add(dictionary_array,"ddd");
    TEST_ASSERT_EQUAL_STRING("ddd",dictionary_get_elem(dictionary_array,3)); 
    dictionary_array_free(dictionary_array);
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(test_dictionary_array_size_zero_el);
    RUN_TEST(test_dictionary_array_size_one_el);
    RUN_TEST(test_dictionary_array_size_two_el);
    RUN_TEST(test_present);
    RUN_TEST(test_not_present);
    RUN_TEST(test_search);
    RUN_TEST(test_search_two);
    RUN_TEST(test_get_element);

    return UNITY_END();
}