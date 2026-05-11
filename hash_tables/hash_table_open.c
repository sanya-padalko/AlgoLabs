#include "hash_table_open.h"

OpenTable* OpenTableCtor(int size, float lf) {
	OpenTable* table = (OpenTable*)malloc(sizeof(OpenTable));

	table->size			= size;
	table->count			= 0;
	table->max_load_factor	= lf;
	table->slots			= (SlotType*)calloc(size, sizeof(SlotType));
	table->keys			= (int*)calloc(size, sizeof(int));

	for (int i = 0; i < size; ++i)
		table->slots[i] = EMP;

	return table;
}

void OpenTableDtor(OpenTable* table) {
	free(table->keys);
	free(table->slots);
	free(table);
}
