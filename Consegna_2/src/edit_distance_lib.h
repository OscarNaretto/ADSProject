#ifndef EDIT_DISTANCE_LIB_H
#define EDIT_DISTANCE_LIB_H

//Starts from first characters of the strings
int edit_distance(char *string1, char *string2);

//Starts from last characters of the strings, in order to implement memoization using an int matrix to save edit distances
int edit_distance_dynamic(char *string1, char *string2, int length1, int length2, int **recursive_calls_table);

int edit_distance_dynamic_wrapper(char *string1, char *string2);

#endif
