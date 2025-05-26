
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct node_t{
    struct node_t* right;
    struct node_t* left;
    void* element;
} node_t;

typedef struct {
    struct node_t* root;
    void (*print)(struct node_t* n);
} binary_tree_t;

binary_tree_t* new_binary_tree(void (*print)(node_t*));
node_t* new_node(void* element);

void left_rotate(node_t* n);

void inOrder_traversal(binary_tree_t* bt, node_t* n);
void preOrder_traversal(binary_tree_t* bt, node_t* n);
void postOrder_traversal(binary_tree_t* bt, node_t* n);
void levelOrder_traversal(binary_tree_t* bt, node_t* n);

#endif