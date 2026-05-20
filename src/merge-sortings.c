#include "merge-sortings.h"

void MergeSeg(uint32_t* arr, int lt, int mid, int rt) {
    int i1 = lt;
    int i2 = mid + 1;
    int j = lt;

    while (i1 <= mid || i2 <= rt) {
        if (i1 > mid) {
            add_arr[j++] = arr[i2++];
            continue;
        }
        if (i2 > rt) {
            add_arr[j++] = arr[i1++];
            continue;
        }

        if (arr[i1] < arr[i2])
            add_arr[j++] = arr[i1++];
        else
            add_arr[j++] = arr[i2++];
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