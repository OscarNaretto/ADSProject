#include <stdio.h>
#include <stdlib.h>
#include "edit_distance_main.c"
#include "unity.h"

static void test_edit_distance_empty(){
    TEST_ASSERT_EQUAL_INT(0, edit_distance("","");
}


int main(){
    UNITY_BEGIN();
    RUN_TEST(test_edit_distance_empty);

    return UNITY_END();
}