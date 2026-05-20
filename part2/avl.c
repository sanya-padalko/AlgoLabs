#include "avl.h"

static int max(int a, int b) {
	if (a >= b) return a;

	return b;
}

static void Update(AVLnode* node) {
	int hl = GetHeight(GetLeft(node));
	int hr = GetHeight(GetRight(node));
	if (hl < hr)
		hl = hr;

	node->height = hl + 1;
}

static AVLnode* RightRotate(AVLnode* node) {
	if (!node || !GetLeft(node))	return node;

	AVLnode* left	= GetLeft(node);
	node->left		= GetRight(left);
	left->right		= node;

	Update(node);
	Update(left);

	return left;
}

static AVLnode* LeftRotate(AVLnode* node) {
	if (!node || !GetRight(node))	return node;

	AVLnode* right	= GetRight(node);
	node->right		= GetLeft(right);
	right->left		= node;

	Update(node);
	Update(right);

	return right;
}

static AVLnode* BigRightRotate(AVLnode* node) {
	node->left = LeftRotate(GetLeft(node));
	Update(node);

	return RightRotate(node);
}

static AVLnode* BigLeftRotate(AVLnode* node) {
	node->right = RightRotate(GetRight(node));
	Update(node);

	return LeftRotate(node);
}

AVLnode* Insert(AVLnode* node, int val) {
	if (node == NULL)   return AVLnodeCtor(val);

	if (val < node->val) {
		node->left = Insert(node->left, val);
	} else if (val > node->val) {
		node->right = Insert(node->right, val);
	} else {
		return node;
	}

	Update(node);
	int bal = GetBal(node);

	if (bal > 1 && val > GetRight(node)->val)
		return LeftRotate(node);
	
	if (bal < -1 && val < GetLeft(node)->val)
		return RightRotate(node);

	if (bal > 1 && val < GetRight(node)->val)
		return BigLeftRotate(node);
	
	if (bal < -1 && val > GetLeft(node)->val)
		return BigRightRotate(node);
	
	return node;
}

static AVLnode* MinValNode(AVLnode* node) {
	AVLnode* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

AVLnode* Delete(AVLnode* node, int val) {
	if (node == NULL) return node;

	if (val < node->val) {
		node->left	= Delete(GetLeft(node), val);
	} else if (val > node->val) {
		node->right	= Delete(GetRight(node), val);
	} else {
		AVLnode* last_node = node;

		if (GetLeft(node) == NULL) {
			node = GetRight(node);
			free(last_node);
		} else if (GetRight(node) == NULL) {
			node = GetLeft(node);
			free(last_node);
		} else {
			node->val	= MinValNode(GetRight(node))->val;
			node->right = Delete(GetRight(node), node->val);
		}
	}

	if (!node)	return node;

	Update(node);
	int bal = GetBal(node);

	if (bal < -1 && GetBal(GetLeft(node)) <= 0)
		return RightRotate(node);

	if (bal < -1 && GetBal(GetLeft(node)) > 0)
		return BigRightRotate(node);

	if (bal > 1 && GetBal(GetRight(node)) >= 0)
		return LeftRotate(node);

	if (bal > 1 && GetBal(GetRight(node)) > 0)
		return BigLeftRotate(node);

	return node;
}

void ClearTree(AVLnode* node) {
	if (!node)	return;

	ClearTree(GetLeft(node));
	ClearTree(GetRight(node));

	NodeDtor(node);
}

AVLnode* AVLnodeCtor(int val) {
	AVLnode* node = (AVLnode*)calloc(1, sizeof(AVLnode));
	MY_ASSERT(node, "calloc не сработал\n");

	node->val    = val;
	node->left   = node->right = NULL;
	node->height = 1;

	return node;
}

void NodeDtor(AVLnode* node) {
	node->val = node->height = 0;
	node->left = node->right = NULL;

	free(node);
}

int GetHeight(AVLnode *node) {
	if (!node)  return 0;

	return node->height;
}

AVLnode* GetLeft(AVLnode* node) {
	if (!node)  return NULL;

	return node->left;
}

AVLnode* GetRight(AVLnode* node) {
	if (!node)  return NULL;

	return node->right;
}

int GetBal(AVLnode* node) {
	if (!node)  return 0;

	return GetHeight(GetRight(node)) - GetHeight(GetLeft(node));
}
