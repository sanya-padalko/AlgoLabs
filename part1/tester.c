#include "bst.h"
#include "../timer.h"
#include "../asserts.h"
#include <stdio.h>
#include <stdlib.h>

BSTnode* root = NULL;

double TestBST(int* arr, int len, BSTnode* (*test_func)(BSTnode*, int)) {
	double sum_time = 0;
	for (int i = 0; i < len; ++i) {
		int val = arr[i];

		double start_time	= GetTime();
		root = test_func(root, val);
		double end_time		= GetTime();

		sum_time += end_time - start_time;
	}

	return sum_time;
}

int main() {
	srand(42);

	const int ins_cnt = 1e5;
	const int del_cnt = 5e4;
	const int srt_cnt = 1e4;
	
	const int test_cnt = 5;

	int* rand_arr = (int*)calloc(ins_cnt, sizeof(int));
	MY_ASSERT(rand_arr, "calloc не сработал\n");
	for (int i = 0; i < ins_cnt; ++i)
		rand_arr[i] = rand();
	
	int* sort_arr = (int*)calloc(srt_cnt, sizeof(int));
	MY_ASSERT(sort_arr, "calloc не сработал\n");
	for (int i = 0; i < srt_cnt; ++i)
		sort_arr[i] = i;

	int* rand_sort_arr = (int*)calloc(srt_cnt, sizeof(int));
	MY_ASSERT(rand_sort_arr, "calloc не сработал\n");
	for (int i = 0; i < srt_cnt; ++i)
		rand_sort_arr[i] = rand() % srt_cnt;

	FILE* ins_file = fopen("results/insert.csv", "w");
	MY_ASSERT(ins_file, "insert-файл не открылся\n");
	for (int i = 0; i < test_cnt; ++i)
		fprintf(ins_file, "%lg\n", TestBST(rand_arr, ins_cnt, Insert));
	fclose(ins_file);

	FILE* del_file = fopen("results/delete.csv", "w");
	MY_ASSERT(del_file, "delete-файл не открылся\n");
	for (int i = 0; i < test_cnt; ++i)
		fprintf(del_file, "%lg\n", TestBST(rand_arr, del_cnt, Delete));
	fclose(del_file);

	root = NULL;

	FILE* sort_ins_file = fopen("results/insert_sort.csv", "w");
	MY_ASSERT(sort_ins_file, "sort_insert-файл не открылся\n");
	for (int i = 0; i < test_cnt; ++i)
		fprintf(sort_ins_file, "%lg\n", TestBST(sort_arr, srt_cnt, Insert));
	fclose(sort_ins_file);

	FILE* sort_del_file = fopen("results/delete_sort.csv", "w");
	MY_ASSERT(sort_del_file, "sort_delete-файл не открылся\n");
	for (int i = 0; i < test_cnt; ++i)
		fprintf(sort_del_file, "%lg\n", TestBST(rand_sort_arr, srt_cnt, Delete));
	fclose(sort_del_file);

	free(rand_arr);
	free(sort_arr);
	free(rand_sort_arr);
}