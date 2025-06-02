#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

/*
 * compareEdges: qsort에서 사용할 Edge 가중치 비교 함수 (오름차순)
 */
static int compareEdges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->weight - e2->weight;
}

/*
 * findSet & unionSet: Disjoint‐Set (유니온 파인드) 내부 함수
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
 * kruskalMST
 */
void kruskalMST(int graph[MAX_VERTICES][MAX_VERTICES],
                int numVertices,
                Edge result[],
                int *edgeCount) {
    int i, j;
    int maxEdges = numVertices * (numVertices - 1) / 2;
    Edge *edges = (Edge *)malloc(maxEdges * sizeof(Edge));
    int idx = 0;

    // 인접 행렬로부터 i<j 간선만 모두 추출
    for (i = 0; i < numVertices; i++) {
        for (j = i + 1; j < numVertices; j++) {
            if (graph[i][j] != 0) {
                edges[idx].src = i;
                edges[idx].dest = j;
                edges[idx].weight = graph[i][j];
                idx++;
            }
        }
    }
    int totalEdges = idx;

    // 가중치 오름차순 정렬
    qsort(edges, totalEdges, sizeof(Edge), compareEdges);

    // Union-Find 초기화
    int *parent = (int *)malloc(numVertices * sizeof(int));
    int *rank = (int *)malloc(numVertices * sizeof(int));
    for (i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // 사이클이 되지 않으면 MST 선택
    int e = 0;       // MST에 추가된 간선 개수
    int k = 0;       // 정렬된 간선 배열 인덱스
    while (e < numVertices - 1 && k < totalEdges) {
        Edge nextEdge = edges[k++];
        int setU = findSet(parent, nextEdge.src);
        int setV = findSet(parent, nextEdge.dest);

        if (setU != setV) {
            result[e++] = nextEdge;
            unionSet(parent, rank, setU, setV);
        }
    }

    *edgeCount = e;  // 실제로 선택된 간선 개수 (정상적이면 numVertices-1)
    free(edges);
    free(parent);
    free(rank);
}
