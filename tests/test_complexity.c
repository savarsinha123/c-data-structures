#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "linked_list.h"
#include "tree_set.h"
#include "hash_table.h"
#include <math.h>

void linked_list_complexity() {
    clock_t start, end;
    double cpu_time_used;
    linked_list_t *list = linked_list_init();
    
    // list_get and list_add
    FILE *add_file = fopen("list_add.csv", "w");
    FILE *get_file = fopen("list_get.csv", "w");
    for (size_t i = 0; i < 10000; i ++) {
        size_t *num = malloc(sizeof(size_t));
        *num = i;

        // test list_add
        start = clock();
        linked_list_add(list, num);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(add_file, "%f\n", cpu_time_used);

        // test list_get
        start = clock();
        linked_list_get(list, i / 2);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(get_file, "%f\n", cpu_time_used);
    }
    fclose(add_file);
    fclose(get_file);

    // list_remove
    double cpu_time_remove[10000];
    FILE *remove_file = fopen("list_remove.csv", "w");
    for (size_t i = 0; i < 10000; i ++) {
        size_t index = (10000 - i) / 2;
        start = clock();
        void *removed = linked_list_remove(list, index);
        end = clock();
        free(removed);
        cpu_time_remove[9999 - i] = ((double) (end - start)) / CLOCKS_PER_SEC;
    }
    for (size_t i = 0; i < 10000; i++) {
        fprintf(remove_file, "%f\n", cpu_time_remove[i]);
    }
    linked_list_free(list);
}

double compare_double(double *a, double *b) {
    // if (fabs(*a - *b) < 1e-7) {
    //     return 0;
    // }
    return *a - *b;
}

void tree_set_complexity() {
    const size_t NUM_ITEMS = 150000;
    clock_t start, end;
    double cpu_time_used;
    tree_set_t *set = tree_set_comp_init((compar_t) compare_double, free);
    
    FILE *add_file = fopen("set_add.csv", "w");
    FILE *contains_file = fopen("set_contains.csv", "w");
    for (double i = 0; i < NUM_ITEMS; i ++) {
        double *num = malloc(sizeof(double));
        *num = sin(i);

        // test set_add
        start = clock();
        tree_set_add(set, num);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(add_file, "%f\n", cpu_time_used);

        // test set_contains
        start = clock();
        tree_set_contains(set, num);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(contains_file, "%f\n", cpu_time_used);
    }
    fclose(add_file);
    fclose(contains_file);

    // set_remove
    linked_list_t *list = tree_set_to_list(set);
    size_t total_size = linked_list_size(list);
    double cpu_time_remove[total_size];
    FILE *remove_file = fopen("set_remove.csv", "w");
    assert(linked_list_size(list) == tree_set_size(set));
    for (size_t i = 0; i < total_size; i ++) {
        double *num = linked_list_get(list, i);
        start = clock();
        void *removed = tree_set_remove(set, num);
        end = clock();
        free(removed);
        cpu_time_remove[total_size - i - 1] = ((double) (end - start)) / CLOCKS_PER_SEC;
    }
    for (size_t i = 0; i < total_size / 2; i++) {
        fprintf(remove_file, "%f\n", cpu_time_remove[i]);
    }
    linked_list_free(list);
    tree_set_free(set);
}

void hash_table_complexity() {
    const size_t NUM_ITEMS = 100000;
    clock_t start, end;
    double cpu_time_used;
    hash_table_t *ht = hash_table_init(sizeof(size_t));
    
    FILE *add_file = fopen("hash_table_put.csv", "w");
    FILE *get_file = fopen("hash_table_get.csv", "w");
    for (size_t i = 0; i < NUM_ITEMS; i ++) {
        size_t *key = malloc(sizeof(size_t));
        size_t *value = malloc(sizeof(size_t));
        *key = (i + 31) % NUM_ITEMS;
        *value = *key;

        // test hash_table_put
        start = clock();
        hash_table_put(ht, key, value);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(add_file, "%f\n", cpu_time_used);

        // test hash_table_get
        start = clock();
        hash_table_get(ht, key);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(get_file, "%f\n", cpu_time_used);
        free(key);
    }
    fclose(add_file);
    fclose(get_file);

    // set_remove
    FILE *remove_file = fopen("hash_table_remove.csv", "w");
    for (size_t i = 0; i < NUM_ITEMS; i ++) {
        size_t *key = malloc(sizeof(size_t));
        *key = (i + 31) % NUM_ITEMS;
        start = clock();
        size_t *value = hash_table_remove(ht, key);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(remove_file, "%f\n", cpu_time_used);
        free(value);
        free(key);
    }
    hash_table_free(ht);
}

int main() {
    linked_list_complexity();
    tree_set_complexity();
    hash_table_complexity();
    printf("Complexity calculations finished\n\n");
    return 0;
}