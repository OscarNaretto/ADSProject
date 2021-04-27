#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int min(int a, int b, int c) {
	int min = a;
    
	if(b < min)
	    min = b;
	if(c < min)
	    min = c;
	return min;
}

int edit_distance(char *string1, char *string2){
    int edit_distance_noop;
    if (strlen(string1) == 0){
        return strlen(string2);
    }

    if (strlen(string2) == 0){
        return strlen(string1);
    }

    char rest1[strlen(string1) - 1];        //oppure incremento puntatore della string
    char rest2[strlen(string2) - 1];        //valutare cambio approccio
    strcpy(rest1, string1 + 1);
    strcpy(rest2, string2 + 1);


    if (string1[0] == string2[0]){
        edit_distance_noop = edit_distance(rest1, rest2);
    } else {
        edit_distance_noop = INT_MAX;
    }
    
    return min(1 + edit_distance(string1, rest2), 1 + edit_distance(rest1, string2), edit_distance(rest1, rest2));
}

int main(int argc, char const *argv[]){

    printf("Parole scelte: tassa  passato \n");
    char string1[] = "pioppo";
    char string2[] = "pioppo";
    
    int res = edit_distance(string1, string2);

    printf("Risultato: %d\n", res);

    return EXIT_SUCCESS;
}