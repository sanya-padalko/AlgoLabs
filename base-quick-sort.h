#ifndef __BASE_QUICK_SORT_H_
#define __BASE_QUICK_SORT_H_

#include <stdio.h>
#include <stdlib.h>

static int comp(void const *a, void const *b) {
    if (*(const unsigned int*)a < *(const unsigned int*)b)
        return -1;

    return 1;
}

static void BaseQuick_sort(unsigned int* arr, int size) {
    qsort(arr, size, sizeof(int), comp);
}

#endif