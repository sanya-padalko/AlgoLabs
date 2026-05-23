#include "../sparse_table.h"
#include <stdlib.h>

#define TESTS \
	ADD(test_sparseN) 		\
	ADD(test_sparseLog)		\

#define CTEST_IMPLEMENTATION
#include "../../ctest.h"

TEST(test_sparseN,
	srand(42);

	const int test_size = 1e6;
	const int qr_cnt	= 1e4;

	int *arr = (int*)calloc(test_size, sizeof(int));
	for (int i = 0; i < test_size; ++i)
		arr[i] = rand() % test_size;

	SparseN* table = ArrNCtor(test_size, arr);
	
	for (int i = 0; i < qr_cnt; ++i) {
		int l = rand() % test_size;
		int d = rand() % (test_size - l);

		int ans = INT_MAX;
		for (int ind = l; ind <= l + d; ++ind)
			ans = MIN(ans, arr[ind]);
		
		int find_ans = GetMinN(table, l, l + d);
		ASSERT_EQ_MSG(ans, find_ans, "Minimum on [%d;%d] is wrong, predict: %d, recd: %d", l, l + d, ans, find_ans);

		fprintf(stderr, "\r%5d/%5d", i, qr_cnt);
	}
	fprintf(stderr, "\r%5d/%5d\n", qr_cnt, qr_cnt);

	SparseNDtor(table);

	fprintf(stderr, "Testing of Sparse Table with N strings ended\n");
)

TEST(test_sparseLog,
	srand(42);

	const int test_size = 1e6;
	const int qr_cnt	= 1e4;

	int *arr = (int*)calloc(test_size, sizeof(int));
	for (int i = 0; i < test_size; ++i)
		arr[i] = rand() % test_size;

	SparseLog* table = ArrLogCtor(test_size, arr);
	
	for (int i = 0; i < qr_cnt; ++i) {
		int l = rand() % test_size;
		int d = rand() % (test_size - l);

		int ans = INT_MAX;
		for (int ind = l; ind <= l + d; ++ind)
			ans = MIN(ans, arr[ind]);
		
		int find_ans = GetMinLog(table, l, l + d);
		ASSERT_EQ_MSG(ans, find_ans, "Minimum on [%d;%d] is wrong, predict: %d, recd: %d", l, l + d, ans, find_ans);
		
		fprintf(stderr, "\r%5d/%5d", i, qr_cnt);
	}
	fprintf(stderr, "\r%5d/%5d\n", qr_cnt, qr_cnt);

	SparseLogDtor(table);

	fprintf(stderr, "Testing of Sparse Table with Log strings ended\n");
)

RUN_TESTS();