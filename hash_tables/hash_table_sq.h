#ifndef _HASH_TABLE_SQ_
#define _HASH_TABLE_SQ_

#include "hash_table_open.h"

bool	SqInsert	(OpenTable* table, uint32_t key)	;
bool	SqSearch	(OpenTable* table, uint32_t key)	;
bool	SqRemove	(OpenTable* table, uint32_t key)	;

void	SqRehash	(OpenTable* table)					;
void	SqInsertKey	(OpenTable* table, uint32_t key)	;

#endif