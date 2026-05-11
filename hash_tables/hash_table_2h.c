#include "hash_table_2h.h"

bool DubInsert(OpenTable* table, uint32_t key) {
	if ((float)(table->count + 1) / table->size > table->max_load_factor)
		DubRehash(table);
	
	uint32_t key_hash		= get_hash(key, table->size);
	uint32_t start_key 		= key_hash;
	int del_ind				= -1;
	uint32_t step			= step_hash(key, table->size);

	do {
		if (table->slots[key_hash] == EMP)
			break;
		
		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key)
			return false;
		
		if (table->slots[key_hash] == DEL && del_ind == -1)
			del_ind = key_hash;

		key_hash = (key_hash + step) % table->size;
	} while (key_hash != start_key);

	uint32_t res_ind = (del_ind != -1 ? del_ind : key_hash);

	table->keys[res_ind] = key;
	table->slots[res_ind] = OCC;

	++table->count;
	return true;
}

bool DubSearch(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);

	uint32_t start_key = key_hash;
	uint32_t step = step_hash(key, table->size);

	do {
		if (table->slots[key_hash] == EMP)
			return false;

		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key) 
			return true;

		key_hash = (key_hash + step) % table->size;
	} while (key_hash != start_key);

	return false;
}

bool DubRemove(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);
	
	uint32_t start_key = key_hash;
	uint32_t step = step_hash(key, table->size);

	do {
		if (table->slots[key_hash] == EMP)
			return false;

		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key) {
			table->slots[key_hash] = DEL;
			--table->count;
			return true;
		}

		key_hash = (key_hash + step) % table->size;
	} while (key_hash != start_key);

	return false;
}

void DubRehash(OpenTable* table) {
	int old_size 		= table->size;
	SlotType* old_slots = table->slots;
	int* old_keys 		= table->keys;

	table->size  *=	2;
	table->slots =		(SlotType*)calloc(table->size, sizeof(SlotType));
	table->keys  =		(int*)calloc(table->size, sizeof(int));

	for (int i = 0; i < old_size; ++i) {
		if (old_slots[i] == OCC)
			DubInsertKey(table, old_keys[i]);
	}

	free(old_slots);
	free(old_keys);
}

void DubInsertKey(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);
	uint32_t step	  = step_hash(key, table->size);

	while (table->slots[key_hash] == OCC) {
		key_hash = (key_hash + step) % table->size;
    }
	
	table->keys[key_hash] = key;
	table->slots[key_hash] = OCC;
}

uint32_t step_hash(uint32_t key, int size) {
	uint32_t key_hash = hash_int_bit(key) % size;

	if (key_hash + 1 != size)
    	return key_hash + 1 - key_hash % 2;
	
	return key_hash - 1 + key_hash % 2;
}
