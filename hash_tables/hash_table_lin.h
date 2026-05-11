#ifndef _HASH_TABLE_LIN_
#define _HASH_TABLE_LIN_

#include "hash_table_open.h"

bool	LinInsert		(OpenTable* ht, uint32_t key)	;
bool	LinSearch		(OpenTable* ht, uint32_t key)	;
bool	LinRemove		(OpenTable* ht, uint32_t key)	;

void	LinRehash		(OpenTable* ht)					;
void	LinInsertKey	(OpenTable* ht, uint32_t key)	;

#endif