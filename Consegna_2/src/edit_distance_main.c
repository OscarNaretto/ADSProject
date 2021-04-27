#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int min(int a, int b, int c) {
	if(a <= b && a <= c) return a;
	if(b <= c){
        return b;
    } else {
        return c;
    }
}

//parte dall'inizio della stringa, per comodità di lettura
int edit_distance(char *string1, char *string2){
    int no_op;
    if (strlen(string1) == 0) return strlen(string2);
    if (strlen(string2) == 0) return strlen(string1);

    if (string1[0] == string2[0]){
        no_op = edit_distance(string1+1, string2+1);
    } else {
        no_op = INT_MAX;
    }
    return min(1 + edit_distance(string1, string2+1), 1 + edit_distance(string1+1, string2), no_op);
}

int main(int argc, char const *argv[]){

    printf("Parole scelte: tassa  passato \n");
    char string1[] = "tassa";
    char string2[] = "passato"; 

    int res = edit_distance(string1, string2);
    printf("Risultato: %d\n", res);

    return EXIT_SUCCESS;
}