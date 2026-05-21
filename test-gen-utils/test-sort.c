#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000

int compar(void const *arg1, void const *arg2) {
    if (*(const unsigned int*)arg1 < *(const unsigned int*)arg2)
        return -1;

	if (*(const unsigned int*)arg1 > *(const unsigned int*)arg2)
        return 1;

    return 0;
}

int main() {
    unsigned int *arr = (unsigned int*)calloc(MAX_SIZE + 10, sizeof(int));

    unsigned int value;
    int ind = 0;
    while (scanf("%u", &value) == 1)
        arr[ind++] = value;

    qsort(arr, ind, sizeof(int), compar);
    for (int arr_ind = 0; arr_ind < ind; ++arr_ind)
        printf("%u ", arr[arr_ind]);

    printf("\n");
    free(arr);
}