#include "hash_table_sq.h"

bool SqInsert(OpenTable* table, uint32_t key) {
	if ((float)(table->count + 1) / table->size > table->max_load_factor)
		SqRehash(table);
	
	uint32_t key_hash		= get_hash(key, table->size);
	uint32_t start_key 	= key_hash;
	int del_ind		= -1;
    int step = 1;

	do {
		if (table->slots[key_hash] == EMP)
			break;
		
		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key)
			return false;
		
		if (table->slots[key_hash] == DEL && del_ind == -1)
			del_ind = key_hash;

		key_hash = (key_hash + step * step) % table->size;
        ++step;
	} while (key_hash != start_key);

	uint32_t res_ind = (del_ind != -1 ? del_ind : key_hash);

	table->keys[res_ind] = key;
	table->slots[res_ind] = OCC;

	++table->count;
	return true;
}

bool SqSearch(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);

	uint32_t start_key = key_hash;
    int step = 1;

	do {
		if (table->slots[key_hash] == EMP)
			return false;

		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key) 
			return true;

		key_hash = (key_hash + step * step) % table->size;
        ++step;
	} while (key_hash != start_key);

	return false;
}

bool SqRemove(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);
	
	uint32_t start_key = key_hash;
    int step = 1;

	do {
		if (table->slots[key_hash] == EMP)
			return false;

		if (table->slots[key_hash] == OCC && table->keys[key_hash] == key) {
			table->slots[key_hash] = DEL;
			--table->count;
			return true;
		}

		key_hash = (key_hash + step * step) % table->size;
        ++step;
	} while (key_hash != start_key);

	return false;
}

void SqRehash(OpenTable* table) {
	int old_size 		= table->size;
	SlotType* old_slots = table->slots;
	int* old_keys 		= table->keys;

	table->size  *=	2;
	table->slots =		(SlotType*)calloc(table->size, sizeof(SlotType));
	table->keys  =		(int*)calloc(table->size, sizeof(int));

	for (int i = 0; i < old_size; ++i) {
		if (old_slots[i] == OCC)
			SqInsertKey(table, old_keys[i]);
	}

	free(old_slots);
	free(old_keys);
}

void SqInsertKey(OpenTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);
    int step = 1;
	while (table->slots[key_hash] == OCC) {
		key_hash = (key_hash + step * step) % table->size;
        ++step;
    }
	
	table->keys[key_hash] = key;
	table->slots[key_hash] = OCC;
}
