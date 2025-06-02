#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 100

/*
 * Edge 구조체: 두 정점(src, dest) 사이의 가중치(weight)를 저장
 */
typedef struct {
    int src, dest, weight;
} Edge;

/*
 * generateGraph
 numVertices 크기의 임의 가중치 완전 그래프를 생성하여
 graph[][] 배열에 저장한다.
 weights은 1 ~ 100 사이로 랜덤 지정.
 */
void generateGraph(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices);

/*
 * isSpanningTree
 */
int isSpanningTree(Edge edges[], int edgeCount, int numVertices);

/*
 * printGraph
 graph[][]의 인접 행렬을 콘솔에 출력한다.
 */
void printGraph(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices);

#endif // GRAPH_H
