#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"

/*
 * kruskalMST
 */
void kruskalMST(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices, Edge result[], int *edgeCount);

#endif // KRUSKAL_H
