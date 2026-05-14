#include "seg_tree.h"
#include "fenwick.h"
#include "../timer.h"
#include "stdlib.h"

double	sum_seg	 = 0;
double	sum_fen	 = 0;
int		test_cnt = 0;

void Test(int size, int* arr) {
	SegTree* seg_tree = SegTreeArrCtor(size, arr);
	Fenwick* fenwick  = FenArrCtor(size, arr);

	++test_cnt;

	double test_sum_seg = 0;
	double test_sum_fen = 0;

	const int seg_test_cnt = 1e6;
	double start = 0;
	double end	 = 0;
	
	for (int seg_ind = 0; seg_ind < seg_test_cnt; ++seg_ind) {
		int type = rand() % 2;
		if (type == 0) {
			int q_ind	= rand() % size;
			int new_val	= rand();
			
			start	= GetTime();
			ChangeVal(seg_tree, q_ind, new_val);
			end		= GetTime();

			test_sum_seg += (end - start);

			int delta = new_val - arr[q_ind];
			start	= GetTime();
			AddVal(fenwick, q_ind + 1, delta);
			end		= GetTime();
			arr[q_ind] = new_val;

			test_sum_fen += (end - start);
		}
		else {
			int l = rand() % size;
			int r = rand() % (size - l) + l;

			start	= GetTime();
			FindSum(seg_tree, l, r + 1);
			end		= GetTime();

			test_sum_seg += (end - start);

			start	= GetTime();
			SegSum(fenwick, l + 1, r + 1);
			end		= GetTime();

			test_sum_fen += (end - start);
		}
	}

	sum_seg += test_sum_seg;
	sum_fen += test_sum_fen;

	SegTreeDtor(seg_tree);
	FenDtor(fenwick);
}

int main() {
	srand(42);

	const int test_size = 1e6;
	const int test_cnt	= 5;
	int* arr = (int*)calloc(test_size, sizeof(int));

	for (int ind = 0; ind < test_size; ++ind)
		arr[ind] = rand();
	
	for (int test_ind = 0; test_ind < test_cnt; ++test_ind)
		Test(test_size, arr);
	
	sum_seg /= test_cnt;
	sum_fen /= test_cnt;

	FILE* res_file = fopen("results/tree_comp.md", "w");

	fprintf(res_file, "## Результаты сравнения Дерева отрезков и Фенвика\n");
	fprintf(res_file, "| Тип дерева | Среднее затраченное время на 1e6 операций |\n");
	fprintf(res_file, "| :---: | :---: |\n");
	fprintf(res_file, "| Фенвик | %7.2lf |\n", sum_fen);
	fprintf(res_file, "| Дерево отрезков | %7.2lf |\n", sum_seg);

	fclose(res_file);

	printf("Results saved in RSQ/results/tree_comp.md\n");
}