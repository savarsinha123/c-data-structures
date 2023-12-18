#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "queue.h"

void test_init() {
    queue_t *queue = queue_init();
    assert(queue != NULL);
    assert(queue_size(queue) == 0);
    queue_free(queue);
    printf("test_init passed\n");
}

void test_one_thru_ten() {
    queue_t *queue = queue_init();
    for (size_t i = 0; i < 10; i++) {
        size_t *num = malloc(sizeof(*num));
        *num = i;
        queue_add(queue, num);
    }

    // test correct size
    assert(queue_size(queue) == 10);

    // test peek works correctly
    assert(*(size_t *) queue_peek(queue) == 0);

    // test equivalence for each element in the list
    for (size_t i = 0; i < 10; i++) {
        size_t *num = queue_poll(queue);
        assert(i == *num);
        free(num);
    }

    // test freeing works properly
    queue_free(queue);
    printf("test_one_thru_ten passed\n");
}

int main() {
    printf("Running queue tests...\n");
    test_init();
    test_one_thru_ten();
    printf("ALL QUEUE TESTS PASSED...\n\n");
}