#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "tree_set.h"

void test_init() {
    tree_set_t *set = tree_set_init();
    assert(set != NULL);
    assert(tree_set_size(set) == 0);
    tree_set_free(set);
    printf("test_init passed\n");
}

void test_filling_set() {
    tree_set_t *set = tree_set_init();
    for (size_t i = 2; i < 32; i+=3) {
        size_t *num = malloc(sizeof(*num));
        *num = i % 10;
        tree_set_add(set, num);
    }

    // test correct size
    assert(tree_set_size(set) == 10);

    // test that each number from 0 - 9 is contained in the set
    for (size_t i = 0; i < 10; i++) {
        size_t *num = malloc(sizeof(*num));
        *num = i;
        assert(tree_set_contains(set, num));
        free(num);
    }

    // test that 10 should not be in the set
    size_t bad_num = 10; 
    assert(!tree_set_contains(set, &bad_num));

    // test freeing works properly
    tree_set_free(set);
    printf("test_filling_set passed\n");
}

void test_repeat_add1() {
    tree_set_t *set = tree_set_init();

    // try adding 1 ten times
    for (size_t i = 0; i < 10; i ++) {
        size_t *num = malloc(sizeof(*num));
        *num = 1;
        tree_set_add(set, num);
        if (i > 0) {
            free(num);
        }
    }

    // check that size is still only one
    assert(tree_set_size(set) == 1);

    // check that the only number contained is 1
    size_t one = 1;
    assert(tree_set_contains(set, &one));

    tree_set_free(set);
    printf("test_repeat_add1 passed\n");
}

void test_repeat_add2() {
    tree_set_t *set = tree_set_init();

    // try adding several numbers between 0 - 9
    for (size_t i = 2; i < 102; i+=3) {
        size_t *num = malloc(sizeof(*num));
        *num = i % 10;
        tree_set_add(set, num);
        if (i >= 32) {
            free(num);
        }
    }

    // check that size is 10
    assert(tree_set_size(set) == 10);

    tree_set_free(set);
    printf("test_repeat_add2 passed\n");
}

void test_remove() {
    tree_set_t *set = tree_set_init();

    // try adding several numbers between 0 - 9
    for (size_t i = 2; i < 102; i+=3) {
        size_t *num = malloc(sizeof(*num));
        *num = i % 10;
        tree_set_add(set, num);
        if (i >= 32) {
            free(num);
        }
    }

    // try removing a leaf
    size_t num = 1;
    size_t *ptr = tree_set_remove(set, &num);
    free(ptr);

    // check that size is 9
    assert(tree_set_size(set) == 9);

    // try removing a node with two children
    num = 8;
    ptr = tree_set_remove(set, &num);
    free(ptr);

    // check that size is 8
    assert(tree_set_size(set) == 8);

    // try removing the root
    num = 2;
    ptr = tree_set_remove(set, &num);
    free(ptr);

    // check that size is 7
    assert(tree_set_size(set) == 7);

    tree_set_free(set);
    printf("test_remove passed\n");
}

int main() {
    printf("Running set tests...\n");
    test_init();
    test_filling_set();
    test_repeat_add1();
    test_repeat_add2();
    test_remove();
    printf("ALL SET TESTS PASSED...\n\n");
}