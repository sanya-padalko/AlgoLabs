#ifndef _AVL_H_
#define _AVL_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLnode {
	int		 val;
	int		 height;
	struct AVLnode* left;
	struct AVLnode* right;
} AVLnode;

AVLnode*	Insert		(AVLnode* node, int val);
AVLnode*	Delete		(AVLnode* root, int val);
void		ClearTree	(AVLnode* node)			;

AVLnode*	AVLnodeCtor	(int val)				;
void		NodeDtor	(AVLnode* node)			;

int			GetHeight	(AVLnode *node)			;
AVLnode*	GetLeft		(AVLnode* node)			;
AVLnode*	GetRight	(AVLnode* node)			;
int			GetBal		(AVLnode* node)			;

#endif