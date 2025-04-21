
#ifndef STACK_H
#define STACK_H

typedef struct stack_t {
    void** data;
    int size;
    int top;

    void (*print)(void*);
} stack_t;


stack_t* new_stack(int size, void (*print)(void*));
void delete_stack(stack_t* stack);

void push_stack(stack_t* stack, void* item);
void* pop_stack(stack_t* stack);

void print_stack(stack_t* stack, char* name);
void* peek_stack(stack_t* stack);

int stack_is_empty(stack_t* stack);
int stack_is_full(stack_t* stack);

#endif