//typedef struct _Dictionary Dictionary;

typedef struct{
    char **array;
    unsigned long size;
    unsigned long array_capacity;
}Dictionary;

Dictionary *dictionary_create();

void dictionary_add(Dictionary *dictionary_array, char *word);

unsigned long dictionary_array_size(Dictionary *dictionary_array);

void load_dictionary(const char *dictionary, Dictionary *dictionary_array);

long dictionary_is_present(Dictionary *dictionary_array, char *key);

long dictionary_search(Dictionary *dictionary_array, unsigned long low, unsigned long high, char *key);

const char* dictionary_get_elem(Dictionary *dictionary_array, unsigned long i);

void dictionary_array_free(Dictionary *dictionary_array);
