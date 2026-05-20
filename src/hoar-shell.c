#include "hoar-shell.h"

void Hoar_Shell_sort(unsigned int* arr, int lt, int rt, 
                            int (*pivot_selector)(unsigned int*, int, int), 
                            int (*partition)(unsigned int*, int, int, int)) {
    if (lt >= rt) 
        return;

    if ((rt - lt + 1) <= block_size) {
        Shell_sort(arr + lt, rt - lt + 1);
        return;
    }

    int pivot = pivot_selector(arr, lt, rt);
    int gr = partition(arr, lt, rt, pivot);

    Hoar_Shell_sort(arr, lt, gr, pivot_selector, partition);
    Hoar_Shell_sort(arr, gr + 1, rt, pivot_selector, partition);
}

void HoarShell_sort(unsigned int* arr, int size) {
    Hoar_Shell_sort(arr, 0, size - 1, pivot_central, hoar_part);
}