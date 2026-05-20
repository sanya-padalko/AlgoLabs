#include "heap-sortings.h"

int get_parent(int ind) {
    return (ind - 1) / K_HEAP;
}

int get_child(int node_ind, int ch_ind) {
    return node_ind * K_HEAP + ch_ind + 1;
}

void sift_down(uint32_t *arr, int size, int el_ind) {
    uint32_t val = arr[el_ind];
    int ind = el_ind;
    
    while (get_child(ind, 0) < size) {
        int nxt = get_child(ind, 0);
        
        for (int cur_ch = 1; cur_ch < K_HEAP; ++cur_ch) {
            int cur = get_child(ind, cur_ch);
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
    
    while (ind > el_ind) {
        int parent = get_parent(ind);
        if (val <= arr[parent]) 
            break;

        arr[ind] = arr[parent];
        ind = parent;
    }

    arr[ind] = val;
}

void Bottom_up_heap_sort(uint32_t* arr, int size) {
    for (int ind = get_parent(size - 1); ind >= 0; --ind)
        sift_down(arr, size, ind);
    
    for (int ind = size - 1; ind > 0; --ind) {
        uint32_t temp = arr[0];
        arr[0] = arr[ind];
        arr[ind] = temp;
        
        sift_down(arr, ind, 0);
    }
}