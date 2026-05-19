#include "small-sortings.h"

void swap(void* a, void* b, int size) {
    void* c = malloc(1 * size);
    memcpy(c, b, size);
    memcpy(b, a, size);
    memcpy(a, c, size);
}

void Insert_sort(uint32_t* arr, int size) {
    for (int i = 1; i < size; ++i) {
        int j = i - 1;
        int val = arr[i];
        while (j >= 0 && val < arr[j]) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = val;
    }
}

void Bubble_sort(uint32_t* arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        int check_swap = 0;

        for (int j = 0; j < size - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr + j, arr + j + 1, sizeof(int));
                check_swap = 1;
            }
        }

        if (!check_swap)
            break;
    }
}

void Select_sort(uint32_t* arr, int size) {
    for (int i = 0; i < size; ++i) {
        uint32_t ans = i;
        for (int j = i; j < size; ++j) {
            if (arr[ans] > arr[j])
                ans = j;
        }
        uint32_t val = arr[ans];
        arr[ans] = arr[i];
        arr[i] = val;
    }
}

void Shell_sort(uint32_t* arr, int size) {
    int gap = 1;
    while (gap < size / 3)
        gap = 3 * gap + 1;
    
    while (gap > 0) {
        for (int i = gap; i < size; ++i) {
            uint32_t val = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > val) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = val;
        }
        gap /= 3;
    }
}

void OrigShell_sort(uint32_t* arr, int size) {
    for (int i = 1; (size >> i) > 0; ++i) {
        int gap = size >> i;
        for (int i = gap; i < size; ++i) {
            uint32_t val = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > val) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = val;
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

        for (int i = gap; i < size; ++i) {
            uint32_t val = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > val) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = val;
        }
    }
}

void CiuraShell_sort(uint32_t* arr, int size) {
    int gaps[8] = {1, 4, 10, 23, 57, 132, 301, 701};
    for (int i = 7; i >= 0; --i) {
        int gap = gaps[i];

        for (int i = gap; i < size; ++i) {
            uint32_t val = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > val) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = val;
        }
    }
}

void GonnetShell_sort(uint32_t* arr, int size) {
    int gap = size;
    for (; gap > 0; ) {
        for (int i = gap; i < size; ++i) {
            uint32_t val = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > val) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = val;
        }

        if (gap == 1)
            break;
        
        gap = (5 * gap - 1) / 11;
        if (gap < 1)
            gap = 1;
    }
}