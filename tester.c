#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include "binary-heap.h"
#include "binom-heap.h"

static double GetTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000.0;
}

void BinaryTest() {
    FILE* lin_results = fopen("binary/linear-bin", "w");
    FILE* ins_results = fopen("binary/insert-bin", "w");

    for (int cnt = 100000; cnt <= 1000000; cnt += 100000) {
        int *arr = (int *)calloc(cnt, sizeof(int));
        int *arr_copy = (int *)calloc(cnt, sizeof(int));
        char *file_name = (char *)calloc(30, sizeof(int));
        sprintf(file_name, "tests/%d.in", cnt);
        FILE* test_file = fopen(file_name, "r");
        for (int i = 0; i < cnt; ++i)
            fscanf(test_file, "%d", arr + i);
        
        memcpy(arr_copy, arr, sizeof(int) * cnt);
        
        double start_time = GetTime();
        build_heap(arr, cnt);
        double end_time = GetTime();
        fprintf(lin_results, "%lg\n", end_time - start_time);

        int last = -1e9;
        for (int i = cnt - 1; i >= 0; --i) {
            int cur = arr[0];
            if (cur < last) {
                printf("Wrong heap-linear-sorting\n");
                assert(0);
            }
            arr[0] = arr[i];
            sift_down(arr, i - 1, 0);
        }

        memcpy(arr, arr_copy, sizeof(int) * cnt);

        start_time = GetTime();
        for (int i = 0; i < cnt; ++i)
            sift_up(arr, i);
        end_time = GetTime();

        fprintf(ins_results, "%lg\n", end_time - start_time);
        
        last = -1e9;
        for (int i = cnt - 1; i >= 0; --i) {
            int cur = arr[0];
            if (cur < last) {
                printf("Wrong heap-insertion-sorting\n");
                assert(0);
            }
            arr[0] = arr[i];
            sift_down(arr, i - 1, 0);
        }

        fprintf(stderr, "Progress: %7d / %7d               \r", cnt, 1000000);
    }

    fprintf(stderr, "Binary Test ended                                \n");

    fclose(lin_results);
    fclose(ins_results);
}

void BinomialTest() {
    FILE* binom_res = fopen("binomial/binom", "w");
    for (int cnt = 100000; cnt <= 1000000; cnt += 100000) {
        int *arr = (int *)calloc(cnt, sizeof(int));
        char *file_name = (char *)calloc(30, sizeof(int));
        sprintf(file_name, "tests/%d.in", cnt);
        FILE* test_file = fopen(file_name, "r");
        for (int i = 0; i < cnt; ++i)
            fscanf(test_file, "%d", arr + i);
        
        double start_time = GetTime();
        struct BinomHeap* Heap = build_binom_heap(arr, cnt);
        double end_time = GetTime();
        fprintf(binom_res, "%lg\n", end_time - start_time);

        /*if (!check_binom_heap(Heap, cnt)) {
            fprintf(stderr, "Wrong binomial-heap's sorting\n");
            return;
        }*/

        free(Heap);

        fprintf(stderr, "Progress: %7d / %7d               \r", cnt, 1000000);
    }

    fclose(binom_res);
}

int main(int argc, char* argv[]) {
    int type = 0;
    if (argc >= 2)
        type = argv[1][0] - '0';

    switch (type) {
        case 1:
            BinaryTest();
            break;
        case 2:
            BinomialTest();
            break;
    }
}