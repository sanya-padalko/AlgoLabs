#include "binary-heap.h"

void swap(void* arg1, void* arg2, size_t size) {
    void* add = malloc(size);
    memcpy(add, arg1, size);
    memcpy(arg1, arg2, size);
    memcpy(arg2, add, size);

	free(add);
}

static int GetLeft(int ind) {
	return 2 * ind + 1;
}

static int GetRight(int ind) {
	return 2 * ind + 2;
}

void sift_down(int *arr, int n, int ind) {
    int cur = ind;
    while (1) {
        cur = ind;
        int left = GetLeft(cur);
        int right = GetRight(cur);
        if (left < n && arr[left] < arr[cur])
            cur = left;
        if (right < n && arr[right] < arr[cur])
            cur = right;
        
        if (cur == ind)
            break;
        
        swap(arr + ind, arr + cur, sizeof(int));

        ind = cur;
    }
}

void sift_up(int *arr, int ind) {
    while (ind > 0 && arr[ind] < arr[(ind - 1) / 2]) {
        swap(arr + ind, arr + (ind - 1) / 2, sizeof(int));
        ind = (ind - 1) / 2;
    }
}

void build_heap(int *arr, int n) {
    for (int ind = n / 2 - 1; ind >= 0; --ind) {
        sift_down(arr, n, ind);
    }
}
