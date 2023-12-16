#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "linked_list.h"

void test_init() {
    linked_list_t *list = linked_list_init();
    assert(list != NULL);
    assert(linked_list_size(list) == 0);
    linked_list_free(list);
    printf("test_init passed\n");
}

void test_one_thru_ten() {
    linked_list_t *list = linked_list_init();
    for (size_t i = 0; i < 10; i++) {
        size_t *num = malloc(sizeof(*num));
        *num = i;
        linked_list_add(list, num);
    }

    // test correct size
    assert(linked_list_size(list) == 10);

    // test equivalence for each element in the list
    for (size_t i = 0; i < 10; i++) {
        size_t num = *(size_t *) linked_list_get(list, i);
        assert(i == num);
    }

    // test freeing works properly
    linked_list_free(list);
    printf("test_one_thru_ten passed\n");
}

void test_remove() {
    linked_list_t *list = linked_list_init();
    for (size_t i = 0; i < 10; i++) {
        size_t *num = malloc(sizeof(*num));
        *num = i;
        linked_list_add(list, num);
    }
    for (int i = 8; i >= 0; i -= 2) {
        size_t *removed = linked_list_remove(list, i);
        assert(*removed == i);
        free(removed);
    }

    // test correct size
    assert(linked_list_size(list) == 5);

    // test freeing works properly
    linked_list_free(list);
    printf("test_remove passed\n");
}

void test_remove_one() {
    linked_list_t *list = linked_list_init();
    size_t i = 1;
    linked_list_add(list, &i);

    // test stored correctly
    assert(*(size_t *) linked_list_get(list, 0) == i);
    assert(linked_list_size(list) == 1);

    // check removal works correctly
    linked_list_remove(list, 0);
    assert(linked_list_size(list) == 0);

    // test readding
    i = 2;
    linked_list_add(list, &i);
    assert(*(size_t *) linked_list_get(list, 0) == i);
    assert(linked_list_size(list) == 1);
    linked_list_remove(list, 0);

    // test freeing works properly
    linked_list_free(list);
    printf("test_remove_one passed\n");
}

int main() {
    printf("Running list tests...\n");
    test_init();
    test_one_thru_ten();
    test_remove();
    test_remove_one();
    printf("ALL TESTS PASSED...\n");
}