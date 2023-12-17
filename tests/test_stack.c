#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

void test_init() {
    stack_t *stack = stack_init();
    assert(stack != NULL);
    assert(stack_size(stack) == 0);
    stack_free(stack);
    printf("test_init passed\n");
}

void test_one_thru_ten() {
    stack_t *stack = stack_init();
    for (size_t i = 0; i < 10; i++) {
        size_t *num = malloc(sizeof(*num));
        *num = i;
        stack_push(stack, num);
    }

    // test correct size
    assert(stack_size(stack) == 10);

    // test peek works correctly
    assert(*(size_t *) stack_peek(stack) == 9);

    // test equivalence for each element in the list
    for (size_t i = 0; i < 10; i++) {
        size_t *num = stack_pop(stack);
        assert(9 - i == *num);
        free(num);
    }

    // test freeing works properly
    stack_free(stack);
    printf("test_one_thru_ten passed\n");
}

int main() {
    printf("Running stack tests...\n");
    test_init();
    test_one_thru_ten();
    printf("ALL STACK TESTS PASSED...\n\n");
}