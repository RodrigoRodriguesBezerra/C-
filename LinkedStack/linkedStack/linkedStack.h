#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedstack {
    struct no* topo;
    int qtdade;
};

struct linkedstack* inicializar() {
    struct linkedstack* pilha = (struct linkedstack*)malloc(sizeof(struct linkedstack));
    pilha->qtdade = 0;
    pilha->topo = NULL;

    return pilha;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;

    return novoNo;
}

//retornar true se a pilha for nula ou vazia
bool vazia(struct linkedstack* pilha) {
    if (pilha != NULL && pilha->qtdade > 0) {
        return false;
    }
    else {
        return true;
    }
}

//se a pilha estiver nula, instancie a pilha
//por causa da possibilidade de instanciacao usamos struct linkedstack**
void empilhar(struct linkedstack** pilha, int valor) {
    struct no* newNode = alocarNovoNo(valor);
    if ((*pilha) == NULL) {
        (*pilha) = inicializar();
        (*pilha)->topo = newNode;
    }
    else {        
        newNode->prox = (*pilha)->topo;
        (*pilha)->topo = newNode;
    }
    (*pilha)->qtdade++;
}

//decrementar qtdade se a pilha não estiver nula ou vazia
void desempilhar(struct linkedstack* pilha) {
    if (pilha != NULL && pilha->qtdade > 0) {
        struct no* aux = pilha->topo;
        pilha->topo = pilha->topo->prox;
        free(aux);
        pilha->qtdade--;
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int desempilharRetornando(struct linkedstack* pilha) {
    if (pilha != NULL && pilha->qtdade > 0) {
        struct no* aux = pilha->topo;
        pilha->topo = pilha->topo->prox;
        pilha->qtdade--;
        return aux->val;
    }
    else {
        return INT_MIN;
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int topo(struct linkedstack* pilha) {
    if (pilha != NULL && pilha->qtdade > 0) {
        return pilha->topo->val;
    }
    else {
        return INT_MIN;
    }
}

void exibirPilha(struct linkedstack* pilha) {
    //usamos o aux para percorrer a lista
    if (!vazia(pilha)) {
        struct no* aux = pilha->topo;
        //navega partindo do topo até chegar NULL
        printf("_\n");
        do {
            printf("%d\n", aux->val);
            aux = aux->prox;
        } while (aux != NULL);
        printf("_");
    }
    else {
        printf("A pilha está vazia!");
    }
}
