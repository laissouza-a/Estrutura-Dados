#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct grafo {
    int numNodes;
    bool** edges;
} Grafo;

Grafo* criar(int numNodes);

void destruir(Grafo* g);

bool addEdge(Grafo* g, int i, int j);

bool removeEdge(Grafo* g, int i, int j);

bool hasEdge(Grafo* g, int i, int j);

void bfs(Grafo* g, int start);

bool hasEdge(Grafo* g, int i, int j) {
    return g->edges[i][j];
}

Grafo* criar(int numNodes) {
    Grafo* g = malloc(sizeof(*g));
    if (g == NULL) {
        return NULL;
    }
    g->numNodes = numNodes;

    g->edges = calloc(sizeof(bool*), g->numNodes);
    if (g->edges == NULL) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < g->numNodes; i++) {
        g->edges[i] = calloc(sizeof(bool), g->numNodes);
        if (g->edges[i] == NULL) {
            destruir(g);
            return NULL;
        }
    }

    return g;
}

void destruir(Grafo* g) {
    if (g->edges == NULL) {
        return;
    }
    for (int i = 0; i < g->numNodes; i++) {
        if (g->edges[i] != NULL) {
            free(g->edges[i]);
        }
    }
    free(g->edges);
    free(g);
}

bool addEdge(Grafo* g, int i, int j) {
    if (hasEdge(g, i, j)) {
        return false;
    }

    g->edges[i][j] = true;
    return true;
}

bool removeEdge(Grafo* g, int i, int j) {
    if (!hasEdge(g, i, j)) {
        return false;
    }

    g->edges[i][j] = false;
    return true;
}
//recebe o grafo e o vertice inicial
void bfs(Grafo* g, int start) {
    //aloca espaço para bool de visitados(numNodes*tamanhoBool)
    bool* visited = calloc(g->numNodes, sizeof(bool));
    //aloca espaço para uma fila (numNodes*tamInt)
    int* queue = malloc(g->numNodes * sizeof(int));
    //frente e tras = 0;
    int front = 0;
    int rear = 0;
    //O vertice que iniciamos já é marcado como visitado
    visited[start] = true;
    //incrementa a fila e coloca o visitado 
    queue[rear++] = start;

    //enquanto tiver fila
    while (front < rear) {
        //current vai ser igual ao proximo da fila
        int current = queue[front++];
        //imprime esse valor
        printf("%d ", current);
        //iterar numNodes vezes
        for (int i = 0; i < g->numNodes; i++) {
            //se e o current tiver relacao com um i e ele não tiver 
            //visitado, então é marcado como visitado e a fila é
            //ampliada e coloca o i na fila;
            if (g->edges[current][i] && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
    //libera os visitados e a fila
    free(visited);
    free(queue);
}

int main() {
    Grafo* g1 = criar(5);
    addEdge(g1, 0, 1);
    addEdge(g1, 0, 2);
    addEdge(g1, 1, 3);
    addEdge(g1, 2, 4);
    addEdge(g1, 2, 3);

    printf("BFS traversal starting from vertex 0: ");
    //manda o grafo e vertice pelo qual vamos iniciar
    bfs(g1, 0);
    printf("\n");

    destruir(g1);

    return 0;
}
