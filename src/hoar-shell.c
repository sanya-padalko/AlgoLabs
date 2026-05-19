#include "hoar-shell.h"

void Hoar_Shell_sort(unsigned int* arr, int l, int r, 
                            int (*pivot_selector)(unsigned int*, int, int), 
                            int (*partition)(unsigned int*, int, int, int)) {
    if (l >= r) 
        return;

    if ((r - l + 1) <= block_size) {
        Shell_sort(arr + l, r - l + 1);
        return;
    }

    int pivot = pivot_selector(arr, l, r);
    int gr = partition(arr, l, r, pivot);

    Hoar_Shell_sort(arr, l, gr, pivot_selector, partition);
    Hoar_Shell_sort(arr, gr + 1, r, pivot_selector, partition);
}

void HoarShell_sort(unsigned int* arr, int size) {
    Hoar_Shell_sort(arr, 0, size - 1, pivot_central, hoar_part);
}