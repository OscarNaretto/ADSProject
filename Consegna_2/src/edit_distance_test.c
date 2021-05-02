#include <stdlib.h>
#include "unity.h"
#include "edit_distance_library.h"

static void test_edit_distance_empty(){
    TEST_ASSERT_EQUAL_INT(0, edit_distance("",""));
}

static void test_edit_distance_empty_1(){
    TEST_ASSERT_EQUAL_INT(1,edit_distance("a",""));
}




int main(){
    UNITY_BEGIN();

    RUN_TEST(test_edit_distance_empty);
    RUN_TEST(test_edit_distance_empty_1);

    return UNITY_END();
}