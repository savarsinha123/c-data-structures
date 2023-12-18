#ifndef QUEUE
#define QUEUE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

/** queue struct implemented based on linked list */
typedef struct queue queue_t;

/** 
 * Initializes queue
 * @return newly initialized queue
 */
queue_t *queue_init();

/** 
 * Frees queue
 * @param queue
 */
void queue_free(queue_t *queue);

/**
 * Returns size of queue
 * @param queue
 * @returns size of queue
 */
size_t queue_size(queue_t *queue);

/**
 * Checks whether queue is empty
 * @param queue
 * @returns true if queue is empty and false otherwise
 */
bool queue_is_empty(queue_t *queue);

/** 
 * Adds element to the back of the queue
 * @param queue
 * @param element to add
 */
void queue_add(queue_t *queue, void *element);

/**
 * Views element at the front of the queue
 * @param queue
 * @returns element at top of queue
 */
void *queue_peek(queue_t *queue);

/**
 * Removes element at the front of the queue
 * @param queue
 * @returns removed element
 */
void *queue_poll(queue_t *queue);

#endif