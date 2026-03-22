#ifndef __TESTING_H_
#define __TESTING_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>

static double GetTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000.0;
}

static double* Test(const char* test_path, void (*func)(unsigned int*, int), int from, int to, int step) {
    unsigned int* arr = (unsigned int*)calloc(to, sizeof(unsigned int));
    double* res_arr = (double*)calloc((to - from) / step + 1, sizeof(double));
    int res_ind = 0;
    
    for (int size = from; size <= to; size += step) {

        double sum_time_spent = 0;
        for (int ind = 1; ind <= 5; ++ind) {
            char* test_full_name_in = (char*)calloc(100, sizeof(char));
            char* test_full_name_out = (char*)calloc(100, sizeof(char));

            sprintf(test_full_name_in, "%s%d_%d.in", test_path, size, ind);
            sprintf(test_full_name_out, "%s%d_%d.out", test_path, size, ind);

            FILE* test_file_in = fopen(test_full_name_in, "r");
            for (int i = 0; i < size; ++i) {
                unsigned int x;
                fscanf(test_file_in, "%u", &x);
                arr[i] = x;
            }
            fclose(test_file_in);

            FILE* test_file_out = fopen(test_full_name_out, "r");
            double start_time = GetTime();
            func(arr, size);
            double spent_time = (GetTime() - start_time);
            sum_time_spent += spent_time;

            for (int i = 0; i < size; ++i) {
                unsigned int x;
                fscanf(test_file_out, "%u", &x);
                if (arr[i] != x) {
                    fprintf(stderr, "Wrong sorting on size = %d, ind = %d\n", size, ind);
                    if (size <= 200) {
                        for (int j = 0; j < size; ++j) {
                            printf("%u ", arr[j]);
                        }
                        printf("\n");
                    }
                    fclose(test_file_out);
                    assert(0);
                }
            }
            fclose(test_file_out);
        }

        res_arr[res_ind++] = sum_time_spent / 5.0;
        fprintf(stderr, "\rProgress: %7d/%d                 ", size, to);
    }
    printf("\n");
    free(arr);

    return res_arr;
} // expected: end of path to dir = "/"

#endif