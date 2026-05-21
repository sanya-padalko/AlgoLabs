#include "small-sortings.h"

void swap(void* arg1, void* arg2, int size) {
    void* add = malloc(1 * size);
    memcpy(add, arg2, size);
    memcpy(arg2, arg1, size);
    memcpy(arg1, add, size);

	free(add);
}

void Insert_sort(uint32_t* arr, int size) {
    for (int ind = 1; ind < size; ++ind) {
        int ins_ind = ind - 1;
        int val = arr[ind];
        while (ins_ind >= 0 && val < arr[ins_ind]) {
            arr[ins_ind + 1] = arr[ins_ind];
            --ins_ind;
        }
        arr[ins_ind + 1] = val;
    }
}

void Bubble_sort(uint32_t* arr, int size) {
    for (int ind = 0; ind < size - 1; ++ind) {
        int check_swap = 0;

        for (int sw_ind = 0; sw_ind < size - 1 - ind; ++sw_ind) {
            if (arr[sw_ind] > arr[sw_ind + 1]) {
                swap(arr + sw_ind, arr + sw_ind + 1, sizeof(int));
                check_swap = 1;
            }
        }

        if (!check_swap)
            break;
    }
}

void Select_sort(uint32_t* arr, int size) {
    for (int ind = 0; ind < size; ++ind) {
        uint32_t ans = ind;
        for (int sel_ind = ind; sel_ind < size; ++sel_ind) {
            if (arr[ans] > arr[sel_ind])
                ans = sel_ind;
        }
        uint32_t val = arr[ans];
        arr[ans] = arr[ind];
        arr[ind] = val;
    }
}

void Shell_sort(uint32_t* arr, int size) {
    int gap = 1;
    while (gap < size / 3)
        gap = 3 * gap + 1;
    
    while (gap > 0) {
        for (int ind = gap; ind < size; ++ind) {
            uint32_t val = arr[ind];
            int best_ind = ind;
            while (best_ind >= gap && arr[best_ind - gap] > val) {
                arr[best_ind] = arr[best_ind - gap];
                best_ind -= gap;
            }
            arr[best_ind] = val;
        }
        gap /= 3;
    }
}

void OrigShell_sort(uint32_t* arr, int size) {
    for (int ind = 1; (size >> ind) > 0; ++ind) {
        int gap = size >> ind;
        for (int ind = gap; ind < size; ++ind) {
            uint32_t val = arr[ind];
            int best_ind = ind;
            while (best_ind >= gap && arr[best_ind - gap] > val) {
                arr[best_ind] = arr[best_ind - gap];
                best_ind -= gap;
            }
            arr[best_ind] = val;
        }
    }
}

int check(int gap) {
    if (gap == 0)
        return 0;

    while (gap % 2 == 0) 
        gap /= 2;
    
    while (gap % 3 == 0)
        gap /= 3;
    
    return (gap == 1);
}

void PrattShell_sort(uint32_t* arr, int size) {
    for (int gap = size; gap > 0; --gap) {
        while (!check(gap))
            --gap;

        for (int ind = gap; ind < size; ++ind) {
            uint32_t val = arr[ind];
            int best_ind = ind;
            while (best_ind >= gap && arr[best_ind - gap] > val) {
                arr[best_ind] = arr[best_ind - gap];
                best_ind -= gap;
            }
            arr[best_ind] = val;
        }
    }
}

void CiuraShell_sort(uint32_t* arr, int size) {
    int gaps[8] = {1, 4, 10, 23, 57, 132, 301, 701};
    for (int ind = 7; ind >= 0; --ind) {
        int gap = gaps[ind];

        for (int ind = gap; ind < size; ++ind) {
            uint32_t val = arr[ind];
            int best_ind = ind;
            while (best_ind >= gap && arr[best_ind - gap] > val) {
                arr[best_ind] = arr[best_ind - gap];
                best_ind -= gap;
            }
            arr[best_ind] = val;
        }
    }
}

void GonnetShell_sort(uint32_t* arr, int size) {
    int gap = size;
    for (; gap > 0; ) {
        for (int ind = gap; ind < size; ++ind) {
            uint32_t val = arr[ind];
            int best_ind = ind;
            while (best_ind >= gap && arr[best_ind - gap] > val) {
                arr[best_ind] = arr[best_ind - gap];
                best_ind -= gap;
            }
            arr[best_ind] = val;
        }

        if (gap == 1)
            break;
        
        gap = (5 * gap - 1) / 11;
        if (gap < 1)
            gap = 1;
    }
}