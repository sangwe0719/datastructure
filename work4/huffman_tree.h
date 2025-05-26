#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "binary_tree.h"
#include "queue.h"

typedef struct {
    char ch;
    int freq;
} huff_element_t;

binary_tree_t* build_huffman_tree(const char* input);
void generate_codes(node_t* root, char* path, int depth);
void print_code_table();
char* encode(const char* input);
char* decode(binary_tree_t* tree, const char* encoded);

#endif
