#ifndef _HASH_TABLE_2H_
#define _HASH_TABLE_2H_

#include "hash_table_open.h"
#include "../hash_func.h"

bool		DubInsert		(OpenTable* ht, uint32_t key);
bool		DubSearch		(OpenTable* ht, uint32_t key);
bool		DubRemove		(OpenTable* ht, uint32_t key);

void		DubRehash		(OpenTable* ht);
void		DubInsertKey	(OpenTable* ht, uint32_t key);

uint32_t	step_hash		(uint32_t key, int size);

#endif