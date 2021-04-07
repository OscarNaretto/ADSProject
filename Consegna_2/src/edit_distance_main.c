#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min3(int a, int b, int c){
    if (a < b){
        if (a < c){
            return a;
        } else {
            return c;
        }
    } else if (b < c ){
        return b;
    } else {
        return c;
    }
}

int min2(int a, int b){
    if (a < b){
        return a;
    } else {
        return b;
    }
}

int edit_distance(char *string1, char *string2){
    if (strlen(string1) == 0){
        return strlen(string2);
    }

    if (strlen(string2) == 0){
        return strlen(string1);
    }

    char rest1[strlen(string1) - 1];
    char rest2[strlen(string2) - 1];
    strcpy(rest1, string1 + 1);
    strcpy(rest2, string2 + 1);

    if (string1[0] == string2[0]){
        return min3(1 + edit_distance(string1, rest2), 1 + edit_distance(rest1, string2), edit_distance(rest1, rest2));
    } else {
        return min2(1 + edit_distance(string1, rest2), 1 + edit_distance(rest1, string2));
    }
}

int main(int argc, char const *argv[]){

    printf("Parole scelte: tassa  passato \n");
    char string1[] = "pioppo";
    char string2[] = "pioppo";
    
    int res = edit_distance(string1, string2);

    printf("Risultato: %d\n", res);

    return EXIT_SUCCESS;
}