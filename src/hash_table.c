#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "hash_table.h"

// sizes to resize array to
// primes chosen to minimize collisions
const size_t SIZES[28] = {31, 61, 127, 251, 509, 1021, 2039, 4093,
                        8191, 16381, 32749, 65521, 131071, 262139,
                        524287, 1048573, 2097143, 4194299, 8388593,
                        16777199, 33554393, 67108859, 134217727, 268435453,
                        536870909, 1073741827, 2147483647, 4294967291};
const size_t STEP_SIZE = 1;

#define CAPACITY_BYTES SIZES[ht->capacity_index] * sizeof(key_value_t *)

typedef struct key_value {
    void *key;
    void *value;
} key_value_t;

typedef struct hash_table {
    key_value_t **table;
    size_t size;
    size_t capacity_index;
    size_t key_size; // num bytes of key type
    equals_t equals;
    hash_t hasher;
    free_t key_freer;
    free_t value_freer;
} hash_table_t;

bool equals(int *a, int *b) {
    return *a == *b;
}

size_t hash(void *key, size_t key_size) {
    const unsigned char *key_str = (const unsigned char *) key;
    size_t hash = 5381; // Initial hash value
    for (size_t i = 0; i < key_size; ++i) {
        hash = (hash * 33) ^ key_str[i];
    }
    return hash;
}

key_value_t *key_value_init(void *key, void *value) {
    key_value_t *key_value = malloc(sizeof(key_value_t));
    key_value->key = key;
    key_value->value = value;
    return key_value;
}

hash_table_t *hash_table_equals_init(size_t key_size, equals_t equals_func, hash_t hash_func,
                                    free_t key_freer, free_t value_freer) {
    hash_table_t *ht = malloc(sizeof(hash_table_t));
    ht->size = 0;
    ht->capacity_index = 0;
    ht->equals = equals_func;
    ht->key_size = key_size;
    ht->table = calloc(SIZES[ht->capacity_index], sizeof(key_value_t *));
    ht->hasher = hash_func;
    ht->key_freer = key_freer;
    ht->value_freer = value_freer;
    return ht;
}

hash_table_t *hash_table_init(size_t key_size) {
    return hash_table_equals_init(key_size, (equals_t) equals, hash, free, free);
}

void hash_table_free(hash_table_t *ht) {
    for (size_t i = 0; i < SIZES[ht->capacity_index]; i ++) {
        if (ht->table[i] != NULL) {
            ht->key_freer(ht->table[i]->key);
            ht->value_freer(ht->table[i]->value);
            free(ht->table[i]);
        }
    }
    free(ht->table);
    free(ht);
}

size_t hash_table_size(hash_table_t *ht) {
    return ht->size;
}

void resize(hash_table_t *ht) {
    key_value_t **copy = malloc(CAPACITY_BYTES);
    memcpy(copy, ht->table, CAPACITY_BYTES);
    ht->capacity_index++;
    ht->table = realloc(ht->table, CAPACITY_BYTES);
    memset(ht->table, 0, CAPACITY_BYTES);

    // rehashing
    for (size_t i = 0; i < ht->size; i++) {
        key_value_t *key_value = copy[i];
        size_t hash_key = ht->hasher(key_value->key, ht->key_size) % SIZES[ht->capacity_index];
        while (ht->table[hash_key] != NULL) {
            hash_key = (hash_key + STEP_SIZE) % SIZES[ht->capacity_index];
        }
        ht->table[hash_key] = key_value;
    }
    free(copy);
}

int64_t hash_table_get_index(hash_table_t *ht, void *key) {
    size_t loop_counter = 0;
    size_t hash_key = ht->hasher(key, ht->key_size) % SIZES[ht->capacity_index];
    while (ht->table[hash_key] == NULL || !ht->equals(key, ht->table[hash_key]->key)) {
        if (loop_counter >= SIZES[ht->capacity_index]) {
            break;
        }
        hash_key = (hash_key + STEP_SIZE) % SIZES[ht->capacity_index];
        loop_counter++;
    }
    if (loop_counter >= SIZES[ht->capacity_index]) {
        return -1;
    }
    return hash_key;
}

bool hash_table_contains_key(hash_table_t *ht, void *key) {
    return hash_table_get_index(ht, key) >= 0;
} 

void *hash_table_put(hash_table_t *ht, void *key, void *value) {
    if (ht->size >= SIZES[ht->capacity_index]) {
        resize(ht);
    }

    // create copy of key since keys are immutable
    void *key_copy = malloc(ht->key_size);
    memcpy(key_copy, key, ht->key_size);
    key_value_t *key_value = key_value_init(key_copy, value);

    // perform linear probing
    size_t hash_key = ht->hasher(key, ht->key_size) % SIZES[ht->capacity_index];
    while (ht->table[hash_key] != NULL && !ht->equals(key, ht->table[hash_key]->key)) {
        hash_key = (hash_key + STEP_SIZE) % SIZES[ht->capacity_index];
    }
    if (ht->table[hash_key] != NULL) {
        void *old_value = ht->table[hash_key]->value;
        ht->table[hash_key]->value = value;
        free(key_value->key);
        free(key_value);
        return old_value;
    }
    ht->table[hash_key] = key_value;
    ht->size++;
    return NULL;
}

void *hash_table_get(hash_table_t *ht, void *key) {
    int64_t index = hash_table_get_index(ht, key);
    assert(index != -1); // checks that the value is actually contained
    return ht->table[index]->value;
}

void *hash_table_remove(hash_table_t *ht, void *key) {
    int64_t index = hash_table_get_index(ht, key);
    assert(index != -1); // checks that the value is actually contained
    void *to_return = ht->table[index]->value;
    ht->key_freer(ht->table[index]->key);
    free(ht->table[index]);
    ht->table[index] = NULL;
    ht->size--;
    return to_return;
}
