#include <stdio.h>
#include <stdlib.h>

#define EDGE_COUNT 24
#define VERTEX_COUNT 16

// Union-Find 구조체
// 부분잡합 트리 정보를 담는 subset 구조체
typedef struct subset {
    int parent;     // 이 subset의 대표 vertex
    int rank;       // 각 subset의 깊이
} subset;

// Edge 구조체
typedef struct Edge {
    int start;      // 시작 정점
    int end;        // 도착 정점
    int weight;     // 가중치
} Edge;

// 그래프 구조체
typedef struct Graph {
    int V, E;       // V = vertex의 수, E = edge의 수
    Edge* edge;     // edge에 대한 배열
} Graph;

Graph* createGraph(int V, int E);
int find(subset subsets[], int i);
void Union(subset subsets[], int x, int y);
int compareEdges(const void* a, const void* b);
void KruskalMST(Graph* graph);
void addEdge(Graph* graph, int index, int start, int end, int weight);

int main() {
    int V = 16, E = 24;
    Graph* graph = createGraph(V, E);

    // 함수를 사용하여 각 edge를 추가해 나갑니다
    addEdge(graph, 0, 1, 2, 3);
    addEdge(graph, 1, 2, 3, 1);
    addEdge(graph, 2, 3, 4, 4);
    addEdge(graph, 3, 1, 5, 2);
    addEdge(graph, 4, 2, 6, 5);
    addEdge(graph, 5, 3, 7, 1);
    addEdge(graph, 6, 4, 8, 6);
    addEdge(graph, 7, 5, 6, 1);
    addEdge(graph, 8, 6, 7, 5);
    addEdge(graph, 9, 7, 8, 8);
    addEdge(graph, 10, 5, 9, 3);
    addEdge(graph, 11, 6, 10, 4);
    addEdge(graph, 12, 7, 11, 2);
    addEdge(graph, 13, 8, 12, 6);
    addEdge(graph, 14, 9, 10, 2);
    addEdge(graph, 15, 10, 11, 4);
    addEdge(graph, 16, 11, 12, 6);
    addEdge(graph, 17, 9, 13, 2);
    addEdge(graph, 18, 10, 14, 6);
    addEdge(graph, 19, 11, 15, 4);
    addEdge(graph, 20, 12, 16, 4);
    addEdge(graph, 21, 13, 14, 3);
    addEdge(graph, 22, 14, 15, 5);
    addEdge(graph, 23, 15, 16, 7);
    
    KruskalMST(graph);
    return 0;
}

// 그래프 생성 함수
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge*) malloc(graph->E * sizeof(Edge));    // edge 수만큼 메모리 할당
    return graph;
}

// subset에서 vertex의 root를 찾는 함수
int find(subset subsets[], int i) {
    if (subsets[i].parent != i)     // i가 root가 아니라면 root를 찾아서 재귀
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;   // root 반환
}

// 두 subset을 합치는 함수 (Union 연산)
void Union(subset subsets[], int x, int y) {
    int xroot = find(subsets, x);   // x의 root 찾기
    int yroot = find(subsets, y);   // y의 root 찾기

    if (subsets[xroot].rank < subsets[yroot].rank)      // rank가 작은 트리를 큰 트리에 붙임
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {      // 두 트리의 rank가 같으면 하나를 root로 하고 rank를 하나 늘림
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// qsort()에 사용될 edge 비교 함수
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;     // 가중치에 따라 오름차순 정렬
}

// Kruskal 알고리즘으로 MST를 구하는 함수
void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V];     // MST에 포함되는 edge를 저장할 배열
    int e = 0, i = 0;

    // 모든 edge를 가중치 순으로 정렬
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    // 각 vertex를 위한 subset 배열
    subset *subsets = (subset*) malloc(V * sizeof(subset));

    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;  // 각 subset의 parent를 자기 자신으로 초기화
        subsets[v].rank = 0;    // rank를 0으로 초기화
    }

    // 정렬된 edge들을 순회하며 MST를 구성한다
    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edge[i++];
        int x = find(subsets, next_edge.start);
        int y = find(subsets, next_edge.end);

        // 이 edge가 cycle을 형성하는지 확인한다
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // cycle을 형성한다면 이 edge를 무시
    }

    // MST 출력
    printf("다음은 Kruskal Algorithm을 사용하며 만든 MST입니다.\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].start, result[i].end, result[i].weight);
}

void addEdge(Graph* graph, int index, int start, int end, int weight){
    graph->edge[index].start = start;
    graph->edge[index].end = end;
    graph->edge[index].weight = weight;
}