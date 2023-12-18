#ifndef TREE_SET
#define TREE_SET

#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"
#include "function_types.h"

/** Node for linked list */
typedef struct node node_t;

/** Tree set struct implemented based on binary search tree */
typedef struct tree_set tree_set_t;

/** 
 * Initializes tree set of nums/chars
 * @return newly initialized tree set
 */
tree_set_t *tree_set_init();

/** 
 * Initializes tree set of strings
 * @return newly initialized tree set
 */
tree_set_t *tree_set_str_init();

/** 
 * Initializes tree set with given comparator
 * @param compar the function used to compare elements
 * @param freer the function used to free individual elements
 * Compare function should return
 *  >0 if arg1 < arg2,
 *  0 if arg1 == arg2,
 *  <0 if arg1 > arg2
 * @return newly initialized tree set
 */
tree_set_t *tree_set_comp_init(compar_t compar, free_t freer);

/** 
 * Frees tree set
 * @param set
 */
void tree_set_free(tree_set_t *set);

/**
 * Returns size of set
 * @param set
 * @returns size of set
 */
size_t tree_set_size(tree_set_t *set);

/**
 * Checks whether set is empty
 * @param set
 * @returns true if set is empty and false otherwise
 */
bool tree_set_is_empty(tree_set_t *set);

/** 
 * Adds element to set
 * @param set
 * @param element to add
 */
void tree_set_add(tree_set_t *set, void *element);

/**
 * Removes element from set
 * @param set
 * @param element
 */
void *tree_set_remove(tree_set_t *set, void *element);

/**
 * Checks if set contains the given element
 * @param set
 * @param element
 */
bool tree_set_contains(tree_set_t *set, void *element);

#endif