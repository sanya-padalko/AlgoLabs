#ifndef _SPARCE_TABLE_
#define _SPARSE_TABLE_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../asserts.h"

#define MAXN		(int)1e6 + 10
#define MAX_LEVEL	20

#define MIN(a, b)	((a) < (b) ? (a) : (b))

typedef struct Node {
	int min;
} Node;

typedef struct SparseN {
	Node st[MAXN][MAX_LEVEL];
} SparseN;

typedef struct SparseLog {
	Node st[MAX_LEVEL][MAXN];
} SparseLog;

int			GetMinN			(SparseN* table, int lt, int rt)	;
int			GetMinLog		(SparseLog* table, int lt, int rt)	;

SparseLog*	ArrLogCtor		(int size, int* arr)				;
SparseN*	ArrNCtor		(int size, int* arr)				;

SparseN*	SparseNCtor		()									;
SparseLog*	SparseLogCtor	()									;

void		CalcLog			()									;

#endif