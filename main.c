#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph.h"
#include "prim.h"
#include "kruskal.h"

#define NUM_VERTICES 50

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int parent[MAX_VERTICES];
    Edge mstEdges[MAX_VERTICES];
    int edgeCount, i;

    // 랜덤 시드를 초기화하면 실행마다 다른 그래프 생성
    srand((unsigned)time(NULL));

    // NUM_VERTICES 크기의 임의 완전 그래프 생성
    generateGraph(graph, NUM_VERTICES);

    // (디버깅용) 그래프 인접 행렬 출력
    // printGraph(graph, NUM_VERTICES);

    // Prim 알고리즘으로 MST 구하기
    primMST(graph, NUM_VERTICES, parent);

    printf("=== Prim's MST ===\n");
    int totalWeightPrim = 0;
    // parent[0] = -1 이므로 1부터 NUM_VERTICES-1까지 반복
    Edge primEdges[NUM_VERTICES - 1];
    for (i = 1; i < NUM_VERTICES; i++) {
        primEdges[i - 1].src = parent[i];
        primEdges[i - 1].dest = i;
        primEdges[i - 1].weight = graph[i][parent[i]];
        printf("  %2d - %2d  | weight = %3d\n",
               primEdges[i - 1].src,
               primEdges[i - 1].dest,
               primEdges[i - 1].weight);
        totalWeightPrim += primEdges[i - 1].weight;
    }
    printf("Total Weight (Prim): %d\n", totalWeightPrim);
    printf("Number of Nodes: %d, Number of Edges: %d\n",
           NUM_VERTICES, NUM_VERTICES - 1);
    // 스패닝 트리 검증
    if (isSpanningTree(primEdges, NUM_VERTICES - 1, NUM_VERTICES)) {
        printf("Prim's result is a valid spanning tree.\n\n");
    } else {
        printf("Prim's result is NOT a valid spanning tree.\n\n");
    }

    // Kruskal 알고리즘으로 MST 구하기
    kruskalMST(graph, NUM_VERTICES, mstEdges, &edgeCount);

    printf("=== Kruskal's MST ===\n");
    int totalWeightKruskal = 0;
    for (i = 0; i < edgeCount; i++) {
        printf("  %2d - %2d  | weight = %3d\n",
               mstEdges[i].src,
               mstEdges[i].dest,
               mstEdges[i].weight);
        totalWeightKruskal += mstEdges[i].weight;
    }
    printf("Total Weight (Kruskal): %d\n", totalWeightKruskal);
    printf("Number of Nodes: %d, Number of Edges: %d\n",
           NUM_VERTICES, edgeCount);
    // 스패닝 트리 검증
    if (isSpanningTree(mstEdges, edgeCount, NUM_VERTICES)) {
        printf("Kruskal's result is a valid spanning tree.\n");
    } else {
        printf("Kruskal's result is NOT a valid spanning tree.\n");
    }

    return 0;
}
