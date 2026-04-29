#include <stdio.h>
#include <stdlib.h>

typedef struct BSTnode {
	int val;
	struct BSTnode* left;
	struct BSTnode* right;
} BSTnode;

BSTnode*	Insert		(BSTnode* node, int val);
BSTnode*	Delete		(BSTnode* node, int val);

BSTnode*	NodeCtor	(int val)				;
int			GetVal		(BSTnode* node)			;
BSTnode*	GetLeft		(BSTnode* node)			;
BSTnode*	GetRight	(BSTnode* node)			;