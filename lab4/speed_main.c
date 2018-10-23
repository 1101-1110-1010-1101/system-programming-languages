#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include "linked_list.h"

int main(int argc, char *argv[]) {
    int i;
    element* list1000 = NULL;
    element* list50 = NULL;
    element* list5 = NULL;
    for (i = 0; i < 1000; i++) {
        list_add_back(i, &list1000);
        if (i < 50)
            list_add_back(i, &list50);
        if (i < 5)
            list_add_back(i, &list5);
    }

    printf("%d\n", list_sum(list1000));

    clock_t add_back_1000_begin = clock();
    list_add_back(20, &list1000);
    clock_t add_back_1000_end = clock();
    double add_back_1000_time = (double) (add_back_1000_end - add_back_1000_begin);
    printf("list_add_back_1000: %.15fns\n", add_back_1000_time);

    clock_t add_middle_1000_begin = clock();
    list_add_by_index(20, &list1000, 500);
    clock_t add_middle_1000_end = clock();
    double add_middle_1000_time = (double) (add_middle_1000_end - add_middle_1000_begin);
    printf("list_add_middle_1000: %.15fns\n", add_middle_1000_time);

    clock_t add_front_1000_begin = clock();
    list_add_front(20, &list1000);
    clock_t add_front_1000_end = clock();
    double add_front_1000_time = (double) (add_front_1000_end - add_front_1000_begin);
    printf("list_add_front_1000: %.15fns\n", add_front_1000_time);

    clock_t add_back_50_begin = clock();
    list_add_back(20, &list50);
    clock_t add_back_50_end = clock();
    double add_back_50_time = (double) (add_back_50_end - add_back_50_begin);
    printf("list_add_back_50: %.15fns\n", add_back_50_time);

    clock_t add_middle_50_begin = clock();
    list_add_by_index(20, &list50, 25);
    clock_t add_middle_50_end = clock();
    double add_middle_50_time = (double) (add_middle_50_end - add_middle_50_begin);
    printf("list_add_middle_50: %.15fns\n", add_middle_50_time);

    clock_t add_front_50_begin = clock();
    list_add_front(20, &list50);
    clock_t add_front_50_end = clock();
    double add_front_50_time = (double) (add_front_50_end - add_front_50_begin);
    printf("list_add_front_50: %.15fns\n", add_front_50_time);

    clock_t add_back_5_begin = clock();
    list_add_back(20, &list5);
    clock_t add_back_5_end = clock();
    double add_back_5_time = (double) (add_back_5_end - add_back_5_begin);
    printf("list_add_back_5: %.15fns\n", add_back_5_time);

    clock_t add_middle_5_begin = clock();
    list_add_by_index(20, &list5, 2);
    clock_t add_middle_5_end = clock();
    double add_middle_5_time = (double) (add_middle_5_end - add_middle_5_begin);
    printf("list_add_middle_5: %.15fns\n", add_middle_5_time);

    clock_t add_front_5_begin = clock();
    list_add_front(20, &list5);
    clock_t add_front_5_end = clock();
    double add_front_5_time = (double) (add_front_5_end - add_front_5_begin);
    printf("list_add_front_5: %.15fns\n", add_front_5_time);
}