#include <stdlib.h>
#include "unity.h"
#include "edit_distance_lib.h"

static void test_edit_distance_empty(){
    TEST_ASSERT_EQUAL_INT(0, edit_distance("",""));
}

static void test_edit_distance_1(){
    TEST_ASSERT_EQUAL_INT(1,edit_distance("i",""));
}

static void test_edit_distance_2(){
    TEST_ASSERT_EQUAL_INT(2,edit_distance("","ii"));
}

static void test_edit_distance_3(){
    TEST_ASSERT_EQUAL_INT(3,edit_distance("iii",""));
}
static void test_edit_distance_example_1(){
    TEST_ASSERT_EQUAL_INT(1,edit_distance("casa","cassa"));
}

static void test_edit_distance_example_2(){
    TEST_ASSERT_EQUAL_INT(2,edit_distance("casa","cara"));
}

static void test_edit_distance_example_3(){
    TEST_ASSERT_EQUAL_INT(4,edit_distance("tassa","passato"));
}

static void test_edit_distance_example_4(){
    TEST_ASSERT_EQUAL_INT(0,edit_distance("pioppo","pioppo"));
}

static void test_edit_distance_example_name_d(){
    TEST_ASSERT_EQUAL_INT(3,edit_distance("dani","danno"));
}

static void test_edit_distance_example_name_o(){
    TEST_ASSERT_EQUAL_INT(5,edit_distance("oscar","omahr")); //controllare 
}

static void test_edit_distance_example_name_v(){
    TEST_ASSERT_EQUAL_INT(3,edit_distance("vince","vincenzo")); //controllare 
}
/*--------TEST PARTE DINAMICA --------------------------------------------------
static void test_edit_distance_dyn_empty(){
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dynamic("","",0,0,NULL));
}

static void test_edit_distance_dyn_1(){
    TEST_ASSERT_EQUAL_INT(1,edit_distance("i",""));
}

static void test_edit_distance_dny_2(){
    TEST_ASSERT_EQUAL_INT(2,edit_distance("","ii"));
}

static void test_edit_distance_dny_3(){
    TEST_ASSERT_EQUAL_INT(3,edit_distance("iii",""));
}
static void test_edit_distance_example_1(){
    TEST_ASSERT_EQUAL_INT(1,edit_distance("casa","cassa"));
}

static void test_edit_distance_example_2(){
    TEST_ASSERT_EQUAL_INT(2,edit_distance("casa","cara"));
}

static void test_edit_distance_example_3(){
    TEST_ASSERT_EQUAL_INT(4,edit_distance("tassa","passato"));
}

static void test_edit_distance_example_4(){
    TEST_ASSERT_EQUAL_INT(0,edit_distance("pioppo","pioppo"));
}

static void test_edit_distance_example_name_d(){
    TEST_ASSERT_EQUAL_INT(3,edit_distance("dani","danno"));
}

static void test_edit_distance_example_name_o(){
    TEST_ASSERT_EQUAL_INT(5,edit_distance("oscar","omahr")); //controllare 
}

static void test_edit_distance_example_name_v(){
    TEST_ASSERT_EQUAL_INT(3,edit_distance("vince","vincenzo")); //controllare 
}
*/

int main(){
    UNITY_BEGIN();

    RUN_TEST(test_edit_distance_empty);
    RUN_TEST(test_edit_distance_1);
    RUN_TEST(test_edit_distance_2);
    RUN_TEST(test_edit_distance_3);
    RUN_TEST(test_edit_distance_example_1);
    RUN_TEST(test_edit_distance_example_2);
    RUN_TEST(test_edit_distance_example_2);
    RUN_TEST(test_edit_distance_example_3);
    RUN_TEST(test_edit_distance_example_4);
    RUN_TEST(test_edit_distance_example_name_d);
    RUN_TEST(test_edit_distance_example_name_o);
    RUN_TEST(test_edit_distance_example_name_v);

    return UNITY_END();
}