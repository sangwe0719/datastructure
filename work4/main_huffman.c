#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "huffman_tree.h"
#include "binary_tree.h"

int main() {
    char input[1000];  // 사용자 입력을 저장할 버퍼
    printf("Enter a sentence :\n");
    fgets(input, sizeof(input), stdin);  // 문자열 입력 (개행 포함)
    input[strcspn(input, "\n")] = 0;     // 문자열 끝의 개행 문자 제거

    // Huffman 트리 생성
    binary_tree_t* tree = build_huffman_tree(input);

    // Huffman 코드 테이블 생성
    char path[100];  // 코드 저장용 임시 버퍼
    generate_codes(tree->root, path, 0);

    // 코드 테이블 출력
    printf("\nHuffman Code Table:\n");
    print_code_table();

    // 입력 문자열을 인코딩
    char* encoded = encode(input);
    printf("\nEncoded string:\n%s\n", encoded);

    // 인코딩된 문자열을 디코딩
    char* decoded = decode(tree, encoded);
    printf("\nDecoded string:\n%s\n", decoded);

    free(decoded);  // malloc으로 받은 메모리 해제

    return 0;
}

