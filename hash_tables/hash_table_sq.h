#ifndef _HASH_TABLE_SQ_
#define _HASH_TABLE_SQ_

#include "hash_table_open.h"

static void SqInsertKey(OpenTable* ht, ui key) {
	ui key_hash = get_hash(key, ht->size);
    int step = 1;
	while (ht->slots[key_hash] == OCC) {
		key_hash = (key_hash + step * step) % ht->size;
        ++step;
    }
	
	ht->keys[key_hash] = key;
	ht->slots[key_hash] = OCC;
}

static void SqRehash(OpenTable* ht) {
	int old_size 		= ht->size;
	SlotType* old_slots = ht->slots;
	int* old_keys 		= ht->keys;

	ht->size  *=	2;
	ht->slots =		(SlotType*)calloc(ht->size, sizeof(SlotType));
	ht->keys  =		(int*)calloc(ht->size, sizeof(int));

	for (int i = 0; i < old_size; ++i) {
		if (old_slots[i] == OCC)
			SqInsertKey(ht, old_keys[i]);
	}

	free(old_slots);
	free(old_keys);
}

static bool SqInsert(OpenTable* ht, ui key) {
	if ((float)(ht->count + 1) / ht->size > ht->max_load_factor)
		SqRehash(ht);
	
	ui key_hash		= get_hash(key, ht->size);
	ui start_key 	= key_hash;
	int del_ind		= -1;
    int step = 1;

	do {
		if (ht->slots[key_hash] == EMP)
			break;
		
		if (ht->slots[key_hash] == OCC && ht->keys[key_hash] == key)
			return false;
		
		if (ht->slots[key_hash] == DEL && del_ind == -1)
			del_ind = key_hash;

		key_hash = (key_hash + step * step) % ht->size;
        ++step;
	} while (key_hash != start_key);

	ui res_ind = (del_ind != -1 ? del_ind : key_hash);

	ht->keys[res_ind] = key;
	ht->slots[res_ind] = OCC;

	++ht->count;
	return true;
}

static bool SqSearch(OpenTable* ht, ui key) {
	ui key_hash = get_hash(key, ht->size);

	ui start_key = key_hash;
    int step = 1;

	do {
		if (ht->slots[key_hash] == EMP)
			return false;

		if (ht->slots[key_hash] == OCC && ht->keys[key_hash] == key) 
			return true;

		key_hash = (key_hash + step * step) % ht->size;
        ++step;
	} while (key_hash != start_key);

	return false;
}

static bool SqRemove(OpenTable* ht, ui key) {
	ui key_hash = get_hash(key, ht->size);
	
	ui start_key = key_hash;
    int step = 1;

	do {
		if (ht->slots[key_hash] == EMP)
			return false;

		if (ht->slots[key_hash] == OCC && ht->keys[key_hash] == key) {
			ht->slots[key_hash] = DEL;
			--ht->count;
			return true;
		}

		key_hash = (key_hash + step * step) % ht->size;
        ++step;
	} while (key_hash != start_key);

	return false;
}

#endif