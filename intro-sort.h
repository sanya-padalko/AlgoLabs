#ifndef __INTRO_SORT_H_
#define __INTRO_SORT_H_

#include <stdlib.h>
#include <stdio.h>
#include "small-sortings.h"
#include "part-sortings.h"

int max_deep = 1;

static int get_log(int n) {
    int ans = 1;
    while (n > 1) {
        n /= 2;
        ++ans;
    }

    return ans;
}

static void RecIntro_sort(unsigned int* arr, int l, int r, 
                            int (*pivot_selector)(unsigned int*, int, int), 
                            int (*partition)(unsigned int*, int, int, int), int deep) {
    if (l >= r) 
        return;

    if ((r - l + 1) <= block_size) {
        Insert_sort(arr + l, r - l + 1);
        return;
    }

    if (deep == max_deep) {
        K_HEAP = 4;
        Bottom_up_heap_sort(arr + l, r - l + 1);
        return;
    }

    int pivot = pivot_selector(arr, l, r);
    int gr = partition(arr, l, r, pivot);

    RecIntro_sort(arr, l, gr, pivot_selector, partition, deep + 1);
    RecIntro_sort(arr, gr + 1, r, pivot_selector, partition, deep + 1);
}

static void Intro_sort(unsigned int* arr, int size) {
    block_size = 64;
    max_deep *= get_log(size);
    RecIntro_sort(arr, 0, size - 1, pivot_central, hoar_part, 0);
    max_deep /= get_log(size);
}

#endif
