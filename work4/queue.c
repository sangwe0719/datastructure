#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

queue_t* new_queue(int size, void (*print)(void*)) {
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    q->data = (void**)malloc(sizeof(void*) * size);
    q->size = size;
    q->count = 0;
    q->print = print;
    return q;
}

void delete_queue(queue_t* q) {
    if (!q) return;
    free(q->data);
    free(q);
}

void enqueue_queue(queue_t* q, void* item) {
    if (queue_is_full(q)) {
        printf("Queue is full\n");
        return;
    }
    q->data[q->count++] = item;
}

void* dequeue_queue(queue_t* q) {
    if (queue_is_empty(q)) {
        printf("Queue is empty\n");
        return NULL;
    }
    void* item = q->data[0];
    for (int i = 1; i < q->count; ++i) {
        q->data[i - 1] = q->data[i];
    }
    q->count--;
    return item;
}

void priority_enqueue_queue(queue_t* q, void* item, int (*get_priority)(void*)) {
    if (queue_is_full(q)) {
        printf("Queue is full\n");
        return;
    }
    int i = q->count - 1;
    while (i >= 0 && get_priority(q->data[i]) > get_priority(item)) {
        q->data[i + 1] = q->data[i];
        i--;
    }
    q->data[i + 1] = item;
    q->count++;
}

int queue_is_empty(queue_t* q) {
    return q->count == 0;
}

int queue_is_full(queue_t* q) {
    return q->count == q->size;
}

void print_queue(queue_t* q, const char* name) {
    printf("%s\n", name);
    for (int i = 0; i < q->count; ++i) {
        q->print(q->data[i]);
    }
    printf("\n");
}
