#include "rbtree.h"

static RBnode NIL_NODE = {0, BLACK, &NIL_NODE, &NIL_NODE, &NIL_NODE};
static RBnode* NIL = &NIL_NODE;

static void NodeDtor(RBnode* node) {
	if (!node || node == NIL)   return;

	node->val   = 0;
	node->color = BLACK;
	node->left  = node->right = node->parent = NIL;
	
	free(node);
}

static RBnode* LeftRotate(RBnode* root, RBnode* x) {
	RBnode* y = GetRight(x);

	x->right = GetLeft(y);
	if (GetLeft(y) != NIL) y->left->parent = x;

	y->parent = x->parent;
	if (GetParent(x) == NIL)
		root = y;
	else if (x == GetLeft(GetParent(x))) 
		x->parent->left = y;
	else 
		x->parent->right = y;

	y->left = x;
	x->parent = y;
	return root;
}

static RBnode* RightRotate(RBnode* root, RBnode* y) {
	RBnode* x = GetLeft(y);

	y->left = GetRight(x);
	if (GetRight(x) != NIL) x->right->parent = y;

	x->parent = GetParent(y);
	if (GetParent(y) == NIL)
		root = x;
	else if (y == GetRight(GetParent(y))) 
		y->parent->right = x;
	else 
		y->parent->left = x;

	x->right = y;
	y->parent = x;
	return root;
}

static RBnode* InsertRepaint(RBnode* root, RBnode* z) {
	while (GetColor(GetParent(z)) == RED) {
		RBnode* p = GetParent(z);
		if (p == GetLeft(GetParent(p))) {
			RBnode* u = GetRight(GetParent(p));
			if (GetColor(u) == RED) {
				p->color		 = BLACK;
				u->color		 = BLACK;
				p->parent->color = RED;

				z = GetParent(p);
			}
			else {
				if (z == GetRight(p)) {
					z = p;
					root = LeftRotate(root, p);
				}

				z->parent->color		 = BLACK;
				z->parent->parent->color = RED;

				root = RightRotate(root, z->parent->parent);
			}
		}
		else {
			RBnode* u = GetLeft(GetParent(p));
			if (GetColor(u) == RED) {
				p->color				 = BLACK;
				u->color				 = BLACK;
				z->parent->parent->color = RED;

				z = GetParent(p);
			}
			else {
				if (z == GetLeft(p)) {
					z = p;
					root = RightRotate(root, z);
				}

				z->parent->color		 = BLACK;
				z->parent->parent->color = RED;

				root = LeftRotate(root, z->parent->parent);
			}
		}
	}

	root->color = BLACK;
	return root;
}

RBnode* Insert(RBnode* root, int val) {
	if (!root) root = NIL;

	RBnode* x = root;
	RBnode* y = NIL;
	RBnode* z = RBnodeCtor(val);

	while (x != NIL) {
		y = x;
		if (GetVal(z) < GetVal(x))
			x = GetLeft(x);
		else 
			x = GetRight(x);
	}

	z->parent = y;
	if (y == NIL)
		root = z;
	else if (GetVal(z) < GetVal(y))
		y->left = z;
	else 
		y->right = z;

	return InsertRepaint(root, z);
}

static RBnode* DeleteRepaint(RBnode* root, RBnode* x) {
    while (x != root && GetColor(x) == BLACK) {
		RBnode* p = GetParent(x);
        if (x == GetLeft(p)) {
            RBnode* y = GetRight(p);
            if (GetColor(y) == RED) { // если был черный брат
                y->color = BLACK;
                p->color = RED;
                root = LeftRotate(root, p); // LeftRotate

                y = GetRight(GetParent(x)); // теперь у X новый брат

            }

            if (GetColor(GetLeft(y)) == BLACK && GetColor(GetRight(y)) == BLACK) {
                y->color = RED;
                x = GetParent(x);
            }
			else {
                if (GetColor(GetRight(y)) == BLACK) { // делаем внешнего племянника красным
                    y->left->color = BLACK;
                    y->color = RED;
                    root = RightRotate(root, y);

                    y = GetRight(GetParent(x));
                }
				
                y->color		 = GetColor(GetParent(x));
                x->parent->color = BLACK;
                y->right->color	 = BLACK;
                root = LeftRotate(root, GetParent(x));
                x = root;
            }
        } else {
            RBnode* y = GetLeft(p);
            if (GetColor(y) == RED) {
                y->color = BLACK;
                p->color = RED;
                root = RightRotate(root, GetParent(x));

                y = GetLeft(GetParent(x));
            }

            if (GetColor(GetRight(y)) == BLACK && GetColor(GetLeft(y)) == BLACK) {
                y->color = RED;
                x = GetParent(x);
            }
			else {
                if (GetColor(GetLeft(y)) == BLACK) {
                    y->right->color = BLACK;
                    y->color		= RED;
                    root = LeftRotate(root, y);

                    y = GetLeft(GetParent(x));
                }

                y->color		 = GetColor(GetParent(x));
                x->parent->color = BLACK;
                y->left->color	 = BLACK;
                root = RightRotate(root, GetParent(x));
                x = root;
            }
        }
    }

    x->color = BLACK;
    return root;
}

static void ChangeSon(RBnode** root, RBnode* u, RBnode* v) {
    if (GetParent(u) == NIL)
		*root = v;
    else if (u == GetLeft(GetParent(u)))
		u->parent->left = v;
    else
		u->parent->right = v;

    v->parent = u->parent;
}

RBnode* Delete(RBnode* root, int val) {
    if (!root || root == NIL)
		return root;

    RBnode* x = root;
    while (x != NIL && GetVal(x) != val) {
        if (val < x->val)
			x = GetLeft(x);
        else 
			x = GetRight(x);
    }

    if (x == NIL)
		return root;

    RBnode* y = x;
    RBnode* z;
    Color last_color = GetColor(y);

    if (GetLeft(x) == NIL) {
        z = GetRight(x);
        ChangeSon(&root, x, z);
    } 
	else if (GetRight(x) == NIL) {
        z = GetLeft(x);
        ChangeSon(&root, x, z);
    } 
	else {
        y = GetRight(x);
        while (GetLeft(y) != NIL) 
			y = GetLeft(y);
        
        last_color = GetColor(y);
        z = GetRight(y);

        if (GetParent(y) != x) {
            ChangeSon(&root, y, GetRight(y));

            y->right		 = GetRight(x);
            y->right->parent = y;
        }

        ChangeSon(&root, x, y);
        y->left			= GetLeft(x);
        y->left->parent = y;
        y->color		= GetColor(x);
    }

    NodeDtor(x);

    if (last_color == BLACK)
        root = DeleteRepaint(root, z);

    return root;
}

RBnode* RBnodeCtor(int val) {
	RBnode* node = (RBnode*)calloc(1, sizeof(RBnode));
	MY_ASSERT(node, "calloc не сработал\n");

	node->val   = val;
	node->color = RED;
	node->left  = node->right = node->parent = NIL;

	return node;
}

void ClearTree(RBnode* node) {
	if (!node || node == NIL) return;

	ClearTree(GetLeft(node));
	ClearTree(GetRight(node));
	
	NodeDtor(node);
}

int		GetVal	 (RBnode* node)	{ return (node) ? node->val    :     0; }
Color	GetColor (RBnode* node)	{ return (node) ? node->color  : BLACK; }
RBnode* GetLeft  (RBnode* node)	{ return (node) ? node->left   :   NIL; }
RBnode* GetRight (RBnode* node)	{ return (node) ? node->right  :   NIL; }
RBnode* GetParent(RBnode* node)	{ return (node) ? node->parent :   NIL; }