#include "skiplist.h"
#include "../timer.h"
#include <stdio.h>
#include <stdlib.h>

SkipList* root = NULL;

double TestList(int cnt, void (*test_func)(SkipList*, int)) {
	double sum_time = 0;
	for (int i = 0; i < cnt; ++i) {
		int val = rand();

		double start_time	= GetTime();
		test_func(root, val);
		double end_time		= GetTime();

		sum_time += end_time - start_time;
	}

	return sum_time;
}

int main() {
	root = SkipListCtor();
	srand(42);

	const int start_cnt = 1e5;
	const int end_cnt	= 1e6;
	const int step_cnt	= 1e5;

	FILE* ins_file = fopen("results/insert.csv", "w");
	if (!ins_file) fprintf(stderr, "File for insert's results didn't open\n");

	FILE* del_file = fopen("results/delete.csv", "w");
	if (!del_file) fprintf(stderr, "File for delete's results didn't open\n");

	for (int size = start_cnt; size <= end_cnt; size += step_cnt) {
		double 	sum_ins = 0;
		double	sum_del	= 0;
		int 	cnt		= 5;

		for (int test_ind = 0; test_ind < cnt; ++test_ind) {
			sum_ins += TestList(size,		Insert);
			sum_del += TestList(size / 2,	Delete);

			ListDtor(root);
			root = SkipListCtor();
		}

		fprintf(ins_file, "%lg\n", sum_ins / cnt);
		fprintf(del_file, "%lg\n", sum_del / cnt);

		fprintf(stderr, "\r random: %7d / %7d", size, end_cnt);
	}
	fprintf(stderr, "\n");

	fclose(ins_file);
	fclose(del_file);

	ListDtor(root);
	root = NULL;
}