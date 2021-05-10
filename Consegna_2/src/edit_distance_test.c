#include <stdlib.h>
#include "unity.h"
#include "edit_distance_lib.h"
#define MWL 10


int **recursive_calls_table;

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
    TEST_ASSERT_EQUAL_INT(4,edit_distance("oscar","omahr")); //controllare 
}

static void test_edit_distance_example_name_v(){
    TEST_ASSERT_EQUAL_INT(3,edit_distance("vince","vincenzo")); //controllare 
}
/*--------TEST PARTE DINAMICA --------------------------------------------------*/

static void test_edit_distance_dyn_empty(){
    recursive_calls_table = (int **)malloc(MWL* sizeof(int*));  
    for (int i = 0; i < MWL; i++){
        recursive_calls_table[i] = malloc(MWL * sizeof(int));
            for (int j = 0; j < MWL; j++){
                recursive_calls_table[i][j]= -1;
            }
    }

    TEST_ASSERT_EQUAL_INT(0, edit_distance_dynamic("","",0,0,recursive_calls_table));

     for (int i = 0; i < MWL; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
}

static void test_edit_distance_dyn_1(){
    recursive_calls_table = (int **)malloc(MWL* sizeof(int*));  
    for (int i = 0; i < MWL; i++){
        recursive_calls_table[i] = malloc(MWL * sizeof(int));
            for (int j = 0; j < MWL; j++){
                recursive_calls_table[i][j]= -1;
            }
    }

    TEST_ASSERT_EQUAL_INT(1,edit_distance_dynamic("i","",1,0,recursive_calls_table));

    for (int i = 0; i < MWL; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
}

static void test_edit_distance_dny_2(){
    recursive_calls_table = (int **)malloc(MWL* sizeof(int*));  
    for (int i = 0; i < MWL; i++){
        recursive_calls_table[i] = malloc(MWL * sizeof(int));
            for (int j = 0; j < MWL; j++){
                recursive_calls_table[i][j]= -1;
            }
    }

    TEST_ASSERT_EQUAL_INT(2,edit_distance_dynamic("","ii",0,2,recursive_calls_table));

    for (int i = 0; i < MWL; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
}

static void test_edit_distance_dny_3(){
    recursive_calls_table = (int **)malloc(MWL* sizeof(int*));  
    for (int i = 0; i < MWL; i++){
        recursive_calls_table[i] = malloc(MWL * sizeof(int));
            for (int j = 0; j < MWL; j++){
                recursive_calls_table[i][j]= -1;
            }
    }

    TEST_ASSERT_EQUAL_INT(3,edit_distance_dynamic("iii","",3,0,recursive_calls_table));

    for (int i = 0; i < MWL; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
}

static void test_edit_distance_dny_example_1(){
    recursive_calls_table = (int **)malloc(MWL* sizeof(int*));  
    for (int i = 0; i < MWL; i++){
        recursive_calls_table[i] = malloc(MWL * sizeof(int));
            for (int j = 0; j < MWL; j++){
                recursive_calls_table[i][j]= -1;
            }
    }

    TEST_ASSERT_EQUAL_INT(1,edit_distance_dynamic("casa","cassa",5,6,recursive_calls_table));

    for (int i = 0; i < MWL; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
}

static void test_edit_distance_dny_example_2(){
    recursive_calls_table = (int **)malloc(MWL* sizeof(int*));  
    for (int i = 0; i < MWL; i++){
        recursive_calls_table[i] = malloc(MWL * sizeof(int));
            for (int j = 0; j < MWL; j++){
                recursive_calls_table[i][j]= -1;
            }
    }

    TEST_ASSERT_EQUAL_INT(2,edit_distance_dynamic("casa","cara",5,5,recursive_calls_table));

    for (int i = 0; i < MWL; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
}

static void test_edit_distance_dny_example_3(){
    recursive_calls_table = (int **)malloc(MWL* sizeof(int*));  
    for (int i = 0; i < MWL; i++){
        recursive_calls_table[i] = malloc(MWL * sizeof(int));
            for (int j = 0; j < MWL; j++){
                recursive_calls_table[i][j]= -1;
            }
    }

    TEST_ASSERT_EQUAL_INT(4,edit_distance_dynamic("tassa","passato",6,8,recursive_calls_table));

    for (int i = 0; i < MWL; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
}

static void test_edit_distance_dny_example_4(){
    recursive_calls_table = (int **)malloc(MWL* sizeof(int*));  
    for (int i = 0; i < MWL; i++){
        recursive_calls_table[i] = malloc(MWL * sizeof(int));
            for (int j = 0; j < MWL; j++){
                recursive_calls_table[i][j]= -1;
            }
    }

    TEST_ASSERT_EQUAL_INT(0,edit_distance_dynamic("pioppo","pioppo",7,7, recursive_calls_table));

    for (int i = 0; i < MWL; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
}

static void test_edit_distance_dny_example_name_d(){
    recursive_calls_table = (int **)malloc(MWL* sizeof(int*));  
    for (int i = 0; i < MWL; i++){
        recursive_calls_table[i] = malloc(MWL * sizeof(int));
            for (int j = 0; j < MWL; j++){
                recursive_calls_table[i][j]= -1;
            }
    }

    TEST_ASSERT_EQUAL_INT(3,edit_distance_dynamic("dani","danno",5,6,recursive_calls_table));

    for (int i = 0; i < MWL; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
}

static void test_edit_distance_dny_example_name_o(){
    recursive_calls_table = (int **)malloc(MWL* sizeof(int*));  
    for (int i = 0; i < MWL; i++){
        recursive_calls_table[i] = malloc(MWL * sizeof(int));
            for (int j = 0; j < MWL; j++){
                recursive_calls_table[i][j]= -1;
            }
    }

    TEST_ASSERT_EQUAL_INT(4,edit_distance_dynamic("oscar","omahr",6,6,recursive_calls_table)); 

    for (int i = 0; i < MWL; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
}

static void test_edit_distance_dny_example_name_v(){
    recursive_calls_table = (int **)malloc(MWL* sizeof(int*));  
    for (int i = 0; i < MWL; i++){
        recursive_calls_table[i] = malloc(MWL * sizeof(int));
            for (int j = 0; j < MWL; j++){
                recursive_calls_table[i][j]= -1;
            }
    }

    TEST_ASSERT_EQUAL_INT(3,edit_distance_dynamic("vince","vincenzo",6,9,recursive_calls_table));

    for (int i = 0; i < MWL; i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);
}



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
/*---------- TEST PARTE DINAMICA -------------*/
    RUN_TEST(test_edit_distance_dyn_empty);
    RUN_TEST(test_edit_distance_dyn_1);
    RUN_TEST(test_edit_distance_dny_2);
    RUN_TEST(test_edit_distance_dny_3);
    RUN_TEST(test_edit_distance_dny_example_1);
    RUN_TEST(test_edit_distance_dny_example_2);
    RUN_TEST(test_edit_distance_dny_example_2);
    RUN_TEST(test_edit_distance_dny_example_3);
    RUN_TEST(test_edit_distance_dny_example_4);
    RUN_TEST(test_edit_distance_dny_example_name_d);
    RUN_TEST(test_edit_distance_dny_example_name_o);
    RUN_TEST(test_edit_distance_dny_example_name_v);

    return UNITY_END();
}