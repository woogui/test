#include"avltree.h"
#include<stdlib.h>

void balance_num(NODE* it){
	while (it->parent){
		if (it == it->parent->left)
			it->parent->Lheight = max(it->Lheight, it->Rheight) + 1;
		else
			it->parent->Rheight = max(it->Lheight, it->Rheight) + 1;
		it = it->parent;
		it->balance = it->Lheight - it->Rheight;
	}
}

void L_rotate(NODE** root, NODE* it){
	it->left->parent = it->parent;
	if (it->parent){
		if (it->parent->left == it)
			it->parent = it->parent->left = it->left;
		else
			it->parent = it->parent->right = it->left;
		it->left = it->parent->right;
		if (it->parent->right) it->parent->right->parent = it;
		it->parent->right = it;
	}
	else{
		it->parent = *root = it->left;
		it->left = it->parent->right;
		if (it->parent->right) it->parent->right->parent = it;
		(*root)->right = it;
	}
	if (it->left) it->Lheight = max(it->left->Lheight, it->left->Rheight) + 1;
	else it->Lheight = 0;
	it->balance = it->Lheight - it->Rheight;
	balance_num(it);
}
void R_rotate(NODE** root, NODE* it){
	it->right->parent = it->parent;
	if (it->parent){
		if (it == it->parent->right)
			it->parent = it->parent->right = it->right;
		else
			it->parent = it->parent->left = it->right;
		it->right = it->parent->left;
		if (it->parent->left) it->parent->left->parent = it;
		it->parent->left = it;
	}
	else{
		it->parent = *root = it->right;
		it->right = it->parent->left;
		if (it->parent->left) it->parent->left->parent = it;
		(*root)->left = it;
	}
	if (it->right) it->Rheight = max(it->right->Lheight, it->right->Rheight) + 1;
	else it->Rheight = 0;
	it->balance = it->Lheight - it->Rheight;
	balance_num(it);
}
void rebalance(NODE**root, NODE* it){
	while (it){
		if (it->balance > 1){
			if (it->left->balance < 0)
				R_rotate(root, it->left);
			L_rotate(root, it);
		}
		else if (it->balance < -1){
			if (it->right->balance > 0)
				L_rotate(root, it->right);
			R_rotate(root, it);
		}
		it = it->parent;
	}
}

void avl_insert(NODE** root, int key){
	NODE** c = root;
	NODE* parent = NULL;
	while (*c){
		parent = *c;
		if ((*c)->key == key)return;
		if ((*c)->key > key) c = &(**c).left;
		else c = &(**c).right;
	}
	*c = (NODE*)calloc(1, sizeof(NODE));
	(*c)->key = key;
	(*c)->parent = parent;
	NODE* it = *c;
	balance_num(it);
	rebalance(root, it);
}
void bst_insert(NODE** root, int key){
	NODE** c = root;
	NODE* parent = NULL;
	while (*c){
		parent = *c;
		if ((*c)->key == key)return;
		if ((*c)->key > key) c = &(**c).left;
		else c = &(**c).right;
	}
	*c = (NODE*)calloc(1, sizeof(NODE));
	(*c)->key = key;
	(*c)->parent = parent;
}

NODE* find(NODE** root, int key){
	NODE* it = *root;
	while (it){
		if (it->key == key) break;
		if (it->key > key) it = it->left;
		else it = it->right;
	}
	return it;
}

void transplant(NODE** root, NODE* dst, NODE* src){
	if (dst->parent == NULL)
		*root = src;
	else if (dst->parent->left == dst)
		dst->parent->left = src;
	else
		dst->parent->right = src;
	if (src)
		src->parent = dst->parent;
}
NODE* to_left(NODE* n){
	while (n && n->left)
		n = n->left;
	return n;
}
void avl_erase(NODE** root, NODE* it){
	NODE* cur;
	if (it == NULL)return;
	cur = it->parent;
	if (it->left)cur = it->left;
	else if (it->right)cur = it->right;
	if (it->left == NULL){
		transplant(root, it, it->right);
	}
	else if (it->right == NULL){
		transplant(root, it, it->left);
	}
	else{
		NODE* succ = to_left(it->right);
		if (succ->parent != it){
			transplant(root, succ, succ->right);
			succ->right = it->right;
			succ->right->parent = succ;
		}
		transplant(root, it, succ);
		succ->left = it->left;
		succ->left->parent = succ;
	}
	free(it);
	if (cur){
		balance_num(cur);
		rebalance(root, cur);
	}

}
void bst_erase(NODE** root, NODE* it){
	if (it == NULL)return;
	if (it->left == NULL){
		transplant(root, it, it->right);
	}
	else if (it->right == NULL){
		transplant(root, it, it->left);
	}
	else{
		NODE* succ = to_left(it->right);
		if (succ->parent != it){
			transplant(root, succ, succ->right);
			succ->right = it->right;
			succ->right->parent = succ;
		}
		transplant(root, it, succ);
		succ->left = it->left;
		succ->left->parent = succ;
	}
	free(it);
}