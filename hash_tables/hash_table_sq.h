#ifndef _HASH_TABLE_SQ_
#define _HASH_TABLE_SQ_

#include "hash_table_open.h"

uint32_t 	square_probe	(uint32_t last_hash, int step_ind, uint32_t size);

OpenTable*	SqTableCtor		(int size, float lf)						;

#endif