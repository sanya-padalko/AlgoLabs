#include "merge-sortings.h"

void MergeSeg(uint32_t* arr, int l, int m, int r) {
    int i1 = l;
    int i2 = m + 1;
    int j = l;

    while (i1 <= m || i2 <= r) {
        if (i1 > m) {
            add_arr[j++] = arr[i2++];
            continue;
        }
        if (i2 > r) {
            add_arr[j++] = arr[i1++];
            continue;
        }

        if (arr[i1] < arr[i2])
            add_arr[j++] = arr[i1++];
        else
            add_arr[j++] = arr[i2++];
    }

    for (int i = l; i <= r; ++i)
        arr[i] = add_arr[i];
}

void RecMergeSort(uint32_t* arr, int l, int r) {
    if (r <= l)
        return;

    int m = (r + l) / 2;
    RecMergeSort(arr, l, m);
    RecMergeSort(arr, m + 1, r);

    MergeSeg(arr, l, m, r);
}

void GoRecMerge_sort(uint32_t* arr, int size) { // go first
    add_arr = (uint32_t*)calloc(1e6, sizeof(int));
    RecMergeSort(arr, 0, size - 1);
    free(add_arr);
}

void IterMerge_sort(uint32_t* arr, int size) { // go last
    add_arr = (uint32_t*)calloc(1e6, sizeof(int));
    for (int len = 1; len < size; len *= 2) {
        for (int l = 0; l < size - len; l += 2 * len) {
            int m = l + len - 1;
            int r = l + 2 * len - 1;
            if (r >= size)
                r = size - 1;

            MergeSeg(arr, l, m, r);
        }
    }

    free(add_arr);
}