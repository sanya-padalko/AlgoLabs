#ifndef _HASH_TABLE_CEP_
#define _HASH_TABLE_CEP_

#include "../hash_func.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
	uint32_t key;
	struct Node* next;
} Node;

typedef struct {
	Node** buckets;
	int size;
	int count;
	float max_load_factor;
} CepTable;

bool		CepInsert		(CepTable* table, int key)			;
bool		CepSearch		(CepTable* table, int key)			;
bool		CepRemove		(CepTable* table, int key)			;

void		CepRehash		(CepTable* table)					;
void		CepInsertKey	(CepTable* table, uint32_t key)		;

CepTable*	CepTableCtor	(int size, float lf)				;
void		CepTableDtor	(CepTable* table)					;
void		ClearBucket		(Node* node)						;

uint32_t	get_hash		(uint32_t key, int size)			;

#endif