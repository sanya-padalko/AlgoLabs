#include "hash_table_kuk.h"

bool KukInsert(OpenTable* table, uint32_t key) {
    if (KukSearch(table, key))
        return false;
    
    if ((float)table->count / table->size > table->max_load_factor)
        KukRehash(table);
    
    if (!DumbKukInsert(table, key)) {
        KukRehash(table);
        return DumbKukInsert(table, key);
    }

    return true;
}

bool KukSearch(OpenTable* table, uint32_t key) {
    uint32_t key_hash_1 = kuk_hash_1(key, table->size);
    if (table->slots[key_hash_1] == OCC && table->keys[key_hash_1] == key)
        return true;

    uint32_t key_hash_2 = kuk_hash_2(key, table->size);
    if (table->slots[key_hash_2] == OCC && table->keys[key_hash_2] == key)
        return true;

	return false;
}

bool KukRemove(OpenTable* table, uint32_t key) {
	uint32_t key_hash_1 = kuk_hash_1(key, table->size);
    if (table->slots[key_hash_1] == OCC && table->keys[key_hash_1] == key) {
        table->slots[key_hash_1] = EMP;
        --table->count;
        return true;
    }

    uint32_t key_hash_2 = kuk_hash_2(key, table->size);
    if (table->slots[key_hash_2] == OCC && table->keys[key_hash_2] == key) {
        table->slots[key_hash_2] = EMP;
        --table->count;
        return true;
    }

	return false;
}

void KukRehash(OpenTable* table) {
	int old_size 		= table->size;
	SlotType* old_slots = table->slots;
	int* old_keys 		= table->keys;

    bool flag = false;
    while (!flag) {

        table->size  *=	2;
        table->slots =		(SlotType*)calloc(table->size, sizeof(SlotType));
        table->keys  =		(int*)calloc(table->size, sizeof(int));
        table->count = 0;

        flag = true;
        for (int i = 0; i < old_size; ++i) {
            if (old_slots[i] == OCC) {
                if (!DumbKukInsert(table, old_keys[i])) {
                    flag = false;
                    free(table->slots);
                    free(table->keys);
                    break;
                }
            }
        }
    }

    free(old_slots);
    free(old_keys);
}

bool DumbKukInsert(OpenTable* table, uint32_t key) {
    uint32_t cur_key = key;
    for (int i = 0; i < MAX_ITERS; ++i) {
        uint32_t h1 = kuk_hash_1(cur_key, table->size);
        if (table->slots[h1] == EMP) {
            table->keys[h1]  = cur_key;
            table->slots[h1] = OCC;
            ++table->count;
            return true;
        }

        uint32_t old_key = table->keys[h1];
        table->keys[h1] = cur_key;
        cur_key = old_key;

        uint32_t h2 = kuk_hash_2(cur_key, table->size);
        if (h1 == h2)
            h2 = (h2 + 1) % table->size;
        if (table->slots[h2] == EMP) {
            table->keys[h2]  = cur_key;
            table->slots[h2] = OCC;
            ++table->count;
            return true;
        }

        old_key = table->keys[h2];
        table->keys[h2] = cur_key;
        cur_key = old_key;
    }
    return false;
}

uint32_t kuk_hash_1(uint32_t key, int size) {
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = (key >> 16) ^ key;
    return key % size;
}

uint32_t kuk_hash_2(uint32_t key, int size) {
    key = (key ^ 61) ^ (key >> 16);
    key = key + (key << 3);
    key = key ^ (key >> 4);
    key = key * 0x27d4eb2d;
    key = key ^ (key >> 15);
    return key % size;
}
