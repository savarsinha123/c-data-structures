#ifndef FUNCTION_TYPES
#define FUNCTION_TYPES

#include <stdio.h>
#include <stdbool.h>

/** Function that frees a given struct */
typedef void (*free_t)(void *);

/** Comparison function type */
typedef int (*compar_t)(void *, void *);

/** Function that tests equality to two variables of same type */
typedef bool (*equals_t)(void *, void *);

#endif