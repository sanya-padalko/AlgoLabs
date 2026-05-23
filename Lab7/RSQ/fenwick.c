#include "fenwick.h"

Fenwick* FenArrCtor(int size, int* arr) {
	Fenwick* tree = FenCtor(size);
	TREE_VERIFY(tree);

	for (int ind = 0; ind < size; ++ind)
		AddVal(tree, ind + 1, arr[ind]);
	
	TREE_VERIFY(tree);
	return tree;
}

void AddVal(Fenwick* tree, int ind, int delta) {
	TREE_VERIFY(tree);

	for (; ind <= tree->size; ind += ind & -ind)
		tree->pref[ind].sum += delta;

	TREE_VERIFY(tree);
}

int SegSum(Fenwick* tree, int lt, int rt) {
	TREE_VERIFY(tree);
	MY_ASSERT(lt >= 0 && rt <= tree->size, "Недопустимые границы отрезка\n");

	return PrefSum(tree, rt) - PrefSum(tree, lt - 1);
}

int PrefSum(Fenwick* tree, int ind) {
	TREE_VERIFY(tree);
	MY_ASSERT(ind <= tree->size, "Недопустимый префикс\n");

	int sum = NEUTRAL_ELEM;
	for (; ind > 0; ind -= ind & -ind)
		sum += tree->pref[ind].sum;
	
	TREE_VERIFY(tree);
	return sum;
}

Fenwick* FenCtor(int size) {
	MY_ASSERT(size >= 0, "Недопустимый размер дерева");

	Fenwick* tree = (Fenwick*)calloc(1, sizeof(Fenwick));

	tree->size = size;
	tree->pref = (FenNode*)calloc(size + 1, sizeof(FenNode));

	return tree;
}

void FenDtor(Fenwick* tree) {
	TREE_VERIFY(tree);

	tree->size = 0;
	free(tree->pref);

	free(tree);
}