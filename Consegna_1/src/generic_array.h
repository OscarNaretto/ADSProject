#ifndef GENERIC_ARRAY_H
#define GENERIC_ARRAY_H

typedef struct _GenericArray GenericArray;

/* It creates an empty ordered array and returns the created ordered array.
 * It accepts as input a pointer to a function implementing the precedence
 * relation between the array elements. Such a function must accept as input
 * two pointers to elements and return 0 iff the first element does NOT precede
 * the second one and a number different from zero otherwise.
 * The input parameter cannot be NULL
 */
GenericArray *generic_array_create(int (*compare)(void*, void*));

/* It accepts as input a pointer to an ordered array and
 * it returns 1 iff the ordered array is empty (0 otherwise).
 * The input parameter cannot be NULL
 */
int generic_array_is_empty(GenericArray*);

/* It accepts as input a pointer to an ordered array and it
 * returns the number of elements currently stored into the array.
 * The input parameter cannot be NULL
 */
unsigned long generic_array_size(GenericArray*);

/* It accepts as input a pointer to an ordered array and a pointer to an
 * element. It adds the element to the ordered array in the right position.
 * The input parameters cannot be NULL
 */
void generic_array_add(GenericArray*, void*);

/* It accepts as input a pointer to an ordered array and an integer "i" and
 * it returns the pointer to the i-th element of the ordered array
 * The first parameter cannot be NULL; the second parameter must be a valid
 * position within the ordered array
 */
void *generic_array_get(GenericArray*, unsigned long);

/* It accepts as input a pointer to an ordered array and
 * it frees the memory allocated to store the ordered array.
 * It does not free the memory allocated to store the array elements,
 * since freeing that memory is responsibility of the function where
 * the ordered array was created. The input parameters cannot be NULL
 */
void generic_array_free_memory(GenericArray*);

void sorting_algorithm(GenericArray *ordered_array, int (*compare)(void*, void*), unsigned long low, unsigned long high);

void set_k_value(const char *k_value_char);

#endif
