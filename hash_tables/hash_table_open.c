#include "hash_table_open.h"

OpenTable* OpenTableCtor(int size, float lf) {
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

void OpenTableDtor(OpenTable* ht) {
	free(ht->keys);
	free(ht->slots);
	free(ht);
}
