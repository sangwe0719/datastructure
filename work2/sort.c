#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

// 난수 배열 생성 함수 (범위: 10000~100000)
int* generate_random_numbers(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (100001 - 10000) + 10000;
    }

    return arr;
}

// 선택 정렬 (Selection Sort)
void selectionsort(int* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (a[k] > a[j]) {
                k = j;
            }
        }
        int temp = a[k];
        a[k] = a[i];
        a[i] = temp;
    }
}

// 삽입 정렬 (Insertion Sort)
void insertion(int* a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i;

        while (j > 0 && a[j - 1] > key) {
            a[j] = a[j - 1];
            j--;
        }

        a[j] = key;
    }
}

// 버블 정렬 (Bubble Sort)
void bubble(int* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}
