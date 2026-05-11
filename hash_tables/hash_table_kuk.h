#ifndef _HASH_TABLE_KUK_
#define _HASH_TABLE_KUK_

#include "hash_table_open.h"
#include "../hash_func.h"
#include <stdio.h>

#define MAX_ITERS 100


bool		KukInsert		(OpenTable* table, uint32_t key)	;
bool		KukSearch		(OpenTable* table, uint32_t key)	;
bool		KukRemove		(OpenTable* table, uint32_t key)	;

void		KukRehash		(OpenTable* table)					;
bool		DumbKukInsert	(OpenTable* table, uint32_t key)	;

uint32_t	kuk_hash_1		(uint32_t key, int size)		    ;
uint32_t	kuk_hash_2		(uint32_t key, int size)		    ;

#endif