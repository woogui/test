#ifndef DATA_STRUCTURE_AVL_16_07_21_WC
#define DATA_STRUCTURE_AVL_16_07_21_WC

typedef struct tagNODE NODE;
struct tagNODE{
	int key;
	int Lheight, Rheight, balance;
	NODE *left, *right, *parent;
};
void avl_insert(NODE** root, int key);

NODE* find(NODE** root, int key);

void avl_erase(NODE** root, NODE* it);

void bst_insert(NODE** root, int key);
void bst_erase(NODE** root, NODE* it);

#endif