#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct grafo{
    int numNodes;
    //matriz:
    bool **edges;
}Grafo;

Grafo *criar(int numNodes){
    Grafo *g = malloc(sizeof(*g));
    //checar se alocou:
    if(g==NULL){
        return NULL;
    }
    g->numNodes = numNodes;

    //alocar matriz:(tamanho do bool * num nodes)
    g->edges = calloc(sizeof(bool*), g->numNodes);

    //checar se alocou:
    if(g->edges == NULL){
        free(g);
        return NULL;
    }

    for(int i = 0; i < g->numNodes; i++){
        g->edges[i] = calloc(sizeof(bool),g->numNodes);

        //checar se alocou:
        if(g->edges == NULL){
            destruir(g);
            return NULL;
        }
    }

    return g;
}

void destruir(Grafo *g){
    if(g->edges == NULL){
        return;
    }
    for(int i = 0; i < g->numNodes; i++){
        if(g->edges[i] != NULL){
            free(g->edges[i]);
        }
    }
    free(g->edges);
    free(g);
}

bool addEdge(Grafo *g, int i, int j){
    if (hasEdge(g,i,j)){
        return false;
    }

    g->edges[i][j] = true;
    return true;
}

bool removeEdge(Grafo *g, int i, int j){
    if (!hasEdge(g,i,j)){
        return false;
    }

    g->edges[i][j] = false;
    return false;
}

bool hasEdge(Grafo *g, int i, int j){
    return g->edges[i][j];
}

void imprimir(Grafo *g){
    for(int i = 0; i < g->numNodes; i++){
        for(int j = 0; j < g->numNodes; j++){
            if(g->edges[i][j]){
                printf("%d -> %d\n", i, j);
            }
        }
    }
}

int main(){
    Grafo *g1 = criar(5);
    imprimir(g1);
    destruir(g1);
}