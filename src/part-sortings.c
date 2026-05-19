#include "part-sortings.h"

int pivot_central(uint32_t* arr, int l, int r) {
    return (l + r) / 2;
}

int pivot_mediana3(uint32_t* arr, int l, int r) {
    int mid = (l + r) / 2;

    if (arr[l] > arr[mid])
        swap(arr + l, arr + mid, sizeof(int));

    if (arr[l] > arr[r])
        swap(arr + l, arr + r, sizeof(int));

    if (arr[mid] > arr[r]) 
        swap(arr + mid, arr + r, sizeof(int));

    return mid;
}

int pivot_random(uint32_t* arr, int l, int r) {
    if ((r - l + 1) <= 0)
        return l;

    srand(time(NULL));

    int rand_num = rand() % (r - l + 1);
    return l + rand_num;
}

int pivot_random_med(uint32_t* arr, int l, int r) {
    if ((r - l + 1) <= 0)
        return l;

    srand(time(NULL));

    int rand1 = l + rand() % (r - l + 1);
    int rand2 = l + rand() % (r - l + 1);
    int rand3 = l + rand() % (r - l + 1);
    if (arr[rand1] > arr[rand2])
        swap(arr + rand1, arr + rand2, sizeof(int));

    if (arr[rand2] > arr[rand3])
        swap(arr + rand2, arr + rand3, sizeof(int));

    if (arr[rand1] > arr[rand3]) 
        swap(arr + rand1, arr + rand3, sizeof(int));

    return rand2;
}

int hoar_part(uint32_t* arr, int l, int r, int pivot_ind) {
    int i = l;
    int j = r;
    uint32_t pivot = arr[pivot_ind];
    while (1) {
        while (i <= r && arr[i] < pivot)
            ++i;
        while (j >= l && arr[j] > pivot)
            --j;

        if (i >= j)
            return j;

        swap(arr + i, arr + j, sizeof(int));
        ++i;
        --j;
    }
}

int lomuto_part(uint32_t* arr, int l, int r, int pivot_ind) {
    uint32_t pivot = arr[pivot_ind];
    swap(arr + r, arr + pivot_ind, sizeof(int));

    int ind = l - 1;
    for (int i = l; i < r; ++i) {
        if (arr[i] <= pivot) {
            ++ind;

            swap(arr + i, arr + ind, sizeof(int));
        }
    }

    swap(arr + r, arr + ind + 1, sizeof(int));

    return ind + 1;
}

uint32_t *left_eq = NULL;
uint32_t *right_eq = NULL;

int thick_part(uint32_t* arr, int l, int r, int pivot_ind) {
    uint32_t pivot = arr[pivot_ind];
    int lq = l;
    int eq = l;
    int rq = r;

    while (eq <= rq) {
        if (arr[eq] < pivot) {
            swap(arr + lq, arr + eq, sizeof(int));
            ++lq;
            ++eq;
        }
        else if (arr[eq] == pivot) {
            ++eq;
        }
        else {
            swap(arr + rq, arr + eq, sizeof(int));
            --rq;
        }
    }

    *left_eq = lq - 1;
    *right_eq = rq + 1;

    return lq;
}

void Quick_sort(uint32_t* arr, int l, int r, 
                            int (*pivot_selector)(uint32_t*, int, int), 
                            int (*partition)(uint32_t*, int, int, int)) {
    if (l >= r)
        return;

    if ((r - l + 1) <= 32) {
        Insert_sort(arr + l, r - l + 1);
        return;
    }

    int pivot = pivot_selector(arr, l, r);
    int gr = partition(arr, l, r, pivot);
    if (left_eq && right_eq) {
        Quick_sort(arr, l, *left_eq, pivot_selector, partition);
        Quick_sort(arr, *right_eq, r, pivot_selector, partition);
        return;
    }

    if (gr == r) --gr;
    if (gr < l) gr = l;

    Quick_sort(arr, l, gr, pivot_selector, partition);
    Quick_sort(arr, gr + 1, r, pivot_selector, partition);
}

int (*hoar_pivot)(uint32_t*, int, int) = pivot_central;

void Hoar_sort(uint32_t* arr, int size)  {
    left_eq = right_eq = NULL;
    Quick_sort(arr, 0, size - 1, hoar_pivot, hoar_part);
}

void Lomuto_sort(uint32_t* arr, int size) {
    left_eq = right_eq = NULL;
    Quick_sort(arr, 0, size - 1, pivot_central, lomuto_part);
}void Thick_sort(uint32_t* arr, int size) {
    left_eq = (uint32_t*)calloc(1, sizeof(int));
    right_eq = (uint32_t*)calloc(1, sizeof(int));
    Quick_sort(arr, 0, size - 1, pivot_central, thick_part);
    free(left_eq);
    free(right_eq);
}
