#include "sparse_table.h"
#include "../timer.h"
#include "stdlib.h"

double	sum_N	 = 0;
double	sum_Log	 = 0;
int		test_cnt = 0;

void Test(int size, int* arr) {
	SparseN* table1		= ArrNCtor(size, arr);
	SparseLog* table2	= ArrLogCtor(size, arr);

	++test_cnt;

	double test_sum_N	= 0;
	double test_sum_Log	= 0;

	const int seg_test_cnt = 1e6;
	double start = 0;
	double end	 = 0;
	
	for (int seg_ind = 0; seg_ind < seg_test_cnt; ++seg_ind) {
		int l = rand() % (size - 1);
		int r = rand() % (size - l - 1) + l + 1;

		start	= GetTime();
		GetMinN(table1, l, r);
		end		= GetTime();

		test_sum_N	 += (end - start);

		start	= GetTime();
		GetMinLog(table2, l, r);
		end		= GetTime();

		test_sum_Log += (end - start);
	}

	sum_N += test_sum_N;
	sum_Log += test_sum_Log;

	SparseNDtor(table1);
	SparseLogDtor(table2);
}

int main() {
	srand(42);

	const int test_size = 1e6;
	const int test_cnt	= 5;
	int* arr = (int*)calloc(test_size, sizeof(int));
	MY_ASSERT(arr, "calloc не сработал\n");

	for (int ind = 0; ind < test_size; ++ind)
		arr[ind] = rand();
	
	for (int test_ind = 0; test_ind < test_cnt; ++test_ind)
		Test(test_size, arr);
	
	sum_N /= test_cnt;
	sum_Log /= test_cnt;

	FILE* res_file = fopen("results/sparse_table_comp.md", "w");
	MY_ASSERT(res_file, "Файл для результатов не открылся\n");

	fprintf(res_file, "## Результаты сравнения двух вариантов Sparse Table\n");
	fprintf(res_file, "| Тип Sparse Table | Среднее затраченное время на 1e6 операций |\n");
	fprintf(res_file, "| :---: | :---: |\n");
	fprintf(res_file, "| n строк | %7.2lf |\n", sum_N);
	fprintf(res_file, "| log n строк | %7.2lf |\n", sum_Log);

	fclose(res_file);

	printf("Results saved in results/sparse_table_comp.md\n");
}