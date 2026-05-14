#include "../seg_tree.h"
#include <stdlib.h>

#define TESTS \
	ADD(test_find) 		\
	ADD(test_change)	\

#define CTEST_IMPLEMENTATION
#include "../ctest.h"

TEST(test_find,
	srand(42);

	int *arr = (int*)calloc(1000, sizeof(int));
	for (int i = 0; i < 1000; ++i)
		arr[i] = rand() % 100;

	SegTree* tree = SegTreeArrCtor(1000, arr);
	
	for (int i = 0; i < 10000; ++i) {
		int l = rand() % 1000;
		int d = 1 + rand() % (1000 - l);

		int ans = 0;
		for (int ind = l; ind < l + d; ++ind)
			ans += arr[ind];
		
		int find_ans = FindSum(tree, l, l + d);
		ASSERT_EQ_MSG(ans, find_ans, "Sum on [%d;%d) is wrong, predict: %d, recd: %d", l, l + d, ans, find_ans);
	}

	SegTreeDtor(tree);
)

TEST(test_change,
	srand(42);

	int *arr = (int*)calloc(1000, sizeof(int));
	for (int i = 0; i < 1000; ++i)
		arr[i] = rand() % 100;

	SegTree* tree = SegTreeArrCtor(1000, arr);
	
	for (int i = 0; i < 10000; ++i) {
		if (i % 100 == 0) {
			int new_val = rand() % 20;
			int ch_ind	= rand() % 1000;

			ChangeVal(tree, ch_ind, new_val);
		}

		int l = rand() % 1000;
		int d = 1 + rand() % (1000 - l);

		int ans = 0;
		for (int ind = l; ind < l + d; ++ind)
			ans += arr[ind];
		
		int find_ans = FindSum(tree, l, l + d);
		ASSERT_EQ_MSG(ans, find_ans, "Sum on [%d;%d) is wrong, predict: %d, recd: %d", l, l + d, ans, find_ans);
	}

	SegTreeDtor(tree);
)

RUN_TESTS();