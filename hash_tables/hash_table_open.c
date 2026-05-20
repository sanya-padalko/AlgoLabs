#include "hash_table_open.h"

bool OpenInsert(OpenTable* table, uint32_t key) {
	if ((float)(table->count + 1) / table->size > table->max_load_factor)
		OpenRehash(table);
	
	uint32_t key_hash		= get_hash(key, table->size);
	uint32_t start_key		= key_hash;

	int del_ind		= -1;
	int step_ind	= 1;		

	do {
		if (table->slots[key_hash] == EMP)
			break;
		
		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key)
			return false;
		
		if (table->slots[key_hash] == DEL && del_ind == -1)
			del_ind = key_hash;

		key_hash = table->probe(key_hash, step_ind, table->size);
		++step_ind;
	} while (key_hash != start_key);

	uint32_t res_ind = (del_ind != -1 ? del_ind : key_hash);

	table->keys[res_ind] = key;
	table->slots[res_ind] = OCC;

	++table->count;
	return true;
}

void OpenRehash(OpenTable* table) {
	int old_size 		= table->size;
	SlotType* old_slots = table->slots;
	int* old_keys 		= table->keys;

	table->size  *=	2;
	table->slots =		(SlotType*)calloc(table->size, sizeof(SlotType));
	table->keys  =		(int*)calloc(table->size, sizeof(int));

	for (int i = 0; i < old_size; ++i) {
		if (old_slots[i] == OCC)
			OpenInsertKey(table, old_keys[i]);
	}

	free(old_slots);
	free(old_keys);
}

void OpenInsertKey(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);
	int step_ind	  = 1;
	while (table->slots[key_hash] == OCC) {
		key_hash = table->probe(key_hash, step_ind, table->size);
		++step_ind;
	}
	
	table->keys[key_hash] = key;
	table->slots[key_hash] = OCC;
}

bool OpenSearch(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);

	uint32_t start_key = key_hash;
	int step_ind	   = 1;

	do {
		if (table->slots[key_hash] == EMP)
			return false;

		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key) 
			return true;

		key_hash = table->probe(key_hash, step_ind, table->size);
		++step_ind;
	} while (key_hash != start_key);

	return false;
}

bool OpenRemove(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);
	
	uint32_t start_key = key_hash;
	int step_ind	   = 1;

	do {
		if (table->slots[key_hash] == EMP)
			return false;

		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key) {
			table->slots[key_hash] = DEL;
			--table->count;
			return true;
		}

		key_hash = table->probe(key_hash, step_ind, table->size);
		++step_ind;
	} while (key_hash != start_key);

	return false;
}

OpenTable* OpenTableCtor(int size, float lf) {
	OpenTable* table = (OpenTable*)malloc(sizeof(OpenTable));

	table->size				= size;
	table->count			= 0;
	table->max_load_factor	= lf;
	table->slots			= (SlotType*)calloc(size, sizeof(SlotType));
	table->keys				= (int*)calloc(size, sizeof(int));

	for (int i = 0; i < size; ++i)
		table->slots[i] = EMP;

	return table;
}

void OpenTableDtor(OpenTable* table) {
	free(table->keys);
	free(table->slots);
	free(table);
}
