#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 30
#define MAX_WORDS_NUMBER 100

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
    if (strlen(string1) == 0) return (int)strlen(string2);
    if (strlen(string2) == 0) return (int)strlen(string1);

    if (string1[0] == string2[0]){
        no_op = edit_distance(string1+1, string2+1);
    } else {
        no_op = INT_MAX;
    }
    return min(1 + edit_distance(string1, string2+1), 1 + edit_distance(string1+1, string2), no_op);
}

//parte dal fondo della stringa attraverso le lenght, per implementare la tabella in cui salvare i risultati. Similarità all'approccio iterativo
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

int best_correction_index(char correzione_minima[MAX_WORDS_NUMBER][MAX_WORD_LENGTH], char *str, int correzione_minima_index){
    for (int i = 0; i < correzione_minima_index; i++){
        if (strlen(str) == strlen(correzione_minima[i])){
            return i;
        }
    }
    return correzione_minima_index - 1;
}
