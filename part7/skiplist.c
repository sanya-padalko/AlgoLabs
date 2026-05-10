#include "skiplist.h"

static int GetLevel() {
	int lvl = 0;
	while ((double)rand() / RAND_MAX < P_FACTOR && lvl < MAX_LEVEL - 1)
		++lvl;

	return lvl;
}

void Insert(SkipList* list, int val) {
	SkipNode* update[MAX_LEVEL];
	SkipNode* node = list->head;

	for (int i = list->cur_level; i >= 0; --i) {
		while (node->next[i] != NULL && node->next[i]->val < val)
			node = node->next[i];
		
		update[i] = node;
	}

	node = node->next[0];
	if (node && node->val == val) 
		return;

	int new_lvl = GetLevel();
	if (new_lvl > list->cur_level) {
		for (int i = list->cur_level + 1; i <= new_lvl; ++i) {
			update[i] = list->head;
		}

		list->cur_level = new_lvl;
	}

	SkipNode* new_node = SkipNodeCtor(val, new_lvl);
	for (int i = 0; i <= new_lvl; ++i) {
		new_node->next[i]  = update[i]->next[i];
		update[i]->next[i] = new_node;
	}
}

void Delete(SkipList* list, int val) {
	SkipNode* update[MAX_LEVEL];
	SkipNode* node = list->head;

	for (int i = list->cur_level; i >= 0; --i) {
		while (node->next[i] != NULL && node->next[i]->val < val)
			node = node->next[i];
		
		update[i] = node;
	}

	node = node->next[0];
	if (!node || node->val != val)
		return;

	for (int i = 0; i <= list->cur_level; ++i) {
		if (update[i]->next[i] != node) 
			break;

		update[i]->next[i] = node->next[i];
	}

	NodeDtor(node);

	while (list->cur_level > 0 && list->head->next[list->cur_level] == NULL)
		--list->cur_level;
}

SkipList* SkipListCtor() {
	SkipList* list	= (SkipList*)calloc(1, sizeof(SkipList));

	list->max_level	= MAX_LEVEL;
	list->cur_level	= 0;
	
	list->head		= SkipNodeCtor(INT_MIN, MAX_LEVEL);
	
	return list;
}

SkipNode* SkipNodeCtor(int val, int level) {
	SkipNode* node	= (SkipNode*)calloc(1, sizeof(SkipNode));

	node->val		= val;
	node->next		= (SkipNode**)calloc(level + 1, sizeof(SkipNode*));

	return node;
}

void ListDtor(SkipList* list) {
	if (!list)	return;
	
	SkipNode* node = list->head;
	while (node) {
		SkipNode* next = node->next[0];
		NodeDtor(node);
		node = next;
	}

	free(list);
}

void NodeDtor(SkipNode* node) {
	if (!node)	return;

	free(node->next);
	free(node);
}