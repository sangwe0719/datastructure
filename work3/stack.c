
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

stack_t* new_stack(int size, void (*print)(void*)) {
    stack_t* s = malloc(sizeof(stack_t));
    s->data = malloc(size * sizeof(void*));
    s->size = size;
    s->top = -1;
    s->print = print;
    return s;
}

void delete_stack(stack_t* s) {
    free(s->data);
    free(s);
}

void push_stack(stack_t* s, void* item) {
    if (stack_is_full(s)) {
        printf("Stack is full\n");
        return;
    }
    s->data[++s->top] = item;
}
void* pop_stack(stack_t* s) {
    if (stack_is_empty(s)) {
        printf("Stack is empty\n");
        return NULL;
    }
    void* item = s->data[s->top--];
    return item;
}

void print_stack(stack_t* s, char* name) {
    printf("%s\n", name);
    for (int i = 0; i <= s->top; i++) {
        s->print(s->data[i]);
    }
    printf("\n");
}

//연산자 우선순위 비교
void* peek_stack(stack_t* s) {
    if (stack_is_empty(s)) return NULL;
    return s->data[s->top];
}

int stack_is_empty(stack_t* s) {
    return (s->top == -1);
}
int stack_is_full(stack_t* s) {
    return (s->top == s->size - 1);
}