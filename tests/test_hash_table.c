#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "hash_table.h"
#include "tree_set.h"

const double PI = 3.14159265359;
const size_t HASH_BYTES = 8;

typedef struct example {
    int a;
    double b;
    char c;
    tree_set_t *d;
} example_t;

example_t *example_init(int64_t value) {
    example_t *example = malloc(sizeof(example_t));
    example->a = value;
    example->b = value * PI;
    example->c = value;
    example->d = tree_set_init();
    size_t *value1 = malloc(sizeof(size_t)); 
    *value1 = value - 1;
    size_t *value2 = malloc(sizeof(size_t)); 
    *value2 = value;
    size_t *value3 = malloc(sizeof(size_t)); 
    *value3 = value + 1;
    tree_set_add(example->d, value1);
    tree_set_add(example->d, value2);
    tree_set_add(example->d, value3);
    return example;
}

bool example_equals(example_t *example1, example_t *example2) {
    return example1->a == example2->a;
}

size_t example_hash(example_t *example, size_t _) {
    const unsigned char *key_str = (const unsigned char *) example;
    size_t hash = 5381; // Initial hash value
    for (size_t i = 0; i < HASH_BYTES; ++i) {
        hash = (hash * 33) ^ key_str[i];
    }
    return hash;
}

void example_free(example_t *example) {
    tree_set_free(example->d);
    free(example);
}

void test_init() {
    hash_table_t *ht = hash_table_init(sizeof(int));
    assert(ht != NULL);
    assert(hash_table_size(ht) == 0);
    hash_table_free(ht);
    printf("test_init passed\n");
}

void test_put_get() {
    hash_table_t *ht = hash_table_init(sizeof(size_t));
    for (size_t i = 0; i < 10; i ++) {
        size_t *num = malloc(sizeof(*num));
        *num = i;
        char *c = malloc(sizeof(*c));
        *c = 'a' + i;
        hash_table_put(ht, num, c);
        free(num);
    }
    
    // check size updates properly
    assert(hash_table_size(ht) == 10);

    // check retrieval
    size_t num = 1;
    char letter = *(char *) hash_table_get(ht, &num);
    assert(letter == 'b');

    num = 7;
    letter = *(char *) hash_table_get(ht, &num);
    assert(letter == 'h');

    hash_table_free(ht);
    printf("test_put_get passed\n");
}

void test_update_entry() {
    hash_table_t *ht = hash_table_init(sizeof(size_t));
    for (size_t i = 0; i < 10; i ++) {
        size_t *num = malloc(sizeof(*num));
        *num = i;
        char *c = malloc(sizeof(*c));
        *c = 'a' + i;
        hash_table_put(ht, num, c);
        free(num);
    }
    assert(hash_table_size(ht) == 10);

    // update hash table entry
    size_t num = 4;
    char letter = 'L';
    free(hash_table_put(ht, &num, &letter));
    assert(hash_table_size(ht) == 10);

    char *letter_retrieved = hash_table_remove(ht, &num);
    assert(*letter_retrieved == 'L');
    hash_table_free(ht);
    printf("test_update_entry passed\n");
}

void test_remove() {
    hash_table_t *ht = hash_table_init(sizeof(size_t));
    for (size_t i = 0; i < 10; i ++) {
        size_t *num = malloc(sizeof(*num));
        *num = i;
        char *c = malloc(sizeof(*c));
        *c = 'a' + i;
        hash_table_put(ht, num, c);
        free(num);
    }

    // check that correct letter is removed
    size_t num = 2;
    char *letter = hash_table_remove(ht, &num);
    assert(*letter == 'c');
    free(letter);

    // check that size has been updated accordingly
    assert(hash_table_size(ht) == 9);
    hash_table_free(ht);
    printf("test_remove passed\n");
}

void test_struct_key() {
    hash_table_t *ht = hash_table_equals_init(sizeof(example_t), (equals_t) example_equals, 
                        (hash_t) example_hash, (free_t) example_free, free);
    for (int i = 10; i < 20; i ++) {
        example_t *example = example_init(i);
        char *c = malloc(sizeof(*c));
        *c = 'a' + i - 10;
        hash_table_put(ht, example, c);
        free(example);
    }
    assert(hash_table_size(ht) == 10);

    // try to retrieve a value
    example_t *example = example_init(10);
    char *c = hash_table_get(ht, example);
    assert(*c == 'a');

    // try updating a value
    c = malloc(sizeof(*c));
    *c = 'X';
    free(hash_table_put(ht, example, c));
    assert(hash_table_size(ht) == 10);
    c = hash_table_get(ht, example);
    assert(*c == 'X');

    // try removing a value
    free(hash_table_remove(ht, example));
    assert(hash_table_size(ht) == 9);

    example_free(example);
    hash_table_free(ht);
    printf("test_struct_key passed\n");
}

int main() {
    printf("Running hash table tests...\n");
    test_init();
    test_put_get();
    test_update_entry();
    test_remove();
    test_struct_key();
    printf("ALL HASH TABLE TESTS PASSED...\n\n");
}