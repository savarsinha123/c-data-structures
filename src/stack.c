#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct stack {
    linked_list_t *list;
} stack_t;

stack_t *stack_init() {
    stack_t *stack = malloc(sizeof(stack_t));
    assert(stack != NULL); // check that memory has been allocated
    stack->list = linked_list_init();
    return stack;
}

void stack_free(stack_t *stack) {
    linked_list_free(stack->list);
    free(stack);
}

size_t stack_size(stack_t *stack) {
    return linked_list_size(stack->list);
}

bool stack_is_empty(stack_t *stack) {
    return linked_list_size(stack->list) == 0;
}

void stack_push(stack_t *stack, void *element) {
    linked_list_add(stack->list, element);
}

void *stack_peek(stack_t *stack) {
    return linked_list_get(stack->list, linked_list_size(stack->list) - 1);
}

void *stack_pop(stack_t *stack) {
    return linked_list_remove(stack->list, linked_list_size(stack->list) - 1);
}