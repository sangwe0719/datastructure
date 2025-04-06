#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

void print_sort_result(int algorithm, int iteration, double time) {
    const char* sort_names[] = { "Selection Sort", "Bubble Sort", "Insertion Sort" };
    printf("Iteration %d - %s: Total time = %f s\n", iteration + 1, sort_names[algorithm], time);
}

int main() {
    int size;
    printf("Size of the Array: ");
    scanf("%d", &size);

    srand(time(NULL));  // 난수 시드 초기화 (한 번만 수행)

    for (int algorithm = 0; algorithm < 3; algorithm++) {
        float sum = 0;

        for (int iteration = 0; iteration < 5; iteration++) {
            int* random_numbers = generate_random_numbers(size);
            if (random_numbers == NULL) {
                return 1; // 메모리 할당 실패 시 종료
            }

              // 생성된 난수 출력
            /*
            printf("Random Array: \n");
            for (int i = 0; i < size; i++) {
                printf("%d ", random_numbers[i]);
            }
            printf("\n");
            */

            clock_t start = clock();

            // 정렬 알고리즘 
            switch (algorithm) {
                case 0: selectionsort(random_numbers, size); break;
                case 1: bubble(random_numbers, size); break;
                case 2: insertion(random_numbers, size); break;
            }

            clock_t end = clock();
            double cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;

            print_sort_result(algorithm, iteration, cpu_time_used);
            sum += cpu_time_used;

            // 배열 출력 
            /*
            printf("Sorted Array:\n");
            for (int i = 0; i < size; i++) {
                printf("%d ", random_numbers[i]);
            }
            printf("\n");
            */

            free(random_numbers);
        }

        printf("\nAverage Total time: %f s\n\n", sum / 5);
    }

    return 0;
}
