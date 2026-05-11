#include "hash_table_lin.h"

bool LinInsert(OpenTable* table, uint32_t key) {
	if ((float)(table->count + 1) / table->size > table->max_load_factor)
		LinRehash(table);
	
	uint32_t key_hash		= get_hash(key, table->size);
	uint32_t start_key 	= key_hash;
	int del_ind		= -1;

	do {
		if (table->slots[key_hash] == EMP)
			break;
		
		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key)
			return false;
		
		if (table->slots[key_hash] == DEL && del_ind == -1)
			del_ind = key_hash;

		key_hash = (key_hash + 1) % table->size;
	} while (key_hash != start_key);

	uint32_t res_ind = (del_ind != -1 ? del_ind : key_hash);

	table->keys[res_ind] = key;
	table->slots[res_ind] = OCC;

	++table->count;
	return true;
}

bool LinSearch(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);

	uint32_t start_key = key_hash;

	do {
		if (table->slots[key_hash] == EMP)
			return false;

		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key) 
			return true;

		key_hash = (key_hash + 1) % table->size;
	} while (key_hash != start_key);

	return false;
}

bool LinRemove(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);
	
	uint32_t start_key = key_hash;

	do {
		if (table->slots[key_hash] == EMP)
			return false;

		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key) {
			table->slots[key_hash] = DEL;
			--table->count;
			return true;
		}

		key_hash = (key_hash + 1) % table->size;
	} while (key_hash != start_key);

	return false;
}

void LinRehash(OpenTable* table) {
	int old_size 		= table->size;
	SlotType* old_slots = table->slots;
	int* old_keys 		= table->keys;

	table->size  *=	2;
	table->slots =		(SlotType*)calloc(table->size, sizeof(SlotType));
	table->keys  =		(int*)calloc(table->size, sizeof(int));

	for (int i = 0; i < old_size; ++i) {
		if (old_slots[i] == OCC)
			LinInsertKey(table, old_keys[i]);
	}

	free(old_slots);
	free(old_keys);
}

void LinInsertKey(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);
	while (table->slots[key_hash] == OCC)
		key_hash = (key_hash + 1) % table->size;
	
	table->keys[key_hash] = key;
	table->slots[key_hash] = OCC;
}
