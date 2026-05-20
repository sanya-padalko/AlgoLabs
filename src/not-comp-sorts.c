#include "not-comp-sorts.h"

void LSD_sort(unsigned int* arr, int size) {
    unsigned int* res = (unsigned int*)calloc(size, sizeof(int));
    for (unsigned int mask = 0xff, shift = 0; mask > 0; mask <<= 8, shift += 8) {
        unsigned int pref_cnt[MAX];
        memset(pref_cnt, 0, sizeof(pref_cnt));
        for (int i = 0; i < size; ++i)
            ++pref_cnt[(arr[i] & mask) >> shift];

        for (int i = 1; i < MAX; ++i)
            pref_cnt[i] += pref_cnt[i - 1];

        for (int i = size - 1; i >= 0; --i)
            res[--pref_cnt[(arr[i] & mask) >> shift]] = arr[i];

        memcpy(arr, res, sizeof(int) * size);
    }
	
	free(res);
}

void RecMSD_sort(unsigned int* arr, int l, int r, unsigned int mask, int shift) {
    if (l >= r || shift < 0)
        return;

    unsigned int* res = (unsigned int*)calloc(r - l + 1, sizeof(int));
    unsigned int pref_cnt[MAX];
    unsigned int cnt[MAX];
    memset(pref_cnt, 0, sizeof(pref_cnt));
    memset(cnt, 0, sizeof(cnt));
    for (int i = l; i <= r; ++i)
        ++cnt[(arr[i] & mask) >> shift];

    pref_cnt[0] = cnt[0];
    for (int i = 1; i < MAX; ++i)
        pref_cnt[i] = pref_cnt[i - 1] + cnt[i];

    for (int i = l; i <= r; ++i) {
        --pref_cnt[(arr[i] & mask) >> shift];
        res[pref_cnt[(arr[i] & mask) >> shift]] = arr[i];
    }

    memcpy(arr + l, res, (r - l + 1) * sizeof(int));

    free(res);
    mask = (mask >> 8);
    shift = (shift - 8);

    pref_cnt[0] = cnt[0];
    for (int i = 1; i < MAX; ++i)
        pref_cnt[i] = pref_cnt[i - 1] + cnt[i];

    RecMSD_sort(arr, l, l + pref_cnt[0] - 1, mask, shift);
    for (int i = 1; i < MAX; ++i)
        RecMSD_sort(arr, l + pref_cnt[i - 1], l + pref_cnt[i] - 1, mask, shift);
}

void MSD_sort(unsigned int* arr, int size) {
    RecMSD_sort(arr, 0, size - 1, 0xff000000, 24);
}