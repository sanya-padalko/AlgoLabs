#ifndef _HASH_TABLE_OPEN_H_
#define _HASH_TABLE_OPEN_H_

#include "hash_table_cep.h"
#include <stdbool.h>

typedef enum {
	EMP = 0,
	OCC = 1,
	DEL = 2
} SlotType;

typedef struct {
	SlotType*	slots;
	int*		keys;
	int			size;
	int			count;
	float		max_load_factor;
} OpenTable;

OpenTable*	OpenTableCtor	(int size, float lf)		;
void		OpenTableDtor	(OpenTable* table)			;

#endif