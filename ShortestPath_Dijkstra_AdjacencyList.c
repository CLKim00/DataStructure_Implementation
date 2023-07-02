#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// 노드를 표현하는 구조체 정의
struct Node
{
    int vertex, weight;
    struct Node* next;
};

// 그래프를 표현하는 구조체 정의
struct Graph
{
    int numVertices;
    struct Node** adjLists;
    int* distance; // 시작 정점으로부터의 최단 거리를 저장할 배열
};

struct Node* createNode(int v, int w)
{
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct Node*));
    graph->distance = malloc(vertices * sizeof(int));
    for(int i=0; i<vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->distance[i] = INT_MAX; // 모든 정점의 최단 거리를 무한대로 초기화
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    // 간선과 가중치를 추가하는 함수
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

int findMinVertex(struct Graph* graph, int* visited)
{
    // 방문하지 않은 정점 중에서 최단 거리가 가장 작은 정점을 찾는 함수
    int minVertex = -1;
    for(int i=0; i<graph->numVertices; i++)
    {
        if(!visited[i] && (minVertex == -1 || graph->distance[i] < graph->distance[minVertex]))
            minVertex = i;
    }
    return minVertex;
}

void dijkstra(struct Graph* graph, int src)
{
    // Dijkstra 알고리즘을 구현하는 함수
    int* visited = malloc(graph->numVertices * sizeof(int));
    for(int i=0; i<graph->numVertices; i++)
        visited[i] = 0; // 모든 정점을 방문하지 않음으로 초기화

    graph->distance[src] = 0; // 시작 정점의 최단 거리를 0으로 설정

    for(int i=0; i<graph->numVertices-1; i++)
    {
        // 방문하지 않은 정점 중에서 최단 거리가 가장 작은 정점을 찾는다.
        int minVertex = findMinVertex(graph, visited);
        struct Node* temp = graph->adjLists[minVertex];
        visited[minVertex] = 1; // 찾은 정점을 방문했음으로 표시한다.

        // 찾은 정점과 인접한 모든 정점에 대해 거리를 업데이트한다.
        while(temp)
        {
            if(!visited[temp->vertex] && graph->distance[minVertex] + temp->weight < graph->distance[temp->vertex])
            {
                graph->distance[temp->vertex] = graph->distance[minVertex] + temp->weight;
            }
            temp = temp->next;
        }
    }

    // 결과 출력
    for(int i=0; i<graph->numVertices; i++)
    {
        if(i != src)
            printf("정점 1부터 정점 %d까지의 최단경로 : %d\n", i+1, graph->distance[i]);
    }
}

int main()
{
    struct Graph* graph = createGraph(16); // 16개의 정점을 가진 그래프 생성
    addEdge(graph, 0, 1, 3); // 간선과 가중치 추가
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 0, 4, 2); // 간선과 가중치 추가
    addEdge(graph, 1, 5, 5);
    addEdge(graph, 2, 6, 1);
    addEdge(graph, 3, 7, 6); // 간선과 가중치 추가
    addEdge(graph, 4, 5, 1);
    addEdge(graph, 5, 6, 5);
    addEdge(graph, 6, 7, 8); // 간선과 가중치 추가
    addEdge(graph, 4, 8, 3);
    addEdge(graph, 5, 9, 4);
    addEdge(graph, 6, 10, 2); // 간선과 가중치 추가
    addEdge(graph, 7, 11, 6);
    addEdge(graph, 8, 9, 2);
    addEdge(graph, 9, 10, 4); // 간선과 가중치 추가
    addEdge(graph, 10, 11, 6);
    addEdge(graph, 8, 12, 2);
    addEdge(graph, 9, 13, 6); // 간선과 가중치 추가
    addEdge(graph, 10, 14, 4);
    addEdge(graph, 11, 15, 4);
    addEdge(graph, 12, 13, 3); // 간선과 가중치 추가
    addEdge(graph, 13, 14, 5);
    addEdge(graph, 14, 15, 7);

    // 여기에 다른 간선과 가중치를 추가한다.

    dijkstra(graph, 0); // 0번 정점에서 시작하는 Dijkstra 알고리즘 실행

    return 0;
}
