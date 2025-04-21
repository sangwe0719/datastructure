#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"
#include "postfix.h"

// 연산자의 우선순위를 반환하는 함수
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;  // 덧셈, 뺄셈 우선순위 1
    } else if (op == '*' || op == '/' || op == '%') {
        return 2;  // 곱셈, 나눗셈, 나머지 우선순위 2
    } else {
        return 0;  
    }
}

// 스택 top 연산자의 우선순위가 현재 연산자보다 높거나 같은지 확인
int is_higher_precedence(char top, char current) {
    return precedence(top) >= precedence(current);
}

//   expr - 중위 수식 문자열
void infix_to_postfix(const char* expr) {
    stack_t* op_stack = new_stack(100, NULL); // 연산자 스택

    printf("Infix: %s\n", expr);
    printf("Postfix: ");

    for (int i = 0; expr[i]; i++) {
        char ch = expr[i];

        if (isspace(ch)) continue; // 공백은 무시

        if (isalnum(ch)) {
            // 피연산자는 바로 출력
            printf("%c", ch);
        } else if (ch == '(') {
            // '('는 스택에 push
            char* c = malloc(sizeof(char)); *c = ch;
            push_stack(op_stack, c);
        } else if (ch == ')') {
            // ')'가 나오면 '('가 나올 때까지 pop해서 출력
            while (!stack_is_empty(op_stack)) {
                char* top = (char*)pop_stack(op_stack);
                if (*top == '(') {
                    free(top);
                    break;
                }
                printf("%c", *top);
                free(top);
            }
        } else {
            // 연산자 처리: 우선순위가 높은 연산자는 먼저 출력
            while (!stack_is_empty(op_stack)) {
                char* top = (char*)peek_stack(op_stack);
                if (*top == '(' || !is_higher_precedence(*top, ch)) break;
                printf("%c", *((char*)pop_stack(op_stack)));
                free(top);
            }
            // 현재 연산자를 push
            char* c = malloc(sizeof(char)); *c = ch;
            push_stack(op_stack, c);
        }
    }

    // 남아있는 연산자 모두 출력
    while (!stack_is_empty(op_stack)) {
        char* top = (char*)pop_stack(op_stack);
        printf("%c", *top);
        free(top);
    }

    printf("\n");
    delete_stack(op_stack); // 스택 메모리 해제
}