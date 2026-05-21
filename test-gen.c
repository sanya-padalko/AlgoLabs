#include <stdio.h>
#include <stdlib.h>

int compar(const void* a, const void *b)  {
    return *(int *)a - *(int *)b;
}

int main() {
    srand(42);

	const int test_cnt = 1e6;
	const int step_cnt = 1e5;

	const int max_name_size = 30;

    int *arr = (int *)calloc(test_cnt, sizeof(int));
    for (int cnt = step_cnt; cnt <= test_cnt; cnt += step_cnt) {
        for (int i = 0; i < cnt; ++i)
            arr[i] = rand();
        
        char *file_name = (char *)calloc(max_name_size, sizeof(int));
        sprintf(file_name, "tests/%d.in", cnt);
        FILE* test_file = fopen(file_name, "w");
        for (int i = 0; i < cnt; ++i)
            fprintf(test_file, "%d ", arr[i]);

        qsort(arr, cnt, sizeof(int), compar);
        sprintf(file_name, "tests/%d.out", cnt);
        test_file = fopen(file_name, "w");
        for (int i = 0; i < cnt; ++i)
            fprintf(test_file, "%d ", arr[i]);

        free(file_name);
    }
    
    free(arr);
}