


#define MAX_WORD_LENGTH 30
#define MAX_WORDS_NUMBER 100

int edit_distance(char *string1, char *string2);

int edit_distance_dynamic(char *string1, char *string2, int length1, int length2, int **recursive_calls_table);

int best_correction_index(char correzione_minima[MAX_WORDS_NUMBER][MAX_WORD_LENGTH], char *str, int correzione_minima_index);

