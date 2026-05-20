#ifndef _HASH_TABLE_LIN_
#define _HASH_TABLE_LIN_

#include "hash_table_open.h"

uint32_t 	linear_probe	(uint32_t last_hash, int step_ind, int size);

OpenTable*	LinTableCtor	(int size, float lf)						;

#endif