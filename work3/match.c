#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "match.h"

// 스택에 저장된 인덱스를 출력하는 함수 
void print_int(void* data) {
    printf("%d ", *(int*)data);
}

//   '('의 인덱스를 스택에 저장하고, ')'를 만나면 마지막 '('와 매칭한다.
//   짝이 맞는 괄호 쌍은 출력하고, 남은 괄호는 "unmatched"로 표시한다.
//   pa - 괄호가 포함된 수식 문자열
void match_parentheses(const char* pa) {
    stack_t* stack = new_stack(100, print_int); // 크기 100짜리 스택 생성

    printf("Input expression: %s\n", pa);

    for (int i = 0; pa[i]; i++) {
        if (pa[i] == '(') {
            // 여는 괄호 '(' 의 인덱스를 동적 할당해서 스택에 push
            int* idx = malloc(sizeof(int));
            *idx = i;
            push_stack(stack, idx);
        } else if (pa[i] == ')') {
            if (!stack_is_empty(stack)) {
                // 닫는 괄호 ')'가 나오면 '('를 pop하고 짝 출력
                int* left = (int*)pop_stack(stack);
                printf("Matched pair: (%d, %d)\n", *left, i);
                free(left);
            } else {
                // 짝이 없는 ')'일 경우
                printf("Unmatched ')' at index %d\n", i);
            }
        }
    }

    // 모든 수식을 처리한 후에도 스택에 남아있는 '('는 unmatched
    while (!stack_is_empty(stack)) {
        int* unmatched = (int*)pop_stack(stack);
        printf("Unmatched '(' at index %d\n", *unmatched);
        free(unmatched);
    }
    // 괄호 순서쌍이 맞아떨어져서 stack 비면
    if (stack_is_empty(stack)) {
        printf("Stack is empty\n");
    }

    delete_stack(stack); // 스택 메모리 해제
}