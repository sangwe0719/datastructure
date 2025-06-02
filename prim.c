#include <stdio.h>
#include <limits.h>
#include "prim.h"

/*
 * minKey:
 *   key[] 배열에서 아직 MST에 포함되지 않은 정점(visited[v] == 0) 중
 *   key 값이 최소인 정점 인덱스를 찾아서 리턴
 */
static int minKey(int key[], int visited[], int numVertices) {
    int min = INT_MAX;
    int minIndex = -1;
    for (int v = 0; v < numVertices; v++) {
        if (visited[v] == 0 && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

/*
 primMST
 */
void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices, int parent[]) {
    int key[MAX_VERTICES];
    int visited[MAX_VERTICES];

    // 초기화
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    // 임의로 정점 0을 시작 정점으로 선택
    key[0] = 0;
    parent[0] = -1;

    // MST에 numVertices-1개의 간선을 추가할 때까지 반복
    for (int count = 0; count < numVertices - 1; count++) {
        int u = minKey(key, visited, numVertices);
        if (u == -1) return;  // 더 이상 확장할 정점이 없음
        visited[u] = 1;

        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
}
