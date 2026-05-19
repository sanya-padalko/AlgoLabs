#include "base-quick-sort.h"

int comp(void const *a, void const *b) {
    if (*(const uint32_t*)a < *(const uint32_t*)b)
        return -1;

    return 1;
}

void BaseQuick_sort(uint32_t* arr, int size) {
    qsort(arr, size, sizeof(int), comp);
}