#include <stdio.h>
#include <stdlib.h>

typedef struct no {
   int val;
   struct no *direita;
   struct no *esquerda; 
} No;

typedef struct arvore {
    No *raiz;
    int tam;
} Arvore;

void inserirEsquerda(No **no, int val, Arvore *arv) {
    if (*no == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->val = val;
        novo->direita = NULL;
        novo->esquerda = NULL;
        *no = novo;
        arv->tam = arv->tam + 1;
    } else {
        if (val < (*no)->val) {
            inserirEsquerda(&(*no)->esquerda, val, arv);
        } else if (val > (*no)->val) {
            inserirDireita(&(*no)->esquerda, val, arv);
        }
    }
}

void inserirDireita(No **no, int val, Arvore *arv) {
    if (*no == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->val = val;
        novo->direita = NULL;
        novo->esquerda = NULL;
        *no = novo;
        arv->tam = arv->tam + 1;
    } else {
        if (val > (*no)->val) {
            inserirDireita(&(*no)->direita, val, arv);
        } else if (val < (*no)->val) {
            inserirEsquerda(&(*no)->direita, val, arv);
        }
    }
}

void inserir(Arvore *arv, int val) {
    if (arv->raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->val = val;
        novo->direita = NULL;
        novo->esquerda = NULL;
        arv->raiz = novo;
        arv->tam = arv->tam + 1;
    } else {
        if (val < arv->raiz->val) {
            inserirEsquerda(&arv->raiz, val, arv);
        } else if (val > arv->raiz->val) {
            inserirDireita(&arv->raiz, val, arv);
        }
    }
}

No* inserirNovaVersao(No *raiz, int val) {
    if (raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->val = val;
        novo->direita = NULL;
        novo->esquerda = NULL;
        return novo;
    } else {
        if (val < raiz->val) {
            raiz->esquerda = inserirNovaVersao(raiz->esquerda, val);
        } else if (val > raiz->val) {
            raiz->direita = inserirNovaVersao(raiz->direita, val);
        }
        return raiz;
    }
}

void imprimir(No *raiz) {
    if (raiz != NULL) {
        imprimir(raiz->esquerda);
        printf("%d ", raiz->val);
        imprimir(raiz->direita);
    }

}

int tamanho(No *raiz){
    if(raiz == NULL){
        return 0;
    }
    else{
        return 1 + tamanho(raiz->direita) + tamanho(raiz->esquerda);
    }
}

int buscar(No *raiz, int chave){
    if(raiz == NULL){
        return -1;
    }
    else{
        if(raiz->val == chave){
            return raiz->val;
        }
        else{
            if(chave < raiz->val){
                return buscar(raiz->esquerda, chave);
            }
            else{
                return buscar(raiz->direita, chave);
            }
        }
    }
}
//no folha: sem filhos nem na esquerda nem na direita, retorna NULL
//no só com um filho, precisa salvar esse filho ||  \\\;
//no com dois filhos, precisa salvar ambos os filhos
No* remover(No *raiz, int chave){
    if(raiz == NULL){
        return NULL;
    }
    else{
        if(raiz->val == chave){
            //remove nós folha
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                return NULL;
            }
            else{
                //remove nós que poussuem apenas 1 filho
                if(raiz->esquerda == NULL || raiz->direita == NULL){
                    No *aux;
                    if(raiz->esquerda != NULL){
                        aux = raiz->esquerda;
                    }
                    else{
                        aux = raiz->direita;
                    }
                    free(raiz);
                    return aux;
                }
                //remove nós que possuem 2 filhos
                else{
                    No *aux = raiz->esquerda;
                    while(aux->direita != NULL){
                        aux = aux->direita;
                    }

                    raiz->val = aux->val;
                    aux->val = chave;
                    raiz->esquerda = remover(raiz->esquerda,chave);
                    return raiz;
                }
            }

        }
        else{
            if(chave < raiz->val){
             raiz->esquerda = remover(raiz->esquerda, chave);
            }
            else{
             raiz->direita = remover(raiz->direita,chave);
            }
            return raiz;
        }
    }
}

int main() {
    int op, valor;
    Arvore arv;
    arv.raiz = NULL;
    arv.tam = 0; 
    do {
        printf("0 - Sair, 1 - Inserir, 2 - Imprimir, 3 - buscar, 4-remover: ");
        scanf("%d", &op);

        switch (op) {
            case 0:
                printf("Sair\n");
                break;
            case 1:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                //inserir(&arv, valor);
                arv.raiz = inserirNovaVersao(arv.raiz, valor);
                break;
            case 2:
                imprimir(arv.raiz);
                printf("\n");
                break;
            case 3:
                printf("Qual valor buscar?");
                scanf("%d", &valor);
                printf("Resultado: %d", buscar(arv.raiz,valor));
                break;
            case 4:
                printf("Digite o valor para remover: ");
                scanf("%d", &valor);
                arv.raiz = remover(arv.raiz, valor);
                break;                
            default:
                printf("Opção inválida\n");
                break;
        }
    } while (op != 0);

    //printf("  %d", arv.tam);
    printf("  %d", tamanho(arv.raiz));

    return 0;
}
