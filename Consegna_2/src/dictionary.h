#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct _Dictionary Dictionary;

/* It creates an empty dictionary array and returns the created dictionary array,
 * used to store all the words present in the dictionary file.
 */
Dictionary *dictionary_create();

/* It accepts as input a pointer to an dictionary array and a pointer to an
 * element. It adds the element to the dictionary array in the first empty position.
 * Mantaining order in such a way is possible because the dictionary file is already sorted.
 * The input parameters cannot be NULL
 */
void dictionary_add(Dictionary *dictionary_array, char *word);

/* It accepts as input a pointer to an dictionary array and it
 * returns the number of elements currently stored into the array.
 * The input parameter cannot be NULL
 */
long dictionary_array_size(Dictionary *dictionary_array);

/* It accepts as input a pointer to an dictionary array and a dictionary input file.
 * The method then calls in a loop the dictionary_add(), reading from file line by line.
 * Mantaining order in such a way is possible because the dictionary file is already sorted.
 * The input parameters cannot be NULL
 */
void load_dictionary(const char *dictionary, Dictionary *dictionary_array);

/* It accepts as input a pointer to an dictionary array and the key element to look for.
 * It returns the index of the element if present, -1 otherwise, 
 * using the dictionary_search() to check if the element is present or not
 * The input parameter cannot be NULL
 */
long dictionary_is_present(Dictionary *dictionary_array, char *key);


/* It accepts as input a pointer to an dictionary array and the right and left indexes used to look for the key between them.
 * It returns the index of the element if present, -1 otherwise, 
 * Time complexity is O(logn) thanks to the binary search implementation.
 * The input parameter cannot be NULL
 */
long dictionary_search(Dictionary *dictionary_array, long low, long high, char *key);

/* It accepts as input a pointer to an dictionary array and an integer "i" and
 * it returns the pointer to the i-th element of the dictionary array
 * The first parameter cannot be NULL; the second parameter must be a valid
 * position within the dictionary array
 */
char* dictionary_get_elem(Dictionary *dictionary_array, long i);

/* It accepts as input a pointer to an dictionary array and
 * it frees the memory allocated to store the dictionary array.
 * The input parameters cannot be NULL
 */
void dictionary_array_free(Dictionary *dictionary_array);

#endif
