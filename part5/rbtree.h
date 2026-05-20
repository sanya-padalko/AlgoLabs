#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include "../asserts.h"

typedef enum { RED, BLACK } Color;

typedef struct RBnode {
	int		val;
	Color	color;
	struct RBnode* left;
	struct RBnode* right;
	struct RBnode* parent;
} RBnode;

RBnode*     Insert          (RBnode* root, int val);
RBnode*     Delete          (RBnode* root, int val);
void        ClearTree       (RBnode* root);

RBnode*     RBnodeCtor      (int val);

RBnode*     GetLeft         (RBnode* node);
RBnode*     GetRight        (RBnode* node);
RBnode*     GetParent       (RBnode* node);
int         GetVal          (RBnode* node);
Color       GetColor        (RBnode* node);

#endif