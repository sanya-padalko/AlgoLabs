#include "bst.h"

BSTnode* Insert(BSTnode* node, int val) {
	if (!node)	return NodeCtor(val);

	int node_val = GetVal(node);
	if (val == node_val)
		return node;

	if (val < node_val)
		node->left = Insert(GetLeft(node), val);
	else
		node->right = Insert(GetRight(node), val);
	
	return node;
}

BSTnode* Delete(BSTnode* node, int val) {
	if (!node)	return NULL;

	BSTnode* left = GetLeft(node);
	BSTnode* right = GetRight(node);

	if (val == GetVal(node)) {
		if (left == NULL)	return right;
		if (right == NULL)	return left;

		BSTnode* last_node = node;
		while (GetLeft(right)) {
			last_node = right;
			right = GetLeft(right);
		}
		
		if (right == GetLeft(last_node))
			last_node->left = GetRight(right);
		else
			last_node->right = GetRight(right);
		
		right->left = GetLeft(node);
		right->right = GetRight(node);

		return right;
	}

	if (val < GetVal(node))
		node->left = Delete(left, val);
	else 
		node->right = Delete(right, val);
	
	return node;
}

BSTnode* NodeCtor(int val) {
	BSTnode* node = (BSTnode*)calloc(1, sizeof(BSTnode));

	node->val = val;
	node->left = node->right = NULL;

	return node;
}

int GetVal(BSTnode* node) {
	if (!node)	return 0;

	return node->val;
}

BSTnode* GetLeft(BSTnode* node) {
	if (!node)	return NULL;

	return node->left;
}

BSTnode* GetRight(BSTnode* node) {
	if (!node)	return NULL;

	return node->right;
}