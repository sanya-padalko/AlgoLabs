#ifndef __BINOM_HEAP__
#define __BINOM_HEAP__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node {
    int value;
    struct Node* parent;
    struct Node* child;
    struct Node* next;
    int degree;
};

struct BinomHeap {
    struct Node* head;
};

struct BinomHeap*	BinomHeap_ctr		()													;
struct Node* 		Node_ctr			(int value)											;

void 				link_binomial		(struct Node* node1, struct Node* node2)			;
struct BinomHeap* 	merge				(struct BinomHeap* Heap1, struct BinomHeap* Heap2)	;
struct BinomHeap* 	build_binom_heap	(int* arr, int cnt)									;

struct Node* 		extract_min			(struct BinomHeap** Heap)							;
int 				check_binom_heap	(struct BinomHeap* Heap, int cnt)					;

#endif