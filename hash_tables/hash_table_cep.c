#include "hash_table_cep.h"

bool CepInsert(CepTable* ht, int key) {
	if ((float)(ht->count + 1) / ht->size > ht->max_load_factor)
		CepRehash(ht);

	uint32_t key_hash = get_hash(key, ht->size);
	Node* cur_node = ht->buckets[key_hash];
	
	while (cur_node) {
		if (cur_node->key == key) 
			return false;

		cur_node = cur_node->next;
	}

	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->key = key;
	new_node->next = ht->buckets[key_hash];
	ht->buckets[key_hash] = new_node;
	
	++ht->count;
	return true;
}

bool CepSearch(CepTable* ht, int key) {
	uint32_t key_hash = get_hash(key, ht->size);
	Node* cur_node = ht->buckets[key_hash];

	while (cur_node) {
		if (cur_node->key == key) 
			return true;
	
		cur_node = cur_node->next;
	}

	return false;
}

bool CepRemove(CepTable* ht, int key) {
	uint32_t key_hash = get_hash(key, ht->size);
	Node* cur_node = ht->buckets[key_hash];
	Node* prev = NULL;

	while (cur_node) {
		if (cur_node->key == key) {
			if (prev) {
				prev->next = cur_node->next;
			} 
			else {
				ht->buckets[key_hash] = cur_node->next;
			}

			free(cur_node);
			--ht->count;

			return true;
		}

		prev = cur_node;
		cur_node = cur_node->next;
	}

	return false;
}

void CepRehash(CepTable* ht) {
	int old_size		= ht->size;
	Node** old_buckets	= ht->buckets;

	ht->size 	*= 	2;
	ht->buckets = 	(Node**)calloc(ht->size, sizeof(Node*));
	
	for (int i = 0; i < old_size; ++i) {
		Node* cur_node = old_buckets[i];
		while (cur_node) {
			CepInsertKey(ht, cur_node->key);
			cur_node = cur_node->next;
		}

		ClearBucket(old_buckets[i]);
	}

	free(old_buckets);
}

void CepInsertKey(CepTable* ht, uint32_t key) {
	uint32_t key_hash = get_hash(key, ht->size);
	Node* node = (Node*)malloc(sizeof(Node));

	node->key = key;
	node->next = ht->buckets[key_hash];
	ht->buckets[key_hash] = node;
}

CepTable* CepTableCtor(int size, float lf) {
	CepTable* ht = (CepTable*)malloc(sizeof(CepTable));

	ht->size			= size;
	ht->count			= 0;
	ht->max_load_factor	= lf;
	ht->buckets			= (Node**)calloc(ht->size, sizeof(Node*));

	return ht;
}

void CepTableDtor(CepTable* ht) {
	for (int i = 0; i < ht->size; ++i)
		ClearBucket(ht->buckets[i]);

	free(ht->buckets);
	free(ht);
}

void ClearBucket(Node* node) {
	while (node) {
		Node* temp = node;
		node = node->next;
		free(temp);
	}
}

uint32_t get_hash(uint32_t key, int size) {
	return (uint32_t)(key * KNUTH_MUL) % size;
}
