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
	uint32_t	(*probe)(uint32_t, int, uint32_t);
} OpenTable;

bool		OpenInsert		(OpenTable* table, uint32_t key)	;
void		OpenRehash		(OpenTable* table)					;
void		OpenInsertKey	(OpenTable* table, uint32_t key)	;

bool		OpenSearch		(OpenTable* table, uint32_t key)	;
bool		OpenRemove		(OpenTable* table, uint32_t key)	;

OpenTable*	OpenTableCtor	(int size, float lf)				;
void		OpenTableDtor	(OpenTable* table)					;

#endif