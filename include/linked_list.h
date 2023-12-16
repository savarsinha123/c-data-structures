#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdio.h>

/** Node for linked list */
typedef struct node node_t;

/** Doubly linked list struct */
typedef struct linked_list linked_list_t;

/** 
 * Initializes linked list
 * @return newly initialized linked list
 */
linked_list_t *linked_list_init();

/** 
 * Frees linked list
 * @param list
 */
void linked_list_free(linked_list_t *list);

/**
 * Returns size of list
 * @param list
 * @returns retrieved element
 */
size_t linked_list_size(linked_list_t *list);

/** 
 * Adds element to end of linked list
 * @param list
 * @param element to add
 */
void linked_list_add(linked_list_t *list, void *element);

/**
 * Retrieves element at index from linked list
 * @param list
 * @param index to retrieve from
 * @returns retrieved element
 */
void *linked_list_get(linked_list_t *list, size_t index);

/**
 * Removes element at index from linked list
 * @param list
 * @param index to remove
 * @returns removed element
 */
void *linked_list_remove(linked_list_t *list, size_t index);

#endif