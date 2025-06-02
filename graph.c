#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/*
 generateGraph:
 대각선(graph[i][i])은 0으로 초기화한 뒤, 
 i < j 구간에서 랜덤 가중치(1~100)를 붙이고 대칭으로 저장한다.
 */
void generateGraph(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int i, j;
    int maxWeight = 100;

    // 초기화
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            graph[i][j] = 0;
        }
    }

    // 완전 그래프로 생성: i<j 구간에만 랜덤 가중치 부여 후 대칭 저장
    for (i = 0; i < numVertices; i++) {
        for (j = i + 1; j < numVertices; j++) {
            int weight = (rand() % maxWeight) + 1; 
            graph[i][j] = weight;
            graph[j][i] = weight;
        }
    }
}

/*
 findSet & unionSet: Disjoint‐Set (유니온 파인드) 내부 함수
 */
static int findSet(int parent[], int i) {
    if (parent[i] != i) {
        parent[i] = findSet(parent, parent[i]);
    }
    return parent[i];
}

static void unionSet(int parent[], int rank[], int x, int y) {
    int xroot = findSet(parent, x);
    int yroot = findSet(parent, y);
    if (xroot == yroot) return;

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

/*
 isSpanningTree:
 - edges[] 배열(edgeCount개)이 numVertices개의 정점으로 이루어진 스패닝 트리인지 검사
 */
int isSpanningTree(Edge edges[], int edgeCount, int numVertices) {
    int i;
    if (edgeCount != numVertices - 1) {
        return 0;  // 간선 수가 V-1이 아니면 스패닝 트리 아님
    }

    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES];
    for (i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // 각 간선을 Union-Find에 넣으면서 사이클이 있는지 검사
    for (i = 0; i < edgeCount; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int setU = findSet(parent, u);
        int setV = findSet(parent, v);
        if (setU == setV) {
            // 사이클 발견 → 스패닝 트리 아님
            return 0;
        }
        unionSet(parent, rank, setU, setV);
    }

    // 모든 정점이 하나의 루트(루트가 같은지)인지 확인
    int root0 = findSet(parent, 0);
    for (i = 1; i < numVertices; i++) {
        if (findSet(parent, i) != root0) {
            return 0;  // 연결이 완전하지 않음
        }
    }

    return 1;  // V-1 간선, 사이클 없음, 완전 연결
}

/*
 * printGraph:
 *   그래프를 인접 행렬 형태로 출력 (디버깅용)
 */
void printGraph(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int i, j;
    printf("Adjacency Matrix:\n");
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            printf("%3d ", graph[i][j]);
        }
        printf("\n");
    }
}
