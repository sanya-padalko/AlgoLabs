#include "treap.h"

static void DDnodeDtor(DDnode* node) {
	if (!node)	return;
	
	node->val = node->prior = 0;
	node->left = node->right = NULL;

	free(node);
}

DDnode* Insert(DDnode* node, int val) {
	if (Check(&node, val))	return node;
	
	DDpair res = Split(node, val);

	return Merge(Merge(res.first, DDnodeCtor(val)), res.second);
}

DDnode* Delete(DDnode* node, int val) {
	DDpair res	= Split(node, val);
	DDpair res2 = Split(res.second, val + 1);

	return Merge(res.first, res2.second);
}

int Check(DDnode** node, int val) {
	DDpair res	= Split(*node, val);
	DDpair res2	= Split(res.second, val + 1);

	int result	= (int)(res2.first != NULL);
	*node = Merge(res.first, Merge(res2.first, res2.second));

	return result;
}

DDpair Split(DDnode* node, int val) {
	if (!node)	return DDpairCtor(NULL, NULL);

	if (GetVal(node) >= val) {
		DDpair res = Split(GetLeft(node), val);
		node->left = res.second;

		return DDpairCtor(res.first, node);
	}
	else {
		DDpair res = Split(GetRight(node), val);
		node->right = res.first;
		
		return DDpairCtor(node, res.second);
	}
}

DDnode* Merge(DDnode* node1, DDnode* node2) {
	if (!node1)	return node2;
	if (!node2)	return node1;

	if (GetPrior(node1) > GetPrior(node2)) {
		node1->right = Merge(GetRight(node1), node2);

		return node1;
	}
	else {
		node2->left = Merge(node1, GetLeft(node2));

		return node2;
	}
}

void ClearTree(DDnode* node) {
	if (!node)	return;

	ClearTree(GetLeft(node));
	ClearTree(GetRight(node));
	
	free(node);
}

DDnode* DDnodeCtor(int val) {
	DDnode* node	=	(DDnode*)calloc(1, sizeof(DDnode));
	MY_ASSERT(node, "calloc не сработал\n");

	node->val		=	val;
	node->prior		=	rand();
	
	node->left		=	node->right	=	NULL;

	return node;
}

DDpair DDpairCtor(DDnode* first, DDnode* second) {
	DDpair* pair_ptr	=	(DDpair*)calloc(1, sizeof(DDpair));
	MY_ASSERT(pair_ptr, "calloc не сработал\n");

	pair_ptr->first		=	first;
	pair_ptr->second	=	second;

	return *pair_ptr;
}

DDnode* GetLeft(DDnode* node) {
	if (!node)	return NULL;

	return node->left;
}

DDnode* GetRight(DDnode* node) {
	if (!node)	return NULL;

	return node->right;
}

int GetVal(DDnode* node) {
	if (!node)	return 0;

	return node->val;
}

int GetPrior(DDnode* node) {
	if (!node)	return 0;

	return node->prior;
}
