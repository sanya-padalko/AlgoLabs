#include "../fenwick.h"
#include <stdlib.h>

#define TESTS \
	ADD(test_find) 		\
	ADD(test_change)	\

#define CTEST_IMPLEMENTATION
#include "../../ctest.h"

TEST(test_find,
	srand(42);

	int *arr = (int*)calloc(1000, sizeof(int));
	for (int i = 0; i < 1000; ++i)
		arr[i] = rand() % 100;

	Fenwick* tree = FenArrCtor(1000, arr);
	
	for (int i = 0; i < 10000; ++i) {
		int l = rand() % 1000;
		int d = rand() % (1000 - l);

		int ans = 0;
		for (int ind = l; ind <= l + d; ++ind)
			ans += arr[ind];
		
		int find_ans = SegSum(tree, l + 1, l + d + 1);
		ASSERT_EQ_MSG(ans, find_ans, "Sum on [%d;%d] is wrong, predict: %d, recd: %d", l, l + d, ans, find_ans);
	}

	FenDtor(tree);
)

TEST(test_change,
	srand(42);

	int *arr = (int*)calloc(1000, sizeof(int));
	for (int i = 0; i < 1000; ++i)
		arr[i] = rand() % 100;

	Fenwick* tree = FenArrCtor(1000, arr);
	
	for (int i = 0; i < 10000; ++i) {
		if (i % 100 == 0) {
			int ch_ind = rand() % 1000;
			int delta = rand() % 100 - arr[ch_ind];
			AddVal(tree, ch_ind + 1, delta);
			arr[ch_ind] += delta;
		}
		int l = rand() % 1000;
		int d = rand() % (1000 - l);

		int ans = 0;
		for (int ind = l; ind <= l + d; ++ind)
			ans += arr[ind];
		
		int find_ans = SegSum(tree, l + 1, l + d + 1);
		ASSERT_EQ_MSG(ans, find_ans, "Sum on [%d;%d] is wrong, predict: %d, recd: %d", l, l + d, ans, find_ans);
	}

	FenDtor(tree);
)

RUN_TESTS();