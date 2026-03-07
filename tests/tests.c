#include "tests.h"

#define ll long long

void Test1() {
	printf("|------------ Test 1: ------------|\n");
	printf("| (list)   time spent: %7.3f ms |\n", ListTest1());
	printf("| (vector) time spent: %7.3f ms |\n", VectTest1());
	printf("|---------------------------------|\n");
}

double ListTest1() {
	struct StackList* stacklist = StackList_ctr(sizeof(int));
	double start = GetTime();
	for (int val = 0; val < 1e6; ++val) {
		int elem = val;
		StackList_push(stacklist, &elem);
	}
	int current_size = 1e6;
	for (int iter = 0; iter < 9 && current_size >= 1e5; ++iter) {
		for (int pop_iter = 0; pop_iter < current_size / 2; ++pop_iter)
			StackList_pop(stacklist);
		current_size = current_size - current_size / 2;

		for (int push_iter = 0; push_iter < current_size / 2; ++push_iter) {
			int val = push_iter;
			StackList_push(stacklist, &val);
		}
		current_size = current_size + current_size / 2;
	}
	double time_spent = GetTime() - start;
	StackList_dtr(stacklist);
	return time_spent;
}

double VectTest1() {
	struct StackVector* stackvec = StackVector_ctr(1e6, sizeof(int));
	double start = GetTime();
	for (int val = 0; val < 1e6; ++val) {
		int elem = val;
		StackVector_push(stackvec, &elem);
	}
	int current_size = 1e6;
	for (int iter = 0; iter < 9 && current_size >= 1e5; ++iter) {
		for (int pop_iter = 0; pop_iter < current_size / 2; ++pop_iter)
			StackVector_pop(stackvec);
		current_size = current_size - current_size / 2;

		for (int push_iter = 0; push_iter < current_size / 2; ++push_iter) {
			int val = push_iter;
			StackVector_push(stackvec, &val);
		}
		current_size = current_size + current_size / 2;
	}
	double time_spent = GetTime() - start;
	StackVector_dtr(stackvec);
	return time_spent;
}

void Test2() {
	printf("|------------ Test 2: ------------|\n");
	printf("| (list)   time spent: %7.3f ms |\n", ListTest2());
	printf("| (vector) time spent: %7.3f ms |\n", VectTest2());
	printf("|---------------------------------|\n");
}

double ListTest2() {
	struct StackList* stacklist = StackList_ctr(sizeof(int));
	double start = GetTime();
	for (int val = 0; val < 1e6; ++val) {
		int elem = val;
		StackList_push(stacklist, &elem);
	}
	for (int iter = 0; iter < 100; ++iter) {
		for (int pop_iter = 0; pop_iter < 10000; ++pop_iter)
			StackList_pop(stacklist);

		for (int push_iter = 0; push_iter < 10000; ++push_iter) {
			int val = push_iter;
			StackList_push(stacklist, &val);
		}
	}

	int current_size = 1e6;
	for (int iter = 0; iter < 9 && current_size >= 1e5; ++iter) {
		for (int pop_iter = 0; pop_iter < current_size / 2; ++pop_iter)
			StackList_pop(stacklist);
		current_size = current_size - current_size / 2;

		for (int push_iter = 0; push_iter < current_size / 2; ++push_iter) {
			int val = push_iter;
			StackList_push(stacklist, &val);
		}
		current_size = current_size + current_size / 2;
	}

	for (int iter = 0; iter < 100; ++iter) {
		for (int pop_iter = 0; pop_iter < 10000; ++pop_iter)
			StackList_pop(stacklist);

		for (int push_iter = 0; push_iter < 10000; ++push_iter) {
			int val = push_iter;
			StackList_push(stacklist, &val);
		}
	}
	double time_spent = GetTime() - start;
	StackList_dtr(stacklist);
	return time_spent;
}

