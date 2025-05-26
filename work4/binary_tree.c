
#include "binary_tree.h"
#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

binary_tree_t* new_binary_tree(void (*print)(node_t*)) {
	binary_tree_t* bt = (binary_tree_t*)malloc(sizeof(binary_tree_t));
	bt->root = (node_t*)malloc(sizeof(node_t*));
	bt->root->right = NULL;
	bt->root->left = NULL;
	bt->root->element = NULL;
	bt->print = print;
	return bt;
}

node_t* new_node(void* element) {
	node_t* n = (node_t*)malloc(sizeof(node_t));
	n->right = NULL;
	n->left = NULL;
	n->element = element;
	return n;
}

void inOrder_traversal(binary_tree_t* bt, node_t* n) {
	if(n != NULL) {
		inOrder_traversal(bt, n->left);
		bt->print(n);
		inOrder_traversal(bt, n->right);
	}
}

void preOrder_traversal(binary_tree_t* bt, node_t* n) {
	if(n != NULL) {
		bt->print(n);
		preOrder_traversal(bt, n->left);
		preOrder_traversal(bt, n->right);
	}
}

void postOrder_traversal(binary_tree_t* bt, node_t* n) {
	if(n != NULL) {
		postOrder_traversal(bt, n->left);
		postOrder_traversal(bt, n->right);
		bt->print(n);
	}
}

void levelOrder_traversal(binary_tree_t* bt, node_t* n) {
	queue_t* node_q = new_queue(1000, NULL);
	node_t* current_n;
	if(current_n != NULL) {
		enqueue_queue(node_q, n);
	}
	while(!queue_is_empty(node_q)) {
		current_n = dequeue_queue(node_q);
		if(current_n->left != NULL) { enqueue_queue(node_q, current_n->left); }
		if(current_n->right != NULL) { enqueue_queue(node_q, current_n->right); }
		bt->print((node_t*)current_n);
	}
}

void left_rotate(node_t* x) {
	node_t* y;
	y = x->right;
	x->right = y->left;	
	y->left = x;
}




