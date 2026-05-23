#include "base-quick-sort.h"

int comp(void const *arg1, void const *arg2) {
    if (*(const uint32_t*)arg1 < *(const uint32_t*)arg2)
        return -1;

	if (*(const uint32_t*)arg1 > *(const uint32_t*)arg2)
        return 1;

    return 0;
}

void BaseQuick_sort(uint32_t* arr, int size) {
    qsort(arr, size, sizeof(int), comp);
}