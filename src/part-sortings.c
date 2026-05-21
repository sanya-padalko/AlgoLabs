#include "part-sortings.h"

int (*hoar_pivot)(uint32_t*, int, int) = pivot_central;

int pivot_central(uint32_t* arr, int lt, int rt) {
    return (lt + rt) / 2;
}

int pivot_mediana3(uint32_t* arr, int lt, int rt) {
    int mid = (lt + rt) / 2;

    if (arr[lt] > arr[mid])
        swap(arr + lt, arr + mid, sizeof(int));

    if (arr[lt] > arr[rt])
        swap(arr + lt, arr + rt, sizeof(int));

    if (arr[mid] > arr[rt]) 
        swap(arr + mid, arr + rt, sizeof(int));

    return mid;
}

int pivot_random(uint32_t* arr, int lt, int rt) {
    if ((rt - lt + 1) <= 0)
        return lt;

    int rand_num = rand() % (rt - lt + 1);
    return lt + rand_num;
}

int pivot_random_med(uint32_t* arr, int lt, int rt) {
    if ((rt - lt + 1) <= 0)
        return lt;

    int rand1 = lt + rand() % (rt - lt + 1);
    int rand2 = lt + rand() % (rt - lt + 1);
    int rand3 = lt + rand() % (rt - lt + 1);
    if (arr[rand1] > arr[rand2])
        swap(arr + rand1, arr + rand2, sizeof(int));

    if (arr[rand2] > arr[rand3])
        swap(arr + rand2, arr + rand3, sizeof(int));

    if (arr[rand1] > arr[rand3]) 
        swap(arr + rand1, arr + rand3, sizeof(int));

    return rand2;
}

int hoar_part(uint32_t* arr, int lt, int rt, int pivot_ind) {
    int lt_ind = lt;
    int rt_ind = rt;
    uint32_t pivot = arr[pivot_ind];
    while (1) {
        while (lt_ind <= rt && arr[lt_ind] < pivot)
            ++lt_ind;
        while (rt_ind >= lt && arr[rt_ind] > pivot)
            --rt_ind;

        if (lt_ind >= rt_ind)
            return rt_ind;

        swap(arr + lt_ind, arr + rt_ind, sizeof(int));
        ++lt_ind;
        --rt_ind;
    }
}

int lomuto_part(uint32_t* arr, int lt, int rt, int pivot_ind) {
    uint32_t pivot = arr[pivot_ind];
    swap(arr + rt, arr + pivot_ind, sizeof(int));

    int ind = lt - 1;
    for (int cur_ind = lt; cur_ind < rt; ++cur_ind) {
        if (arr[cur_ind] <= pivot) {
            ++ind;

            swap(arr + cur_ind, arr + ind, sizeof(int));
        }
    }

    swap(arr + rt, arr + ind + 1, sizeof(int));

    return ind + 1;
}

uint32_t *left_eq = NULL;
uint32_t *right_eq = NULL;

int thick_part(uint32_t* arr, int lt, int rt, int pivot_ind) {
    uint32_t pivot = arr[pivot_ind];
    int lq = lt;
    int eq = lt;
    int rq = rt;

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

void Quick_sort(uint32_t* arr, int lt, int rt, 
                            int (*pivot_selector)(uint32_t*, int, int), 
                            int (*partition)(uint32_t*, int, int, int)) {
    if (lt >= rt)
        return;

    if ((rt - lt + 1) <= 32) {
        Insert_sort(arr + lt, rt - lt + 1);
        return;
    }

    int pivot = pivot_selector(arr, lt, rt);
    int gr = partition(arr, lt, rt, pivot);
    if (left_eq && right_eq) {
        Quick_sort(arr, lt, *left_eq, pivot_selector, partition);
        Quick_sort(arr, *right_eq, rt, pivot_selector, partition);
        return;
    }

    if (gr == rt) --gr;
    if (gr < lt) gr = lt;

    Quick_sort(arr, lt, gr, pivot_selector, partition);
    Quick_sort(arr, gr + 1, rt, pivot_selector, partition);
}

void Hoar_sort(uint32_t* arr, int size)  {
    left_eq = right_eq = NULL;
    Quick_sort(arr, 0, size - 1, hoar_pivot, hoar_part);
}

void Lomuto_sort(uint32_t* arr, int size) {
    left_eq = right_eq = NULL;
    Quick_sort(arr, 0, size - 1, pivot_central, lomuto_part);
}

void Thick_sort(uint32_t* arr, int size) {
    left_eq = (uint32_t*)calloc(1, sizeof(int));
    right_eq = (uint32_t*)calloc(1, sizeof(int));
    Quick_sort(arr, 0, size - 1, pivot_central, thick_part);
    free(left_eq);
    free(right_eq);
}
