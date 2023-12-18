#ifndef HASH_TABLE
#define HASH_TABLE

#include <stdio.h>
#include <stdbool.h>
#include "function_types.h"

/** Node for hash table */
typedef struct key_value key_value_t;

/** Doubly hash table struct */
typedef struct hash_table hash_table_t;

/** 
 * Initializes hash table
 * @return newly initialized hash table
 */
hash_table_t *hash_table_init(size_t key_size);

/** 
 * Initializes hash table with custom equals function and freers
 * @return newly initialized hash table
 */
hash_table_t *hash_table_equals_init(size_t key_size, equals_t equals_func, free_t key_freer, free_t value_freer);

/** 
 * Frees hash table
 * @param ht
 */
void hash_table_free(hash_table_t *ht);

/**
 * Returns size of list
 * @param ht
 * @returns size of list
 */
size_t hash_table_size(hash_table_t *ht);

/** 
 * Adds key value pair to hash table
 * @param ht
 * @param key
 * @param value
 * @returns old value entry if key is already in dict, else NULL
 */
void *hash_table_put(hash_table_t *ht, void *key, void *value);

/**
 * Retrieves value corresponding to key in hash table
 * @param ht
 * @param key of value
 * @returns value corresponding to key
 */
void *hash_table_get(hash_table_t *ht, void *key);

/**
 * Removes element at index from hash table
 * @param ht
 * @param index to remove
 * @returns removed element
 */
void *hash_table_remove(hash_table_t *ht, void *key);

#endif