double VectTest2() {
	struct StackVector* stackvector = StackVector_ctr(1e6, sizeof(int));
	double start = GetTime();
	for (int val = 0; val < 1e6; ++val) {
		int* val_ptr = (int*)calloc(1, sizeof(int));
		*val_ptr = val;
		StackVector_push(stackvector, val_ptr);
	}
	for (int iter = 0; iter < 100; ++iter) {
		for (int pop_iter = 0; pop_iter < 10000; ++pop_iter)
			StackVector_pop(stackvector);

		for (int push_iter = 0; push_iter < 10000; ++push_iter) {
			int val = push_iter;
			StackVector_push(stackvector, &val);
		}
	}
	
	int current_size = 1e6;
	for (int iter = 0; iter < 9 && current_size >= 1e5; ++iter) {
		for (int pop_iter = 0; pop_iter < current_size / 2; ++pop_iter)
			StackVector_pop(stackvector);
		current_size = current_size - current_size / 2;

		for (int push_iter = 0; push_iter < current_size / 2; ++push_iter) {
			int val = push_iter;
			StackVector_push(stackvector, &val);
		}
		current_size = current_size + current_size / 2;
	}

	for (int iter = 0; iter < 100; ++iter) {
		for (int pop_iter = 0; pop_iter < 10000; ++pop_iter)
			StackVector_pop(stackvector);

		for (int push_iter = 0; push_iter < 10000; ++push_iter) {
			int val = push_iter;
			StackVector_push(stackvector, &val);
		}
	}
	double time_spent = GetTime() - start;
	StackVector_dtr(stackvector);
	return time_spent;
}

void Test3() {
	srand(time(NULL));
	printf("|------------ Test 3: ------------|\n");
	printf("| (list)   time spent: %7.3f ms |\n", ListTest3());
	printf("| (vector) time spent: %7.3f ms |\n", VectTest3());
	printf("|---------------------------------|\n");
}

double ListTest3() {
	struct StackList* stacklist = StackList_ctr(sizeof(int));
	for (int iter = 0; iter < 1e6; ++iter) {
		int val = iter;
		StackList_push(stacklist, &val);
	}

	double start = GetTime();
	for (int iter = 0; iter < 1e6; ++iter) {
		int val = iter;
		int rnd_type = GetRandom();
		if (rnd_type == 1)
			StackList_push(stacklist, &val);
		else
			StackList_pop(stacklist);
	}

	double time_spent = GetTime() - start;
	StackList_dtr(stacklist);
	return time_spent;
}

double VectTest3() {
	struct StackVector* stackvec = StackVector_ctr(1e6, sizeof(int));
	for (int iter = 0; iter < 1e6; ++iter) {
		int val = iter;
		StackVector_push(stackvec, &val);
	}

	double start = GetTime();
	for (int iter = 0; iter < 1e6; ++iter) {
		int val = iter;
		int rnd_type = GetRandom();
		if (rnd_type == 1)
			StackVector_push(stackvec, &val);
		else
			StackVector_pop(stackvec);
	}

	double time_spent = GetTime() - start;
	StackVector_dtr(stackvec);
	return time_spent;
}

int GetRandom() {
	return 1 + rand() % 2;
}

void Test4() {
	clock_t test4_time = clock();
	FILE* test_res = fopen("test4.txt", "w");
	for (int elem_cnt = 1000; elem_cnt <= 1e6; elem_cnt += 1000) {
		fprintf(test_res, "%d %lg %lg\n", elem_cnt, ListTest4(elem_cnt), VectTest4(elem_cnt));
		if (elem_cnt % 10000 == 0)
			printf("Test4: %2d/100\r", elem_cnt / 10000);
	}
	printf("Test 4 is 100%% complete\n");
	printf("\n");
	
	fclose(test_res);
}

double ListTest4(int elem_cnt) {
	struct StackList* stacklist = StackList_ctr(sizeof(int));
	double start = GetTime();
	for (int iter = 0; iter < elem_cnt; ++iter) {
		int val = iter;
		StackList_push(stacklist, &val);
	}
	double spent_time = (GetTime() - start);
	StackList_dtr(stacklist);
	return spent_time;
}

double VectTest4(int elem_cnt) {
	struct StackVector* stackvec = StackVector_ctr(1e6, sizeof(int));
	double start = GetTime();
	for (int iter = 0; iter < elem_cnt; ++iter) {
		int val = iter;
		StackVector_push(stackvec, &val);
	}
	double spent_time = (GetTime() - start);
	StackVector_dtr(stackvec);
	return spent_time;
}

double GetTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000.0;
}