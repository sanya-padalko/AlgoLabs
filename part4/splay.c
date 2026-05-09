#include "splay.h"

static SplayNode* RightRotate(SplayNode* node) {
	if (!node || !GetLeft(node))	return node;

	SplayNode* left	= GetLeft(node);
	node->left		= GetRight(left);
	left->right		= node;

	return left;
}

static SplayNode* LeftRotate(SplayNode* node) {
	if (!node || !GetRight(node))	return node;

	SplayNode* right	= GetRight(node);
	node->right			= GetLeft(right);
	right->left			= node;

	return right;
}

static SplayNode* ZigZig(SplayNode* node) {
	return RightRotate(RightRotate(node));
}

static SplayNode* ZagZag(SplayNode* node) {
	return LeftRotate(LeftRotate(node));
}

static SplayNode* ZigZag(SplayNode* node) {
	node->left = LeftRotate(GetLeft(node));
	return RightRotate(node);
}

static SplayNode* ZagZig(SplayNode* node) {
	node->right = RightRotate(GetRight(node));
	return LeftRotate(node);
}

static SplayNode* Splay(SplayNode* node, int val) {
	if (!node || GetVal(node) == val) return node;

	if (val < GetVal(node)) {
		if (!GetLeft(node)) return node;

		int left_val = GetVal(GetLeft(node));
		if (val < left_val) {
			node->left->left = Splay(GetLeft(GetLeft(node)), val);
			node = ZigZig(node);
		}
		
		if (val > left_val) {
			node->left->right = Splay(GetRight(GetLeft(node)), val);

			if (GetRight(GetLeft(node)))
				node = ZigZag(node);
		}

		if (val == left_val)
			node = RightRotate(node);

	}
	else {
		if (!GetRight(node)) return node;

		int right_val = GetVal(GetRight(node));
		if (val > right_val) {
			node->right->right = Splay(GetRight(GetRight(node)), val);
			node = ZagZag(node);
		}
		
		if (val < right_val) {
			node->right->left = Splay(GetLeft(GetRight(node)), val);

			if (GetLeft(GetRight(node)))
				node = ZagZig(node);
		}
		
		if (val == right_val)
			node = LeftRotate(node);
	}

	return node;
}

SplayNode* Insert(SplayNode* node, int val) {
	if (!node) return SplayNodeCtor(val);

	node = Splay(node, val);
	if (GetVal(node) == val) return node;

	SplayNode* new_node = SplayNodeCtor(val);
	if (val < GetVal(node)) {
		new_node->right = node;
		new_node->left  = GetLeft(node);
		node->left      = NULL;
	} 
	else {
		new_node->left  = node;
		new_node->right = GetRight(node);
		node->right     = NULL;
	}

	return new_node;
}

SplayNode* Delete(SplayNode* node, int val) {
	if (!node) return NULL;

	node = Splay(node, val);
	if (GetVal(node) != val) return node;

	SplayNode* last_node	= node;
	SplayNode* last_left	= GetLeft(node);
	SplayNode* last_right	= GetRight(node);
	if (!GetLeft(node)) {
		node = GetRight(node);
	}
	else if (!GetRight(node)) {
		node = GetLeft(node);
	}
	else {
		node = Splay(last_left, val);
		node->right = last_right;
	}

	NodeDtor(last_node);
	return node;
}

void ClearTree(SplayNode* node) {
	if (!node)	return;

	ClearTree(GetLeft(node));
	ClearTree(GetRight(node));
	
	NodeDtor(node);
}

SplayNode* SplayNodeCtor(int val) {
	SplayNode* node	=	(SplayNode*)calloc(1, sizeof(SplayNode));

	node->val		=	val;
	node->left		=	node->right	=	NULL;

	return node;
}

void NodeDtor(SplayNode* node) {
	node->val = 0;
	node->left = node->right = NULL;

	free(node);
}

SplayNode* GetLeft(SplayNode* node) {
	if (!node)	return NULL;

	return node->left;
}

SplayNode* GetRight(SplayNode* node) {
	if (!node)	return NULL;

	return node->right;
}

int GetVal(SplayNode* node) {
	if (!node)	return 0;

	return node->val;
}
