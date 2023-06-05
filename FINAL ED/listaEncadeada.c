#include <stdio.h>
#include <stdlib.h>

// Nó:
typedef struct node {
    int val;
    struct node* next;
} Node;

// Lista:
typedef struct lista {
    Node* begin;
    Node* end;
    int size;
} Lista;

// Criar lista
Lista* criarLista() {
    Lista* l = (Lista*)calloc(1, sizeof(Lista));
    l->begin = NULL;
    l->end = NULL;
    l->size = 0;

    return l;
}

// Criar nó
Node* criarNo(int val) {
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->val = val;
    node->next = NULL;

    return node;
}

// Inserir nó no início da lista
void inserirInicio(Lista* l, int val) {
    Node* node = criarNo(val);
    node->next = l->begin;
    l->begin = node;

    if (l->begin == NULL && l->end == NULL) {
        l->end = node;
    }
}

// Inserir nó no final da lista
void inserirFinal(Lista* l, int val) {
    Node* node = criarNo(val);

    if (l->begin == NULL) {
        l->begin = node;
        l->end = node;
    } else {
        l->end->next = node;
        l->end = l->end->next;
    }
}

// Verificar se um elemento pertence à lista
bool pertence(Lista* l, int val) {
    Node* current = l->begin;
    while (current != NULL) {
        if (current->val == val) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Remover um elemento da lista
void remover(Lista* l, int val) {
    if (l->begin != NULL) {
        if (l->begin->val == val) {
            Node* pos = l->begin;

            if (l->end == pos) {
                l->end = NULL;
            }

            l->begin = l->begin->next;
            free(pos);
        } else {
            Node* prev = l->begin;
            Node* pos = l->begin->next;

            while (pos != NULL && pos->val != val) {
                prev = pos;
                pos = pos->next;
            }

            if (pos != NULL) {
                prev->next = pos->next;

                if (pos->next == NULL) {
                    l->end = prev;
                }

                free(pos);
            }
        }
    }
}

// Ordenar a lista em ordem crescente (Bubble Sort)
void ordenarCrescente(Lista* l) {
    if (l->begin == NULL) {
        return;
    }

    int swapped;
    Node* current;
    Node* last = NULL;

    do {
        swapped = 0;
        current = l->begin;

        while (current->next != last) {
            if (current->val > current->next->val) {
                int temp = current->val;
                current->val = current->next->val;
                current->next->val = temp;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

void destroy(Lista** l) {
    Lista* lista = *l;

    Node* n = lista->begin;
    Node* aux = NULL;

    while (n != NULL) {
        aux = n;
        n = n->next;
        free(aux);
    }
    free(lista);
    *l = NULL;
}

// Imprimir lista do início até o final
void imprimir(Lista* l) {
    Node* i = l->begin;

    while (i != NULL) {
        printf("%d ", i->val);
        i = i->next;
    }
    printf("\n");
}

int main() {
    Lista* lista = criarLista();

    int i;
    for (i = 0; i < 5; i++) {
        inserirInicio(lista, i);
    }

    inserirFinal(lista, 6);
    inserirInicio(lista, 7);
    imprimir(lista);

    remover(lista, 3);
    imprimir(lista);

    printf("Pertence a lista? %d\n", pertence(lista, 2));
    printf("Pertence a lista? %d\n", pertence(lista, 8));

    ordenarCrescente(lista);
    imprimir(lista);

    destroy(&lista);

    return 0;
}
