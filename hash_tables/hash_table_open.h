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

static OpenTable* OpenTableCtor(int size, float lf) {
	OpenTable* ht = (OpenTable*)malloc(sizeof(OpenTable));

	ht->size			= size;
	ht->count			= 0;
	ht->max_load_factor	= lf;
	ht->slots			= (SlotType*)calloc(size, sizeof(SlotType));
	ht->keys			= (int*)calloc(size, sizeof(int));

	for (int i = 0; i < size; ++i)
		ht->slots[i] = EMP;

	return ht;
}

static void OpenTableDtor(OpenTable* ht) {
	free(ht->keys);
	free(ht->slots);
	free(ht);
}

#endif