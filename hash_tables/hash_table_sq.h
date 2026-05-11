#ifndef _HASH_TABLE_SQ_
#define _HASH_TABLE_SQ_

#include "hash_table_open.h"

bool	SqInsert	(OpenTable* ht, uint32_t key)	;
bool	SqSearch	(OpenTable* ht, uint32_t key)	;
bool	SqRemove	(OpenTable* ht, uint32_t key)	;

void	SqRehash	(OpenTable* ht)					;
void	SqInsertKey	(OpenTable* ht, uint32_t key)	;

#endif