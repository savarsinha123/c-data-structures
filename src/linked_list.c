#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

// typedef void (*free_t)(void *);

typedef struct node {
    void *data;
    node_t *prev;
    node_t *next;
} node_t;

typedef struct linked_list {
    node_t *head;
    node_t *tail;
    size_t size;
    free_t freer;
} linked_list_t;

node_t *node_init(void *data, node_t *prev, node_t *next) {
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    node->prev = prev;
    node->next = next;
    return node;
}

linked_list_t *linked_list_free_init(free_t freer) {
    linked_list_t *list = malloc(sizeof(linked_list_t));
    assert(list != NULL); // checks memory is allocated properly
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->freer = freer;
    return list;
}

linked_list_t *linked_list_init() {
    return linked_list_free_init(free);
}

void node_free(node_t *node, free_t freer) {
    // recursively frees nodes
    if (node->next != NULL) {
        node_free(node->next, freer);
    }
    freer(node->data);
    free(node);
}

void linked_list_free(linked_list_t *list) {
    if (list->head != NULL) {
        node_free(list->head, list->freer);
    }
    free(list);
}

size_t linked_list_size(linked_list_t *list) {
    return list->size;
}

void linked_list_add(linked_list_t *list, void *element) {
    if (list->head == NULL) {
        list->head = node_init(element, NULL, NULL);
        list->tail = list->head;
    }
    else {
        node_t *old_tail = list->tail;
        list->tail = node_init(element, old_tail, NULL);
        old_tail->next = list->tail;
    }
    list->size++;
}

void *linked_list_get(linked_list_t *list, size_t index) {
    assert(index < list->size); // check index within list
    node_t *curr;

    // choose which end to search from
    if (index < list->size / 2) {
        curr = list->head;
        for (size_t i = 0; i < index; i++) {
            curr = curr->next;
        }
    }
    else {
        curr = list->tail;
        for (size_t i = 0; i < list->size - index - 1; i++) {
            curr = curr->prev;
        }
    }
    return curr->data;
}

void *linked_list_remove(linked_list_t *list, size_t index) {
    assert(index < list->size); // check index within list
    node_t *curr;
    if (index < list->size / 2) {
        curr = list->head;
        for (size_t i = 0; i < index; i++) {
            curr = curr->next;
        }
    }
    else {
        curr = list->tail;
        for (size_t i = 0; i < list->size - index - 1; i++) {
            curr = curr->prev;
        }
    }

    // checks if not head
    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
    }
    else {
        list->head = list->head->next;
    }

    // checks if not tail
    if (curr->next != NULL) {
        curr->next->prev = curr->prev;
    }
    else {
        list->tail = list->tail->prev;
    }
    void *data = curr->data;
    free(curr);
    list->size--;
    return data;
}
