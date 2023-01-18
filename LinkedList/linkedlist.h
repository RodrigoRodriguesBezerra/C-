#pragma once
#include <stdlib.h>
#include <stdio.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializar() {
    struct linkedlist* lista = (struct linkedlist*)malloc(sizeof(struct linkedlist));
    lista->qtdade = 0;
    lista->cabeca = NULL;

    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;

    return novoNo;
}

void inserirElementoNoFim(struct linkedlist* lista, int valor) {
    struct no* newNode = alocarNovoNo(valor);

    if ((lista->cabeca) != NULL) {
        struct no* aux = lista->cabeca;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }

        aux->prox = newNode;
    }
    else {
        lista->cabeca = newNode;
    }

    lista->qtdade++;
}

void inserirElementoNoInicio(struct linkedlist* lista, int valor) {
    struct no* newNode = alocarNovoNo(valor);
    if (lista->cabeca != NULL) {
        newNode->prox = lista->cabeca;
        lista->cabeca = newNode;
    }
    else {
        lista->cabeca = newNode;
    }
    lista->qtdade++;
}

void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao) {
    struct no* newNode = alocarNovoNo(valor);
    struct no* aux = lista->cabeca;
    //if (posicao >= 0 && posicao < lista->qtdade) {
        if (posicao == 0) {
            inserirElementoNoInicio(lista, valor);
        }
        else if (posicao == lista->qtdade - 1) {
            inserirElementoNoFim(lista, valor);
        }
        else if (posicao == 1) {
            newNode->prox = aux->prox;
            aux->prox = newNode;
            lista->qtdade++;
        }
        else {
            for (int i = 0; i < posicao-1; i++) {
                aux = aux->prox;
            }

            newNode->prox = aux->prox;
            aux->prox = newNode;
            lista->qtdade++;
        }
    //}
 }

int obterElementoEmPosicao(struct linkedlist* lista, int posicao) {
    struct no* aux = lista->cabeca;
    if (posicao > 1 && posicao < lista->qtdade) {
        if (lista->cabeca != NULL) {
            for (int i = 0; i < posicao; i++) {
                aux = aux->prox;
            }
            return aux->val;
        }
    }
    else if (posicao == 0) {
        return lista->cabeca->val;
    }
    else if (posicao == 1) {
        return aux->prox->val;
    }

}

void removerElementoEmPosicao(struct linkedlist* lista, int posicao) {
    struct no* aux = lista->cabeca;
    struct no* aux2;
    if (posicao > 0 && posicao < lista->qtdade) {
        for (int i = 0; i < posicao - 1; i++) {
            aux = aux->prox;
        }
        aux2 = aux->prox;
        aux = aux2->prox;
    }
    else if(posicao == 0) {
        lista->cabeca = aux->prox;
        free(aux);
    }
    lista->qtdade--;
}

void imprimirLista(struct linkedlist* lista) {
    //usamos o aux para percorrer a lista
    if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL) {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else {
        printf("A lista está vazia!");
    }
}