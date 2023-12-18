#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

typedef struct queue {
    linked_list_t *list;
} queue_t;

queue_t *queue_init() {
    queue_t *queue = malloc(sizeof(queue_t));
    assert(queue != NULL); // check that memory has been allocated
    queue->list = linked_list_init();
    return queue;
}

void queue_free(queue_t *queue) {
    linked_list_free(queue->list);
    free(queue);
}

size_t queue_size(queue_t *queue) {
    return linked_list_size(queue->list);
}

bool queue_is_empty(queue_t *queue) {
    return linked_list_size(queue->list) == 0;
}

void queue_add(queue_t *queue, void *element) {
    linked_list_add(queue->list, element);
}

void *queue_peek(queue_t *queue) {
    return linked_list_get(queue->list, 0);
}

void *queue_poll(queue_t *queue) {
    return linked_list_remove(queue->list, 0);
}