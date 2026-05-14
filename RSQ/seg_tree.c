#include "seg_tree.h"

static int	RecFindSum		(SegTree* tree, int ind, 
							int lt,	  int rt, 
							int q_lt, int q_rt);

static void RecChangeVal	(SegTree* tree, int ind, 
							int lt, int rt, 
							int q_ind, int q_val);

int FindSum(SegTree* tree, int q_lt, int q_rt) {
	TREE_VERIFY(tree);
	ASSERT(0 <= q_lt && q_rt <= tree->size, "Недопустимые границы отрезка\n");

	return RecFindSum(tree, 0, 0, tree->size, q_lt, q_rt);
}

void ChangeVal(SegTree* tree, int ind, int val) {
	TREE_VERIFY(tree);
	ASSERT(0 <= ind < tree->size, "Неправильный индекс замены значения\n");

	RecChangeVal(tree, 0, 0, tree->size, ind, val);
}

static int RecFindSum(SegTree* tree, int ind, int lt, int rt, int q_lt, int q_rt) {
	TREE_VERIFY(tree);
	ASSERT(0 <= ind < 2 * tree->size,	"Неправильный индекс вершины\n");
	
	if (rt <= q_lt || q_rt <= lt)	return NEUTRAL_ELEM;

	if (q_lt <= lt && rt <= q_rt)	return GetSum(&tree->nodes[ind]);

	int m = (lt + rt) / 2;
	return	RecFindSum(tree, 2 * ind + 1, lt, m, q_lt, q_rt) +
			RecFindSum(tree, 2 * ind + 2, m, rt, q_lt, q_rt);
}

static void RecChangeVal(SegTree* tree, int ind, int lt, int rt, int q_ind, int q_val) {
	TREE_VERIFY(tree);
	ASSERT(0 <= ind < 2 * tree->size,	"Неправильный индекс вершины\n");
	
	if (rt <= ind || ind < lt)	return;

	if (lt + 1 == rt) {
		tree->nodes[ind].sum = q_val;
		return;
	}

	int m = (lt + rt) / 2;
	RecChangeVal(tree, 2 * ind + 1, lt, m, q_ind, q_val);
	RecChangeVal(tree, 2 * ind + 2, m, rt, q_ind, q_val);

	tree->nodes[ind].sum = NodeMerge(&tree->nodes[2 * ind + 1], &tree->nodes[2 * ind + 2]);
}

SegTree* SegTreeArrCtor(int size, int* arr) {
	SegTree* tree = SegTreeCtor(size);
	ASSERT(tree, "Не удалось создать дерево\n");

	TreeNode* nodes = tree->nodes;
	for (int ind = tree->size - 1, arr_ind = 0; ind < 2 * tree->size; ++ind, ++arr_ind)
		nodes[ind].sum = arr[arr_ind];
	
	for (int ind = tree->size - 2; ind >= 0; --ind)
		nodes[ind].sum = NodeMerge(&nodes[2 * ind + 1], &nodes[2 * ind + 2]);

	return tree;
}

SegTree* SegTreeCtor(int size) {
	int pow_size = 1;
	while (pow_size < size) pow_size <<= 1;

	SegTree* tree = (SegTree*)calloc(1, sizeof(SegTree));
	ASSERT(tree, "CALLOC ERROR: Не удалось создать дерево\n");
	
	tree->size	= pow_size;
	tree->nodes	= (TreeNode*)calloc(2 * pow_size, sizeof(TreeNode));
	ASSERT(tree->nodes, "CALLOC ERROR: Не удалось создать вершин\n");

	return tree;
}

void SegTreeDtor(SegTree* tree) {
	TREE_VERIFY(tree);

	for (int ind = 0; ind < 2 * tree->size; ++ind)
		tree->nodes[ind].sum = NEUTRAL_ELEM;
	
	tree->size = 0;
	free(tree->nodes);

	free(tree);
}

int NodeMerge(TreeNode* left, TreeNode* right) {
	return GetSum(left) + GetSum(right);
}

int GetSum(TreeNode* node) {
	if (!node)	return NEUTRAL_ELEM;

	return node->sum;
}
