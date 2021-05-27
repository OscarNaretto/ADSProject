#ifndef GENERIC_ARRAY_H
#define GENERIC_ARRAY_H

typedef struct _GenericArray GenericArray;

/* It creates an empty generic array and returns the created generic array.
 * It accepts as input a pointer to a function implementing the precedence
 * relation between the array elements. Such a function must accept as input
 * two pointers to elements and return 0 if the first element does NOT precede
 * the second one and a number different from zero otherwise (for the succedes function the relation is inverted).
 * The input parameter cannot be NULL
 */
GenericArray *generic_array_create(int (*compare)(void*, void*));

/* It accepts as input a pointer to an generic array and
 * it returns 1 iff the generic array is empty (0 otherwise).
 * The input parameter cannot be NULL
 */
int generic_array_is_empty(GenericArray*);

/* It accepts as input a pointer to an generic array and it
 * returns the number of elements currently stored into the array.
 * The input parameter cannot be NULL
 */
unsigned long generic_array_size(GenericArray*);

/* It accepts as input a pointer to an generic array and a pointer to an
 * element. It adds the element to the generic array in the first empty position.
 * The input parameters cannot be NULL
 */
void generic_array_add(GenericArray*, void*);

/* It accepts as input a pointer to an generic array and an integer "i" and
 * it returns the pointer to the i-th element of the generic array
 * The first parameter cannot be NULL; the second parameter must be a valid
 * position within the generic array
 */
void *generic_array_get(GenericArray*, unsigned long);

/* It accepts as input a pointer to an generic array and
 * it frees the memory allocated to store the generic array.
 * It does not free the memory allocated to store the array elements,
 * since freeing that memory is responsibility of the function where
 * the generic array was created. The input parameters cannot be NULL
 */
void generic_array_free_memory(GenericArray*);

/* Calls recursively the merge-sort implementation until the generic_array length is leww or equal than k_value; then it uses
 * the binary insertion sort in an iterative implementation, in order to sort the array without putting too much weight on the stack
*/
void sorting_algorithm(GenericArray *generic_array, int (*compare)(void*, void*), unsigned long low, unsigned long high);

// Sets the K value if passed as argument; otherwise k_value will be the default one
void set_k_value(const char *k_value_char);

#endif
