#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct {
    void** data;
    int size;
    int count;
    void (*print)(void*);
} queue_t;

queue_t* new_queue(int size, void (*print)(void*));
void delete_queue(queue_t* q);

void enqueue_queue(queue_t* q, void* item); // 일반 FIFO 삽입
void* dequeue_queue(queue_t* q);           // 앞에서 제거

void priority_enqueue_queue(queue_t* q, void* item, int (*get_priority)(void*)); // 빈도 기반 삽입

int queue_is_empty(queue_t* q);
int queue_is_full(queue_t* q);
void print_queue(queue_t* q, const char* name);

#endif
