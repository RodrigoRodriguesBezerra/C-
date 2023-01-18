#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stack>
using namespace std;

/* Q1: Inverta uma lista duplamente ligada
 * com um algoritmo in-place (ou seja, sem
 * criar uma nova lista duplamente ligada)
 */

struct noDuplo {
    struct noDuplo* ant;
    int val;
    struct noDuplo* prox;
};

struct doublylinkedlist {
    struct noDuplo* cabeca;
    struct noDuplo* cauda;
    int qtdade;
};

struct doublylinkedlist* inicializarDLL() {
    struct doublylinkedlist* lista = (struct doublylinkedlist*)malloc(sizeof(struct doublylinkedlist));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->qtdade = 0;
    return lista;
}

struct noDuplo* alocarNovoNoDuplo(int valor) {
    struct noDuplo* novoNo = (struct noDuplo*)malloc(sizeof(struct noDuplo));
    novoNo->val = valor;
    novoNo->ant = NULL;
    novoNo->prox = NULL;
    return novoNo;
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor) {
    //aloca espaço na memória e popula novoNo
    struct noDuplo* novoNo = alocarNovoNoDuplo(valor);

    if (lista->cabeca == NULL) {
        //quando a lista é vazia, basta apontar o cabeca e cauda para o novoNo
        lista->cabeca = novoNo;
    }
    else {
        //atualizamos o ponteiro novoNo->ant para o antigo último nó
        novoNo->ant = lista->cauda;
        //ponteiro prox do antigo último nó para o novoNo
        lista->cauda->prox = novoNo;
    }
    //uma certeza: inserindo no fim, a cauda apontará para o novoNo
    lista->cauda = novoNo;
    lista->qtdade++;
}

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    struct noDuplo* aux = lista->cabeca;
    for (int i = 0; i < posicao && aux->prox != NULL; i++) {
        aux = aux->prox;
    }
    return aux->val;
}

void inverterDoublyLinkedList(struct doublylinkedlist* lista) {
    struct noDuplo* noAnterior = lista->cabeca;
    struct noDuplo* proximoNo = noAnterior->prox;

    noAnterior->prox = NULL;
    noAnterior->ant = proximoNo;

    while (proximoNo != NULL) {
        proximoNo->ant = proximoNo->prox;
        proximoNo->prox = noAnterior;
        noAnterior = proximoNo;
        proximoNo = proximoNo->ant;
    }
    lista->cabeca = noAnterior;
}

/******************************************/

/* Q2: escreva um algoritmo que detecte se uma
 * certa combinacao de parenteses estah balanceada.
 * Dica: usar pilha, pode ser a impl "stack" CPP STL.
 * Olhe os casos de teste para entender o que eh uma
 * combinacao balanceada.
 */

bool balanceamentoParenteses(const char* parenteses, int tam) {
    int tamanhoChar = strlen(parenteses);
    int cont1 = 0;
    int cont2 = 0;
    stack<char> pilha;
    if (tamanhoChar == tam) {
        for (int i = 0; i < tam; i++) {
            pilha.push(parenteses[i]);
            if (pilha.top() == ')' && i == 0) {
                return false;
            }
            if (pilha.top() == '(' && i == tam - 1) {
                return false;
            }
            if (pilha.top() == '(') {
                cont1++;
            }
            else if (pilha.top() == ')') {
                cont2++;
            }
            
        }
        if (cont1 == cont2) {
            return true;
        }
        else{
            return false;
        }
    }
}

/******************************************/

/* Q3: Inverta uma lista ligada (LinkedList)
 * com um algoritmo in-place (ou seja, sem
 * criar uma nova LinkedList)
 */

struct no {
    int val;
    struct no* prox;
};

struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializarLL() {
    struct linkedlist* lista = (struct linkedlist*)malloc(sizeof(struct linkedlist));
    lista->cabeca = NULL;
    lista->qtdade = 0;
    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;
    return novoNo;
}

void inserirElementoNoFim(struct linkedlist* lista, int valor) {
    struct no* novoNo = alocarNovoNo(valor);
    if (lista->cabeca == NULL) {
        lista->cabeca = novoNo;
    }
    else {
        struct no* aux = lista->cabeca;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novoNo;
    }
    lista->qtdade++;
}

void inverterLinkedListInPlace(struct linkedlist* lista) {
    struct no* aux1 = lista->cabeca;
    struct no* proximoNo;
    struct no* noAnterior = NULL;
    while(aux1 != NULL) {
        proximoNo = aux1->prox;
        aux1->prox = noAnterior;
        noAnterior = aux1;
        aux1 = proximoNo;
    }
    lista->cabeca = noAnterior;
}

int obterElementoEmPosicao(struct linkedlist* lista, int posicao) {
    struct no* aux = lista->cabeca;
    for (int i = 0; i < posicao && aux->prox != NULL; i++) {
        aux = aux->prox;
    }
    return aux->val;
}