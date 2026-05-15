#include "sparse_table.h"

int lg[MAXN];

int GetMinN(SparseN* table, int lt, int rt) {
	MY_ASSERT(table,		"Нулевой указатель на массив\n");
	MY_ASSERT(0 <= lt,		"Недопустимая левая граница\n");
	MY_ASSERT(rt < MAXN,	"Недопустимая правая граница\n");
	MY_ASSERT(lt <= rt, 	"Вырожденный отрезок\n");

	int len		= rt - lt + 1;
	int log_len = lg[len];
	
	return MIN(table->st[lt][log_len].min,
			   table->st[rt - (1 << log_len) + 1][log_len].min);
}

int GetMinLog(SparseLog* table, int lt, int rt) {
	MY_ASSERT(table,		"Нулевой указатель на массив\n");
	MY_ASSERT(0 <= lt,		"Недопустимая левая граница\n");
	MY_ASSERT(rt < MAXN,	"Недопустимая правая граница\n");
	MY_ASSERT(lt <= rt, 	"Вырожденный отрезок\n");

	int len		= rt - lt + 1;
	int log_len = lg[len];
	
	return MIN(table->st[log_len][lt].min,
			   table->st[log_len][rt - (1 << log_len) + 1].min);
}

SparseN* ArrNCtor(int size, int* arr) {
	MY_ASSERT(arr,		 "Нулевой указатель на массив\n");
	MY_ASSERT(size >= 0, "Недопустимый размер\n");

	SparseN* table = SparseNCtor();
	for (int i = 0; i < size; ++i)
		table->st[i][0].min = arr[i];
	
	for (int j = 1; j < MAX_LEVEL; ++j) {
		for (int i = 0; i < MAXN; ++i) {
			int nxt = i + (1 << (j - 1));

			table->st[i][j].min = MIN(table->st[i][j - 1].min, 
									  table->st[nxt][j - 1].min);
		}
	}

	return table;
}

SparseLog* ArrLogCtor(int size, int* arr) {
	MY_ASSERT(arr,		 "Нулевой указатель на массив\n");
	MY_ASSERT(size >= 0, "Недопустимый размер\n");

	SparseLog* table = SparseLogCtor();
	for (int i = 0; i < size; ++i)
		table->st[0][i].min = arr[i];
	
	for (int i = 1; i < MAX_LEVEL; ++i) {
		for (int j = 0; j < MAXN; ++j) {
			int nxt = j + (1 << (i - 1));

			table->st[i][j].min = MIN(table->st[i][j - 1].min, 
									  table->st[nxt][j - 1].min);
		}
	}

	return table;
}

SparseN* SparseNCtor() {
	CalcLog();

	SparseN* table = (SparseN*)calloc(1, sizeof(SparseN));
	MY_ASSERT(table, "calloc не сработал\n");

	for (int i = 0; i < MAXN; ++i) {
		for (int j = 0; j < MAX_LEVEL; ++j) 
			table->st[i][j].min = INT_MAX;
	}

	return table;
}

SparseLog* SparseLogCtor() {
	CalcLog();

	SparseLog* table = (SparseLog*)calloc(1, sizeof(SparseLog));
	MY_ASSERT(table, "calloc не сработал\n");

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < MAXN; ++j) 
			table->st[i][j].min = INT_MAX;
	}

	return table;
}

void CalcLog() {
	lg[1] = 0;

	for (int i = 2; i < MAXN; ++i)
		lg[i] = lg[i / 2] + 1;
}