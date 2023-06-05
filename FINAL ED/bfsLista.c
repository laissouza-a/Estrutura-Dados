#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int val;
    struct node* next;
} Node;

typedef struct grafo {
    int numNodes;
    Node** adjList;
} Grafo;

Grafo* criar(int numNodes) {
    Grafo* g = malloc(sizeof(*g));
    if (g == NULL) {
        return NULL;
    }
    g->numNodes = numNodes;
    g->adjList = malloc(numNodes * sizeof(Node*));
    if (g->adjList == NULL) {
        free(g);
        return NULL;
    }
    for (int i = 0; i < numNodes; i++) {
        g->adjList[i] = NULL;
    }
    return g;
}

void destruir(Grafo* g) {
    if (g->adjList == NULL) {
        return;
    }
    for (int i = 0; i < g->numNodes; i++) {
        Node* current = g->adjList[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(g->adjList);
    free(g);
}

Node* criarNode(int val) {
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Grafo* g, int i, int j) {
    Node* newNode = criarNode(j);
    newNode->next = g->adjList[i];
    g->adjList[i] = newNode;
}

void removeEdge(Grafo* g, int i, int j) {
    Node* current = g->adjList[i];
    Node* prev = NULL;

    while (current != NULL) {
        if (current->val == j) {
            if (prev == NULL) {
                g->adjList[i] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

bool hasEdge(Grafo* g, int i, int j) {
    Node* current = g->adjList[i];
    while (current != NULL) {
        if (current->val == j) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void imprimir(Grafo* g) {
    for (int i = 0; i < g->numNodes; i++) {
        Node* current = g->adjList[i];
        while (current != NULL) {
            printf("%d -> %d\n", i, current->val);
            current = current->next;
        }
    }
}

void bfs(Grafo* g, int start) {
    bool* visited = calloc(g->numNodes, sizeof(bool));
    int* queue = malloc(g->numNodes * sizeof(int));
    int front = 0;
    int rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        Node* node = g->adjList[current];
        while (node != NULL) {
            int adjacent = node->val;
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                queue[rear++] = adjacent;
            }
            node = node->next;
        }
    }

    free(visited);
    free(queue);
}

int main() {
    Grafo* g1 = criar(5);
    addEdge(g1, 0, 1);
    addEdge(g1, 0, 3);
    addEdge(g1, 1, 2);
    addEdge(g1, 2, 4);
    addEdge(g1, 3, 4);
    imprimir(g1);

    printf("BFS traversal starting from vertex 0: ");
    bfs(g1, 0);
    printf("\n");

    destruir(g1);
    return 0;
}
