#ifndef __BINARY_HEAP__
#define __BINARY_HEAP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void swap(void* a, void* b, size_t size) {
    void* c = malloc(size);
    memcpy(c, a, size);
    memcpy(a, b, size);
    memcpy(b, c, size);
}

static void sift_down(int *arr, int n, int i) {
    int cur = i;
    while (1) {
        cur = i;
        int left = 2 * cur + 1;
        int right = 2 * cur + 2;
        if (left < n && arr[left] < arr[cur])
            cur = left;
        if (right < n && arr[right] < arr[cur])
            cur = right;
        
        if (cur == i)
            break;
        
        swap(arr + i, arr + cur, sizeof(int));

        i = cur;
    }
}

static void sift_up(int *arr, int i) {
    while (i > 0 && arr[i] < arr[(i - 1) / 2]) {
        swap(arr + i, arr + (i - 1) / 2, sizeof(int));
        i = (i - 1) / 2;
    }
}

static void build_heap(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        sift_down(arr, n, i);
    }
}

#endif