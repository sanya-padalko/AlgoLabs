#include "hash_table_2h.h"

bool DubInsert(OpenTable* ht, uint32_t key) {
	if ((float)(ht->count + 1) / ht->size > ht->max_load_factor)
		DubRehash(ht);
	
	uint32_t key_hash		= get_hash(key, ht->size);
	uint32_t start_key 		= key_hash;
	int del_ind				= -1;
	uint32_t step			= step_hash(key, ht->size);

	do {
		if (ht->slots[key_hash] == EMP)
			break;
		
		if (ht->slots[key_hash] == OCC && ht->keys[key_hash] == key)
			return false;
		
		if (ht->slots[key_hash] == DEL && del_ind == -1)
			del_ind = key_hash;

		key_hash = (key_hash + step) % ht->size;
	} while (key_hash != start_key);

	uint32_t res_ind = (del_ind != -1 ? del_ind : key_hash);

	ht->keys[res_ind] = key;
	ht->slots[res_ind] = OCC;

	++ht->count;
	return true;
}

bool DubSearch(OpenTable* ht, uint32_t key) {
	uint32_t key_hash = get_hash(key, ht->size);

	uint32_t start_key = key_hash;
	uint32_t step = step_hash(key, ht->size);

	do {
		if (ht->slots[key_hash] == EMP)
			return false;

		if (ht->slots[key_hash] == OCC && ht->keys[key_hash] == key) 
			return true;

		key_hash = (key_hash + step) % ht->size;
	} while (key_hash != start_key);

	return false;
}

bool DubRemove(OpenTable* ht, uint32_t key) {
	uint32_t key_hash = get_hash(key, ht->size);
	
	uint32_t start_key = key_hash;
	uint32_t step = step_hash(key, ht->size);

	do {
		if (ht->slots[key_hash] == EMP)
			return false;

		if (ht->slots[key_hash] == OCC && ht->keys[key_hash] == key) {
			ht->slots[key_hash] = DEL;
			--ht->count;
			return true;
		}

		key_hash = (key_hash + step) % ht->size;
	} while (key_hash != start_key);

	return false;
}

void DubRehash(OpenTable* ht) {
	int old_size 		= ht->size;
	SlotType* old_slots = ht->slots;
	int* old_keys 		= ht->keys;

	ht->size  *=	2;
	ht->slots =		(SlotType*)calloc(ht->size, sizeof(SlotType));
	ht->keys  =		(int*)calloc(ht->size, sizeof(int));

	for (int i = 0; i < old_size; ++i) {
		if (old_slots[i] == OCC)
			DubInsertKey(ht, old_keys[i]);
	}

	free(old_slots);
	free(old_keys);
}

void DubInsertKey(OpenTable* ht, uint32_t key) {
	uint32_t key_hash = get_hash(key, ht->size);
	uint32_t step	  = step_hash(key, ht->size);

	while (ht->slots[key_hash] == OCC) {
		key_hash = (key_hash + step) % ht->size;
    }
	
	ht->keys[key_hash] = key;
	ht->slots[key_hash] = OCC;
}

uint32_t step_hash(uint32_t key, int size) {
	uint32_t key_hash = hash_int_bit(key) % size;

	if (key_hash + 1 != size)
    	return key_hash + 1 - key_hash % 2;
	
	return key_hash - 1 + key_hash % 2;
}
