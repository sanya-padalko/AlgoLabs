#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "hash_tables/hash_table_2h.h"
#include "hash_tables/hash_table_cep.h"
#include "hash_tables/hash_table_kuk.h"
#include "hash_tables/hash_table_lin.h"
#include "hash_tables/hash_table_sq.h"

static double GetTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000.0;
}

uint32_t* test_arr;

void load_cep_test() {
	fprintf(stderr, "Cep testing start...\n");
	FILE* res_file = fopen("hash_table_res/cep", "w");
	for (float cur_lf = 0.4; cur_lf <= 0.8; cur_lf += 0.01) {
		CepTable* table = CepTableCtor(4, cur_lf);

		double start_time = GetTime();
		for (int i = 0; i < 1e6; ++i)
			CepInsert(table, test_arr[i]);

		double end_time = GetTime();

		fprintf(res_file, "%lg\n", end_time - start_time);

		CepTableDtor(table);
		fprintf(stderr, "%lg / %lg\r", cur_lf, 0.8);
	}
		fclose(res_file);

	fprintf(stderr, "Cep testing ended...\n");
}

void load_2h_test() {
	fprintf(stderr, "2h testing start...\n");
	FILE* res_file = fopen("hash_table_res/2h", "w");
	for (float cur_lf = 0.4; cur_lf <= 0.8; cur_lf += 0.01) {
		OpenTable* table = OpenTableCtor(4, cur_lf);

		double start_time = GetTime();
		for (int i = 0; i < 1e6; ++i)
			DubInsert(table, test_arr[i]);

		double end_time = GetTime();

		fprintf(res_file, "%lg\n", end_time - start_time);

		OpenTableDtor(table);
		fprintf(stderr, "%lg / %lg\r", cur_lf, 0.8);
	}
	fclose(res_file);

	fprintf(stderr, "2H testing ended...\n");
}

void load_kuk_test() {
	fprintf(stderr, "Kukushka testing start...\n");
	FILE* res_file = fopen("hash_table_res/kuk", "w");
	for (float cur_lf = 0.4; cur_lf <= 0.8; cur_lf += 0.01) {
		OpenTable* table = OpenTableCtor(4, cur_lf);

		double start_time = GetTime();
		for (int i = 0; i < 1e6; ++i)
			KukInsert(table, test_arr[i]);

		double end_time = GetTime();

		fprintf(res_file, "%lg\n", end_time - start_time);

		OpenTableDtor(table);
		fprintf(stderr, "%lg / %lg\r", cur_lf, 0.8);
	}
	fclose(res_file);

	fprintf(stderr, "Kukushka testing ended...\n");
}

void load_lin_test() {
	fprintf(stderr, "Linear testing start...\n");
	FILE* res_file = fopen("hash_table_res/lin", "w");
	for (float cur_lf = 0.4; cur_lf <= 0.8; cur_lf += 0.01) {
		OpenTable* table = OpenTableCtor(4, cur_lf);

		double start_time = GetTime();
		for (int i = 0; i < 1e6; ++i)
			LinInsert(table, test_arr[i]);

		double end_time = GetTime();

		fprintf(res_file, "%lg\n", end_time - start_time);

		OpenTableDtor(table);
		fprintf(stderr, "%lg / %lg\r", cur_lf, 0.8);
	}
	fclose(res_file);
	fprintf(stderr, "Linear testing ended...\n");
}

void load_sq_test() {
	fprintf(stderr, "Square testing start...\n");
	FILE* res_file = fopen("hash_table_res/sq", "w");
	for (float cur_lf = 0.4; cur_lf <= 0.8; cur_lf += 0.01) {
		OpenTable* table = OpenTableCtor(4, cur_lf);

		double start_time = GetTime();
		for (int i = 0; i < 1e6; ++i)
			SqInsert(table, test_arr[i]);

		double end_time = GetTime();

		fprintf(res_file, "%lg\n", end_time - start_time);

		OpenTableDtor(table);
		fprintf(stderr, "%lg / %lg\r", cur_lf, 0.8);
	}
	fclose(res_file);
	fprintf(stderr, "Square testing ended...\n");
}

int main() {
	FILE* test_file	= fopen("tests/tests_int.txt", "r");
	test_arr		= (uint32_t*)calloc(1e6, sizeof(int));

	for (int i = 0; i < 1e6; ++i)
		fscanf(test_file, "%u", &test_arr[i]);

	load_2h_test();
	load_cep_test();
	load_kuk_test();
	load_lin_test();
	load_sq_test();
}