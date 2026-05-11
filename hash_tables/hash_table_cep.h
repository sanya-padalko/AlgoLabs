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

bool		CepInsert		(CepTable* ht, int key)			;
bool		CepSearch		(CepTable* ht, int key)			;
bool		CepRemove		(CepTable* ht, int key)			;

void		CepRehash		(CepTable* ht)					;
void		CepInsertKey	(CepTable* ht, uint32_t key)	;

CepTable*	CepTableCtor	(int size, float lf)			;
void		CepTableDtor	(CepTable* ht)					;
void		ClearBucket		(Node* node)					;

uint32_t	get_hash		(uint32_t key, int size)		;

#endif