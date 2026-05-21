#include "merge-sortings.h"

uint32_t* add_arr = NULL;

void MergeSeg(uint32_t* arr, int lt, int mid, int rt) {
    int ind1 	= lt;
    int ind2 	= mid + 1;
    int add_ind = lt;

    while (ind1 <= mid || ind2 <= rt) {
        if (ind1 > mid) {
            add_arr[add_ind++] = arr[ind2++];
            continue;
        }
        if (ind2 > rt) {
            add_arr[add_ind++] = arr[ind1++];
            continue;
        }

        if (arr[ind1] < arr[ind2])
            add_arr[add_ind++] = arr[ind1++];
        else
            add_arr[add_ind++] = arr[ind2++];
    }

    for (int i = lt; i <= rt; ++i)
        arr[i] = add_arr[i];
}

void RecMergeSort(uint32_t* arr, int lt, int rt) {
    if (rt <= lt)
        return;

    int mid = (rt + lt) / 2;
    RecMergeSort(arr, lt, mid);
    RecMergeSort(arr, mid + 1, rt);

    MergeSeg(arr, lt, mid, rt);
}

void GoRecMerge_sort(uint32_t* arr, int size) { // go first
    add_arr = (uint32_t*)calloc(size, sizeof(int));
    RecMergeSort(arr, 0, size - 1);
    free(add_arr);
}

void IterMerge_sort(uint32_t* arr, int size) { // go last
    add_arr = (uint32_t*)calloc(size, sizeof(int));
    for (int len = 1; len < size; len *= 2) {
        for (int lt = 0; lt < size - len; lt += 2 * len) {
            int mid = lt + len - 1;
            int rt = lt + 2 * len - 1;
            if (rt >= size)
                rt = size - 1;

            MergeSeg(arr, lt, mid, rt);
        }
    }

    free(add_arr);
}