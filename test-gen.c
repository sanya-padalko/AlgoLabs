#include <stdio.h>
#include <stdlib.h>

int compar(const void* a, const void *b)  {
    return *(int *)a - *(int *)b;
}

int main() {
    srand(42);
    int *a = (int *)calloc(1000000, sizeof(int));
    for (int cnt = 100000; cnt <= 1000000; cnt += 100000) {
        for (int i = 0; i < cnt; ++i)
            a[i] = rand();
        
        char *file_name = (char *)calloc(30, sizeof(int));
        sprintf(file_name, "tests/%d.in", cnt);
        FILE* test_file = fopen(file_name, "w");
        for (int i = 0; i < cnt; ++i)
            fprintf(test_file, "%d ", a[i]);

        qsort(a, cnt, sizeof(int), compar);
        sprintf(file_name, "tests/%d.out", cnt);
        test_file = fopen(file_name, "w");
        for (int i = 0; i < cnt; ++i)
            fprintf(test_file, "%d ", a[i]);

        free(file_name);
    }
    
    free(a);
}