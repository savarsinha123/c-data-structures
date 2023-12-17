#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

int main() {
    clock_t start, end;
    double cpu_time_used;
    linked_list_t *list = linked_list_init();

    start = clock();
    
    // Call your function here
    FILE *add_file = fopen("list_add.csv", "w");
    FILE *get_file = fopen("list_get.csv", "w");
    for (size_t i = 0; i < 10000; i ++) {
        size_t *num = malloc(sizeof(size_t));
        *num = i;
        linked_list_add(list, num);
        end = clock();
        cpu_time_used = ((double) (end - start));
        // printf("add execution Time: %f seconds\n", cpu_time_used);
        // fprintf(add_file, "%f\n", cpu_time_used);
        start = end;
        linked_list_get(list, i / 2);
        end = clock();
        cpu_time_used = ((double) (end - start));
        // printf("add execution Time: %f seconds\n", cpu_time_used);
        fprintf(get_file, "%f\n", cpu_time_used);
        start = end;
    }
    fclose(add_file);
    fclose(get_file);

    // file = fopen("list_get.csv", "w");
    // for (size_t i = 0; i < 50000; i ++) {
    //     linked_list_get(list, i);
    //     end = clock();
    //     cpu_time_used = ((double) (end - start));
    //     // printf("get execution Time: %f seconds\n", cpu_time_used);
    //     fprintf(file, "%f\n", cpu_time_used);
    //     start = end;
    // }
    // fclose(file);

    linked_list_free(list);
    return 0;
}