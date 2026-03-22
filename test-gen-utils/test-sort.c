#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000

int compar(void const *a, void const *b) {
    if (*(const unsigned int*)a < *(const unsigned int*)b)
        return -1;

    return 1;
}

int main() {
    unsigned int *arr = (unsigned int*)calloc(MAX_SIZE + 10, sizeof(int));

    unsigned int value;
    int ind = 0;
    while (scanf("%u", &value) == 1)
        arr[ind++] = value;

    qsort(arr, ind, sizeof(int), compar);
    for (int i = 0; i < ind; ++i)
        printf("%u ", arr[i]);

    printf("\n");
    free(arr);
}