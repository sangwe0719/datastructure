#include "huffman_tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char ch;
    char code[256];
} code_entry_t;

static code_entry_t table[256];  // 문자 → 이진 코드 매핑 테이블
static int table_size = 0;       // 테이블에 저장된 항목 수
static int freq[256] = {0};      // 각 문자 빈도수 저장

// 노드의 빈도수 추출 (우선순위 큐용)
int get_node_freq(void* ptr) {
    return ((huff_element_t*)((node_t*)ptr)->element)->freq;
}

// 새 Huffman 노드 생성
node_t* new_huff_node(char ch, int freq) {
    huff_element_t* he = malloc(sizeof(huff_element_t));
    he->ch = ch;
    he->freq = freq;
    return new_node(he);
}

// 입력 문자열로부터 Huffman 트리 생성
binary_tree_t* build_huffman_tree(const char* input) {
    memset(freq, 0, sizeof(freq));
    for (int i = 0; input[i]; ++i) {
        freq[(unsigned char)input[i]]++;  // 문자 빈도 계산
    }

    // 우선순위 큐 생성 및 초기 노드 삽입
    queue_t* q = new_queue(512, NULL);
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            node_t* n = new_huff_node(i, freq[i]);
            priority_enqueue_queue(q, n, get_node_freq);
        }
    }

    // 최소 빈도수 노드 2개씩 꺼내 합치면서 트리 생성
    while (q->count > 1) {
        node_t* left = dequeue_queue(q);
        node_t* right = dequeue_queue(q);

        int total_freq = get_node_freq(left) + get_node_freq(right);
        node_t* parent = new_huff_node(0, total_freq);
        parent->left = left;
        parent->right = right;

        priority_enqueue_queue(q, parent, get_node_freq);
    }

    binary_tree_t* tree = new_binary_tree(NULL);
    tree->root = dequeue_queue(q);
    delete_queue(q);
    return tree;
}

// Huffman 트리를 따라 각 리프 노드에 이진 코드 부여
void generate_codes(node_t* root, char* path, int depth) {
    if (!root) return;
    huff_element_t* he = (huff_element_t*)root->element;

    if (!root->left && !root->right) {
        path[depth] = '\0';
        table[table_size].ch = he->ch;
        strcpy(table[table_size].code, path);
        table_size++;
        return;
    }

    path[depth] = '0';
    generate_codes(root->left, path, depth + 1);
    path[depth] = '1';
    generate_codes(root->right, path, depth + 1);
}

// Huffman 코드 테이블 출력
void print_code_table() {
    for (int i = 0; i < table_size; ++i) {
        printf("%c : %s\n", table[i].ch, table[i].code);
    }
}

// 입력 문자열을 이진 Huffman 코드로 인코딩
char* encode(const char* input) {
    static char buffer[10000];
    buffer[0] = '\0';
    for (int i = 0; input[i]; ++i) {
        for (int j = 0; j < table_size; ++j) {
            if (input[i] == table[j].ch) {
                strcat(buffer, table[j].code);
                break;
            }
        }
    }
    return buffer;
}

// Huffman 트리를 기반으로 인코딩된 문자열을 원래 문자열로 디코딩
char* decode(binary_tree_t* tree, const char* encoded) {
    size_t len = strlen(encoded);
    char* output = malloc(len + 1);  // 디코딩된 문자열 저장할 동적 버퍼
    int pos = 0;
    node_t* cur = tree->root;
    for (int i = 0; encoded[i]; ++i) {
        if (encoded[i] == '0') cur = cur->left;
        else cur = cur->right;

        if (!cur->left && !cur->right) {
            output[pos++] = ((huff_element_t*)cur->element)->ch;
            cur = tree->root;
        }
    }
    output[pos] = '\0';
    return output;
}
