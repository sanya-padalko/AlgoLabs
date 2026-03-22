#ifndef __PART_SORTINGS_H_
#define __PART_SORTINGS_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "small-sortings.h"

static int pivot_central(unsigned int* arr, int l, int r) {
    return (l + r) / 2;
}

static int pivot_mediana3(unsigned int* arr, int l, int r) {
    int mid = (l + r) / 2;

    if (arr[l] > arr[mid])
        swap(arr + l, arr + mid, sizeof(int));

    if (arr[l] > arr[r])
        swap(arr + l, arr + r, sizeof(int));

    if (arr[mid] > arr[r]) 
        swap(arr + mid, arr + r, sizeof(int));

    return mid;
}

static int pivot_random(unsigned int* arr, int l, int r) {
    if ((r - l + 1) <= 0)
        return l;

    srand(time(NULL));

    int rand_num = rand() % (r - l + 1);
    return l + rand_num;
}

static int pivot_random_med(unsigned int* arr, int l, int r) {
    if ((r - l + 1) <= 0)
        return l;

    srand(time(NULL));

    int rand1 = l + rand() % (r - l + 1);
    int rand2 = l + rand() % (r - l + 1);
    int rand3 = l + rand() % (r - l + 1);
    if (arr[rand1] > arr[rand2])
        swap(arr + rand1, arr + rand2, sizeof(int));

    if (arr[rand2] > arr[rand3])
        swap(arr + rand2, arr + rand3, sizeof(int));

    if (arr[rand1] > arr[rand3]) 
        swap(arr + rand1, arr + rand3, sizeof(int));

    return rand2;
}

static int hoar_part(unsigned int* arr, int l, int r, int pivot_ind) {
    int i = l;
    int j = r;
    unsigned int pivot = arr[pivot_ind];
    while (1) {
        while (i <= r && arr[i] < pivot)
            ++i;
        while (j >= l && arr[j] > pivot)
            --j;

        if (i >= j)
            return j;

        swap(arr + i, arr + j, sizeof(int));
        ++i;
        --j;
    }
}

static int lomuto_part(unsigned int* arr, int l, int r, int pivot_ind) {
    unsigned int pivot = arr[pivot_ind];
    swap(arr + r, arr + pivot_ind, sizeof(int));

    int ind = l - 1;
    for (int i = l; i < r; ++i) {
        if (arr[i] <= pivot) {
            ++ind;

            swap(arr + i, arr + ind, sizeof(int));
        }
    }

    swap(arr + r, arr + ind + 1, sizeof(int));

    return ind + 1;
}

unsigned int *left_eq = NULL;
unsigned int *right_eq = NULL;

static int thick_part(unsigned int* arr, int l, int r, int pivot_ind) {
    unsigned int pivot = arr[pivot_ind];
    int lq = l;
    int eq = l;
    int rq = r;

    while (eq <= rq) {
        if (arr[eq] < pivot) {
            swap(arr + lq, arr + eq, sizeof(int));
            ++lq;
            ++eq;
        }
        else if (arr[eq] == pivot) {
            ++eq;
        }
        else {
            swap(arr + rq, arr + eq, sizeof(int));
            --rq;
        }
    }

    *left_eq = lq - 1;
    *right_eq = rq + 1;

    return lq;
}

static void Quick_sort(unsigned int* arr, int l, int r, 
                            int (*pivot_selector)(unsigned int*, int, int), 
                            int (*partition)(unsigned int*, int, int, int)) {
    if (l >= r)
        return;

    if ((r - l + 1) <= 32) {
        Insert_sort(arr + l, r - l + 1);
        return;
    }

    int pivot = pivot_selector(arr, l, r);
    int gr = partition(arr, l, r, pivot);
    if (left_eq && right_eq) {
        Quick_sort(arr, l, *left_eq, pivot_selector, partition);
        Quick_sort(arr, *right_eq, r, pivot_selector, partition);
        return;
    }

    if (gr == r) --gr;
    if (gr < l) gr = l;

    Quick_sort(arr, l, gr, pivot_selector, partition);
    Quick_sort(arr, gr + 1, r, pivot_selector, partition);
}

int (*hoar_pivot)(unsigned int*, int, int) = pivot_central;

static void Hoar_sort(unsigned int* arr, int size)  {
    left_eq = right_eq = NULL;
    Quick_sort(arr, 0, size - 1, hoar_pivot, hoar_part);
}

static void Lomuto_sort(unsigned int* arr, int size) {
    left_eq = right_eq = NULL;
    Quick_sort(arr, 0, size - 1, pivot_central, lomuto_part);
}

static void Thick_sort(unsigned int* arr, int size) {
    left_eq = (unsigned int*)calloc(1, sizeof(int));
    right_eq = (unsigned int*)calloc(1, sizeof(int));
    Quick_sort(arr, 0, size - 1, pivot_central, thick_part);
    free(left_eq);
    free(right_eq);
}

#endif