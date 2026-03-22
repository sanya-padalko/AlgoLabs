#include <stdio.h>

int K_HEAP = 2;

static int get_parent(int i) {
    return (i - 1) / K_HEAP;
}

static int get_child(int i, int j) {
    return i * K_HEAP + j + 1;
}

static void sift_down(unsigned int *arr, int size, int i) {
    unsigned int val = arr[i];
    int ind = i;
    
    while (get_child(ind, 0) < size) {
        int nxt = get_child(ind, 0);
        
        for (int j = 1; j < K_HEAP; ++j) {
            int cur = get_child(ind, j);
            if (cur >= size)
                break;

            if (arr[cur] > arr[nxt])
                nxt = cur;
        }
        
        if (val >= arr[nxt])
            break;

        arr[ind] = arr[nxt];
        ind = nxt;
    }
    
    while (ind > i) {
        int parent = get_parent(ind);
        if (val <= arr[parent]) 
            break;

        arr[ind] = arr[parent];
        ind = parent;
    }

    arr[ind] = val;
}

static void Bottom_up_heap_sort(unsigned int *arr, int size) {
    for (int i = get_parent(size - 1); i >= 0; --i)
        sift_down(arr, size, i);
    
    for (int i = size - 1; i > 0; --i) {
        unsigned int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        sift_down(arr, i, 0);
    }
}