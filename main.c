#include"avltree.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 1000000
NODE* to_next(NODE** root, NODE* it){
	if (it->right){
		it = it->right;
		while (it->left)it = it->left;
	}
	else if (it->parent&&it == it->parent->left)it = it->parent;
	else{
		while (it->parent&&it == it->parent->right)
			it = it->parent;
		it = it->parent;
	}
	return it;
}
int count(NODE** root){
	NODE* it = *root;
	int count = 0;
	if (it){
		while (it->left)it = it->left;
	}
	while (it){
		count++;
		it = to_next(root, it);
	}
	return count;
}
int depth(NODE* root){
	NODE* it = root;
	int d = 0;
	if (it)
		d = max(depth(it->left), depth(it->right)) + 1;
	return d;
}

int a[MAX];
int main(){
	NODE* root = NULL;
	double start;

	double result = 0;
	srand(time(NULL));
	for (int i = 0; i < MAX; i++){
		a[i] = i;
	}
	for (int i = 0; i < MAX; i++){
		int tmp = a[i];
		int r = rand() % MAX;
		a[i] = a[r];
		a[r] = tmp;
	}
	
	for (int j = 0; j < 100; j++){
		start = clock();
		for (int j = 0; j < MAX; j++){
			avl_insert(&root, a[j]);
		}
		result += (clock() - start) / CLOCKS_PER_SEC;
	}
	printf("%f\n", result/100);
	result = 0;

	for (int j = 0; j < 100; j++){
		start = clock();
		for (int j = 0; j < MAX; j++){
			NODE* it = find(&root, j);
			avl_erase(&root, it);
		}
		result += (clock() - start) / CLOCKS_PER_SEC;
	}
	printf("%f\n", result / 100);
	result = 0;

	for (int j = 0; j < 100; j++){
		start = clock();
		for (int j = 0; j < MAX; j++){
			bst_insert(&root, a[j]);
		}
		result += (clock() - start) / CLOCKS_PER_SEC;
	}
	printf("%f\n", result / 100);
	result = 0;

	for (int j = 0; j < 100; j++){
		start = clock();
		for (int j = 0; j < MAX; j++){
			NODE* it = find(&root, j);
			bst_erase(&root, it);
		}
		result += (clock() - start) / CLOCKS_PER_SEC;
	}
	printf("%f\n", result / 100);
	result = 0;
	return 0;
}