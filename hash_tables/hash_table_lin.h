#ifndef _HASH_TABLE_LIN_
#define _HASH_TABLE_LIN_

#include "hash_table_open.h"

bool	LinInsert		(OpenTable* table, uint32_t key)	;
bool	LinSearch		(OpenTable* table, uint32_t key)	;
bool	LinRemove		(OpenTable* table, uint32_t key)	;

void	LinRehash		(OpenTable* table)					;
void	LinInsertKey	(OpenTable* table, uint32_t key)	;

#endif