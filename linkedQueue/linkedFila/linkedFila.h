#pragma once

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedqueue {
    struct no* frente;
    struct no* tras;
    int qtdade;
};

struct linkedqueue* inicializar() {
    struct linkedqueue* fila = (struct linkedqueue*)malloc(sizeof(struct linkedqueue));
    fila->qtdade = 0;
    fila->frente = NULL;
    fila->tras = NULL;

    return fila;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;

    return novoNo;
}

bool vazia(struct linkedqueue* fila) {
    if (fila == NULL) {
        return true;
    }
    else if (fila->frente == NULL && fila->tras == NULL && fila->qtdade == 0) {
        return true;
    }
    else return false;
}

//se a fila estiver nula, instancie a fila
//por causa da possibilidade de instanciacao usamos struct linkedqueue**
void enfileirar(struct linkedqueue** fila, int val) {
    if ((*fila) == NULL) {
        (*fila) = inicializar();
    }
    struct no* newNode = alocarNovoNo(val);
    if (vazia((*fila))) {
        (*fila)->frente = newNode;
        (*fila)->tras = newNode;
    }
    else {
        (*fila)->tras->prox = newNode;
        (*fila)->tras = newNode;
    }
    (*fila)->qtdade++;

}

//retorne a constante INT_MIN se a fila for nula ou vazia
//lembrem de desalocar o nó removido (free)
int desenfileirar(struct linkedqueue* fila) {
    if (vazia(fila)) {
        return INT_MIN;
    }
    int valor = fila->frente->val;
    if (fila->frente == fila->tras && fila->frente != NULL && fila->qtdade == 1) {
        free(fila->frente);
        fila->frente = NULL;
        fila->tras = NULL;
    }
    else {
        struct no* novoFrente = fila->frente->prox;
        free(fila->frente);
        fila->frente = novoFrente;
    }
    fila->qtdade--;
    return valor;
}

//retorne a constante INT_MIN se a fila for nula ou vazia


int frente(struct linkedqueue* fila) {
    if (vazia(fila)) {
        return INT_MIN;
    }
    return fila->frente->val;
}
