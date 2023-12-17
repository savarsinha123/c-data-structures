#ifndef STACK
#define STACK

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

/** Stack struct implemented based on linked list */
typedef struct stack stack_t;

/** 
 * Initializes stack
 * @return newly initialized stack
 */
stack_t *stack_init();

/** 
 * Frees stack
 * @param stack
 */
void stack_free(stack_t *stack);

/**
 * Returns size of stack
 * @param stack
 * @returns size of stack
 */
size_t stack_size(stack_t *stack);

/**
 * Checks whether stack is empty
 * @param stack
 * @returns true if stack is empty and false otherwise
 */
bool stack_is_empty(stack_t *stack);

/** 
 * Adds element to top of stack
 * @param stack
 * @param element to add
 */
void stack_push(stack_t *stack, void *element);

/**
 * Views element at top of stack
 * @param stack
 * @returns element at top of stack
 */
void *stack_peek(stack_t *stack);

/**
 * Removes element at top of stack
 * @param stack
 * @returns removed element
 */
void *stack_pop(stack_t *stack);

#endif