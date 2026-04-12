#ifndef _HASH_TABLE_LIN_
#define _HASH_TABLE_LIN_

#include "hash_table_open.h"

static void LinInsertKey(OpenTable* ht, ui key) {
	ui key_hash = get_hash(key, ht->size);
	while (ht->slots[key_hash] == OCC)
		key_hash = (key_hash + 1) % ht->size;
	
	ht->keys[key_hash] = key;
	ht->slots[key_hash] = OCC;
}

static void LinRehash(OpenTable* ht) {
	int old_size 		= ht->size;
	SlotType* old_slots = ht->slots;
	int* old_keys 		= ht->keys;

	ht->size  *=	2;
	ht->slots =		(SlotType*)calloc(ht->size, sizeof(SlotType));
	ht->keys  =		(int*)calloc(ht->size, sizeof(int));

	for (int i = 0; i < old_size; ++i) {
		if (old_slots[i] == OCC)
			LinInsertKey(ht, old_keys[i]);
	}

	free(old_slots);
	free(old_keys);
}

static bool LinInsert(OpenTable* ht, ui key) {
	if ((float)(ht->count + 1) / ht->size > ht->max_load_factor)
		LinRehash(ht);
	
	ui key_hash		= get_hash(key, ht->size);
	ui start_key 	= key_hash;
	int del_ind		= -1;

	do {
		if (ht->slots[key_hash] == EMP)
			break;
		
		if (ht->slots[key_hash] == OCC && ht->keys[key_hash] == key)
			return false;
		
		if (ht->slots[key_hash] == DEL && del_ind == -1)
			del_ind = key_hash;

		key_hash = (key_hash + 1) % ht->size;
	} while (key_hash != start_key);

	ui res_ind = (del_ind != -1 ? del_ind : key_hash);

	ht->keys[res_ind] = key;
	ht->slots[res_ind] = OCC;

	++ht->count;
	return true;
}

static bool LinSearch(OpenTable* ht, ui key) {
	ui key_hash = get_hash(key, ht->size);

	ui start_key = key_hash;

	do {
		if (ht->slots[key_hash] == EMP)
			return false;

		if (ht->slots[key_hash] == OCC && ht->keys[key_hash] == key) 
			return true;

		key_hash = (key_hash + 1) % ht->size;
	} while (key_hash != start_key);

	return false;
}

static bool LinRemove(OpenTable* ht, ui key) {
	ui key_hash = get_hash(key, ht->size);
	
	ui start_key = key_hash;

	do {
		if (ht->slots[key_hash] == EMP)
			return false;

		if (ht->slots[key_hash] == OCC && ht->keys[key_hash] == key) {
			ht->slots[key_hash] = DEL;
			--ht->count;
			return true;
		}

		key_hash = (key_hash + 1) % ht->size;
	} while (key_hash != start_key);

	return false;
}

#endif