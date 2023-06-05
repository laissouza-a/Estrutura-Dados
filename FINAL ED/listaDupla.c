#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int val;
    struct node *prev;
    struct node *next;
}Node;

typedef struct lista{
    Node *begin;
    Node *end;
    int size;
}Lista;

Lista *criarLista(){
    Lista *l = (Lista*)calloc(1, sizeof(Lista));
    l->begin = NULL;
    l->end = NULL;
    l->size = 0;

    return l;
}

Node *criarNo(int val){
    Node *node = (Node*)calloc(1,sizeof(Node));
    node->val = val;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

bool empty(Lista *l){
    return l->size == 0 && l->begin == NULL;
}

void inserirInicio(Lista *l, int val){
        Node *p = criarNo(val);
        p->next = l->begin;

        if(empty(l)){
            l->end = p;
        }
        else{
         l->begin->prev = p;
        }

        l->begin = p;
        l->size++;   
}

void inserirFinal(Lista *l, int val){
    Node *node = criarNo(val);

    if(l->begin == NULL){
        l->begin = node;
    }
    else{
        node->prev = l->end;
        l->end->next = node;
    }
    l->end = node;
    l->size++;
}

void remover(Lista *l, int val){
    if(l->begin!=NULL){
        //elemento no inicio
        if(l->begin->val == val){
            Node *p = l->begin;
            l->begin = p->next;
            //lista só tem um elemento
            if(l->end == p){
                l->end = NULL;
            }
            //mais de um elemento
            else{
                l->begin->prev = NULL;
            }
            free(p);
            l->size--;
        }
        //elemento no meio ou final
        else{
            Node *p = l->begin->next;
            while(p!= NULL){
                if(p->val == val){
                    //final:
                    if(l->end == p){
                        l->end = p->prev;
                        l->end->next = NULL;
                    }
                    //meio:
                    else{
                    p->prev->next = p->next;
                    p->next->prev = p->prev;
                    }
                    free(p);
                    p = NULL;
                    l->size--;
                }
                else{
                    p = p->next;
                }
            }
        }

        
        }
    }

void destroy(Lista **l){
    Lista *lista = *l;

    Node *n = lista->begin;
    Node *aux = NULL;

    while (n != NULL)
    {
        aux = n;
        n = n->next;
        free(aux);
    }
    free(lista);
    l = NULL;
}

void imprimir(Lista *l){
    Node *i = l->begin;

    while(i!=NULL){
        printf("%d", i->val);
        i = i->next;
    }
}

int main(){

    Lista *lista = criarLista();
    
    int i;
    for(i=0;i<5;i++){
        inserirInicio(lista,i);
    }

    remover(lista, 0);
    imprimir(lista);
    destroy(&lista);

    return 0;
}