#include "hash_table_cep.h"

bool CepInsert(CepTable* table, int key) {
	if ((float)(table->count + 1) / table->size > table->max_load_factor)
		CepRehash(table);

	uint32_t key_hash = get_hash(key, table->size);
	Node* cur_node = table->buckets[key_hash];
	
	while (cur_node) {
		if (cur_node->key == key) 
			return false;

		cur_node = cur_node->next;
	}

	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->key = key;
	new_node->next = table->buckets[key_hash];
	table->buckets[key_hash] = new_node;
	
	++table->count;
	return true;
}

bool CepSearch(CepTable* table, int key) {
	uint32_t key_hash = get_hash(key, table->size);
	Node* cur_node = table->buckets[key_hash];

	while (cur_node) {
		if (cur_node->key == key) 
			return true;
	
		cur_node = cur_node->next;
	}

	return false;
}

bool CepRemove(CepTable* table, int key) {
	uint32_t key_hash = get_hash(key, table->size);
	Node* cur_node = table->buckets[key_hash];
	Node* prev = NULL;

	while (cur_node) {
		if (cur_node->key == key) {
			if (prev) {
				prev->next = cur_node->next;
			} 
			else {
				table->buckets[key_hash] = cur_node->next;
			}

			free(cur_node);
			--table->count;

			return true;
		}

		prev = cur_node;
		cur_node = cur_node->next;
	}

	return false;
}

void CepRehash(CepTable* table) {
	int old_size		= table->size;
	Node** old_buckets	= table->buckets;

	table->size 	*= 	2;
	table->buckets = 	(Node**)calloc(table->size, sizeof(Node*));
	
	for (int i = 0; i < old_size; ++i) {
		Node* cur_node = old_buckets[i];
		while (cur_node) {
			CepInsertKey(table, cur_node->key);
			cur_node = cur_node->next;
		}

		ClearBucket(old_buckets[i]);
	}

	free(old_buckets);
}

void CepInsertKey(CepTable* table, uint32_t key) {
	uint32_t key_hash = get_hash(key, table->size);
	Node* node = (Node*)malloc(sizeof(Node));

	node->key = key;
	node->next = table->buckets[key_hash];
	table->buckets[key_hash] = node;
}

CepTable* CepTableCtor(int size, float lf) {
	CepTable* table = (CepTable*)malloc(sizeof(CepTable));

	table->size			= size;
	table->count			= 0;
	table->max_load_factor	= lf;
	table->buckets			= (Node**)calloc(table->size, sizeof(Node*));

	return table;
}

void CepTableDtor(CepTable* table) {
	for (int i = 0; i < table->size; ++i)
		ClearBucket(table->buckets[i]);

	free(table->buckets);
	free(table);
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
