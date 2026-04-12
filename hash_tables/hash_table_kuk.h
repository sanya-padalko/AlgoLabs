#ifndef _HASH_TABLE_KUK_
#define _HASH_TABLE_KUK_

#include "hash_table_open.h"
#include "../hash_func.h"

#define MAX_ITERS 100

static ui kuk_hash_1(ui key, int size) {
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = (key >> 16) ^ key;
    return key % size;
}

static ui kuk_hash_2(ui key, int size) {
    key = (key ^ 61) ^ (key >> 16);
    key = key + (key << 3);
    key = key ^ (key >> 4);
    key = key * 0x27d4eb2d;
    key = key ^ (key >> 15);
    return key % size;
}

static void KukRehash(OpenTable* ht);
static bool KukSearch(OpenTable* ht, ui key);

static bool DumbKukInsert(OpenTable* ht, ui key) {
    ui cur_key = key;
    for (int i = 0; i < MAX_ITERS; ++i) {
        ui h1 = kuk_hash_1(cur_key, ht->size);
        if (ht->slots[h1] == EMP) {
            ht->keys[h1]  = cur_key;
            ht->slots[h1] = OCC;
            ++ht->count;
            return true;
        }

        ui old_key = ht->keys[h1];
        ht->keys[h1] = cur_key;
        cur_key = old_key;

        ui h2 = kuk_hash_2(cur_key, ht->size);
        if (h1 == h2)
            h2 = (h2 + 1) % ht->size;
        if (ht->slots[h2] == EMP) {
            ht->keys[h2]  = cur_key;
            ht->slots[h2] = OCC;
            ++ht->count;
            return true;
        }

        old_key = ht->keys[h2];
        ht->keys[h2] = cur_key;
        cur_key = old_key;
    }
    return false;
}

static bool KukInsert(OpenTable* ht, ui key) {
    if (KukSearch(ht, key))
        return false;
    
    if ((float)ht->count / ht->size > ht->max_load_factor)
        KukRehash(ht);
    
    if (!DumbKukInsert(ht, key)) {
        KukRehash(ht);
        return DumbKukInsert(ht, key);
    }

    return true;
}

static void KukRehash(OpenTable* ht) {
	int old_size 		= ht->size;
	SlotType* old_slots = ht->slots;
	int* old_keys 		= ht->keys;

    bool flag = false;
    while (!flag) {

        ht->size  *=	2;
        ht->slots =		(SlotType*)calloc(ht->size, sizeof(SlotType));
        ht->keys  =		(int*)calloc(ht->size, sizeof(int));
        ht->count = 0;

        if (!ht->slots || !ht->keys) {
            fprintf(stderr, "Zalupa with size = %d\n", ht->size);
            exit(1);
        }

        flag = true;
        for (int i = 0; i < old_size; ++i) {
            if (old_slots[i] == OCC) {
                if (!DumbKukInsert(ht, old_keys[i])) {
                    flag = false;
                    free(ht->slots);
                    free(ht->keys);
                    break;
                }
            }
        }
    }

    free(old_slots);
    free(old_keys);
}

static bool KukSearch(OpenTable* ht, ui key) {
    ui key_hash_1 = kuk_hash_1(key, ht->size);
    if (ht->slots[key_hash_1] == OCC && ht->keys[key_hash_1] == key)
        return true;

    ui key_hash_2 = kuk_hash_2(key, ht->size);
    if (ht->slots[key_hash_2] == OCC && ht->keys[key_hash_2] == key)
        return true;

	return false;
}

static bool KukRemove(OpenTable* ht, ui key) {
	ui key_hash_1 = kuk_hash_1(key, ht->size);
    if (ht->slots[key_hash_1] == OCC && ht->keys[key_hash_1] == key) {
        ht->slots[key_hash_1] = EMP;
        --ht->count;
        return true;
    }

    ui key_hash_2 = kuk_hash_2(key, ht->size);
    if (ht->slots[key_hash_2] == OCC && ht->keys[key_hash_2] == key) {
        ht->slots[key_hash_2] = EMP;
        --ht->count;
        return true;
    }

	return false;
}

#endif