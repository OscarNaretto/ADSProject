#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

int min(int a, int b, int c) {
	if(a <= b && a <= c) return a;
	if(b <= c){
        return b;
    } else {
        return c;
    }
}

int edit_distance(char *string1, char *string2){
    int no_op;
    if (strlen(string1) == 0) return (int)strlen(string2);
    if (strlen(string2) == 0) return (int)strlen(string1);

    if (string1[0] == string2[0]){
        no_op = edit_distance(string1+1, string2+1);
    } else {
        no_op = INT_MAX;
    }
    return min(1 + edit_distance(string1, string2+1), 1 + edit_distance(string1+1, string2), no_op);
}

int edit_distance_dynamic(char *string1, char *string2, int length1, int length2, int **recursive_calls_table){
    int no_op;
    if (length1 == 0) return length2;
    if (length2 == 0) return length1;

    if (recursive_calls_table[length1 - 1][length2 - 1] != -1) return recursive_calls_table[length1 - 1][length2 - 1];

    if (string1[length1 - 1] == string2[length2 - 1]) {
        no_op = recursive_calls_table[length1 - 1][length2 - 1] = edit_distance_dynamic(string1, string2, length1 - 1, length2 - 1, recursive_calls_table);
    } else {
        no_op = INT_MAX;
    }

    return recursive_calls_table[length1 - 1][length2 - 1] = min(1 + edit_distance_dynamic(string1, string2, length1, length2 - 1, recursive_calls_table), 1 + edit_distance_dynamic(string1, string2, length1 - 1, length2, recursive_calls_table), no_op);
}

int edit_distance_dynamic_wrapper(char *string1, char *string2){
    int **recursive_calls_table;
    //recursive_calls_table is used for memoization in correction()
    recursive_calls_table = (int **)malloc(strlen(string1) * sizeof(int*));  
    for (int i = 0; i < (int)strlen(string1); i++){
        recursive_calls_table[i] = malloc(strlen(string2) * sizeof(int));
    }

    for (int i = 0; i < (int)strlen(string1); i++){
        for (int j = 0; j < (int)strlen(string2); j++){
            recursive_calls_table[i][j] = -1;
        }
    }
    int res = edit_distance_dynamic(string1, string2, (int)strlen(string1), (int)strlen(string2), recursive_calls_table);

    for (int i = 0; i < (int)strlen(string1); i++){
        free(recursive_calls_table[i]);
    }
    free(recursive_calls_table);

    return res;
}
