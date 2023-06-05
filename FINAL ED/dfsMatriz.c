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

void dfsUtil(Grafo* g, int v, bool* visited);

void dfs(Grafo* g, int start);

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

void dfsUtil(Grafo* g, int v, bool* visited) {
    visited[v] = true;
    printf("%d ", v);

    for (int i = 0; i < g->numNodes; i++) {
        if (g->edges[v][i] && !visited[i]) {
            dfsUtil(g, i, visited);
        }
    }
}

void dfs(Grafo* g, int start) {
    bool* visited = calloc(g->numNodes, sizeof(bool));
    dfsUtil(g, start, visited);
    free(visited);
}

int main() {
    Grafo* g1 = criar(5);
    addEdge(g1, 0, 1);
    addEdge(g1, 0, 2);
    addEdge(g1, 1, 3);
    addEdge(g1, 2, 4);
    addEdge(g1, 2, 3);

    printf("DFS traversal starting from vertex 0: ");
    dfs(g1, 0);
    printf("\n");

    destruir(g1);

    return 0;
}
