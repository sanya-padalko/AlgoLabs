#include "not-comp-sorts.h"

void LSD_sort(unsigned int* arr, int size) {
    unsigned int* res = (unsigned int*)calloc(size, sizeof(int));
    for (unsigned int mask = 0xff, shift = 0; mask > 0; mask <<= 8, shift += 8) {
        unsigned int pref_cnt[MAX];
        memset(pref_cnt, 0, sizeof(pref_cnt));
        for (int ind = 0; ind < size; ++ind)
            ++pref_cnt[(arr[ind] & mask) >> shift];

        for (int ind = 1; ind < MAX; ++ind)
            pref_cnt[ind] += pref_cnt[ind - 1];

        for (int ind = size - 1; ind >= 0; --ind)
            res[--pref_cnt[(arr[ind] & mask) >> shift]] = arr[ind];

        memcpy(arr, res, sizeof(int) * size);
    }
	
	free(res);
}

void RecMSD_sort(unsigned int* arr, int lt, int rt, unsigned int mask, int shift) {
    if (lt >= rt || shift < 0)
        return;

    unsigned int* res = (unsigned int*)calloc(rt - lt + 1, sizeof(int));
    unsigned int pref_cnt[MAX];
    unsigned int cnt[MAX];
    memset(pref_cnt, 0, sizeof(pref_cnt));
    memset(cnt, 0, sizeof(cnt));
    for (int ind = lt; ind <= rt; ++ind)
        ++cnt[(arr[ind] & mask) >> shift];

    pref_cnt[0] = cnt[0];
    for (int ind = 1; ind < MAX; ++ind)
        pref_cnt[ind] = pref_cnt[ind - 1] + cnt[ind];

    for (int ind = lt; ind <= rt; ++ind) {
        --pref_cnt[(arr[ind] & mask) >> shift];
        res[pref_cnt[(arr[ind] & mask) >> shift]] = arr[ind];
    }

    memcpy(arr + lt, res, (rt - lt + 1) * sizeof(int));

    free(res);
    mask = (mask >> 8);
    shift = (shift - 8);

    pref_cnt[0] = cnt[0];
    for (int ind = 1; ind < MAX; ++ind)
        pref_cnt[ind] = pref_cnt[ind - 1] + cnt[ind];

    RecMSD_sort(arr, lt, lt + pref_cnt[0] - 1, mask, shift);
    for (int ind = 1; ind < MAX; ++ind)
        RecMSD_sort(arr, lt + pref_cnt[ind - 1], lt + pref_cnt[ind] - 1, mask, shift);
}

void MSD_sort(unsigned int* arr, int size) {
    RecMSD_sort(arr, 0, size - 1, 0xff000000, 24);
}