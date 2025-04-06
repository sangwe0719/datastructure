#ifndef SORT_H
#define SORT_H

// 정렬 함수 선언들
void bubble(int* a, int n);           // 버블 정렬
void insertion(int* a, int n);        // 삽입 정렬
void selectionsort(int* a, int n);    // 선택 정렬

// 난수 배열 생성 함수
int* generate_random_numbers(int size);

#endif
