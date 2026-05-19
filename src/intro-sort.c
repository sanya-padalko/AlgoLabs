#include "intro-sort.h"

int get_log(int n) {
    int ans = 1;
    while (n > 1) {
        n /= 2;
        ++ans;
    }

    return ans;
}

void RecIntro_sort(uint32_t* arr, int l, int r, 
                            int (*pivot_selector)(uint32_t*, int, int), 
                            int (*partition)(uint32_t*, int, int, int), int deep) {
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

void Intro_sort(uint32_t* arr, int size) {
    block_size = 64;
    max_deep *= get_log(size);
    RecIntro_sort(arr, 0, size - 1, pivot_central, hoar_part, 0);
    max_deep /= get_log(size);
}