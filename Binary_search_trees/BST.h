#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <algorithm>

struct noBst {
    int val;
    struct noBst* esq;
    struct noBst* dir;
};

/**
 * Funcao que aloca um novo noBst, e
 * ajusta os ponteiros esq e dir para NULL.
 **/
struct noBst* alocarNovoNo(int val) {
    struct noBst* novoNo = (struct noBst*)malloc(sizeof(struct noBst));
    novoNo->val = val;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    return novoNo;
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * insere um novo valor na BST. Tamanho deve
 * ser incrementado.
 * Ambos tamanho e raiz são passados por referência.
 **/
void inserir(struct noBst** raiz, int val, int* tamanho) {
    if ( (*raiz) == NULL) {
        (*raiz) = alocarNovoNo(val);
        (*tamanho)++;
    }
    else if ( val <= ( * raiz)->val ) {
        inserir(&((*raiz)->esq), val, tamanho);
    }
    else {
        inserir(&((*raiz)->dir), val, tamanho);
    }
}


/**
 * Funcao que retorna o maior valor de uma BST.
 **/
int max(struct noBst* raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    while (raiz->dir != NULL) {
        raiz = raiz->dir;
    }
    return raiz->val;
}

///**
// * Funcao que retorna o menor valor de uma BST.
// **/
int min(struct noBst* raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    while (raiz->esq != NULL) {
        raiz = raiz->esq;
    }
    return raiz->val;
}

/**
 * Funcao que retorna a altura de uma BST.
 * A altura de uma BST é dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 **/
int altura(struct noBst* raiz) {
    int alturaEsq = 0;
    int alturaDir = 0;
    if (raiz == NULL) {
        return 0;
    }
    else {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            return 0;
        }
        else if (raiz->esq == NULL) {
            return alturaDir = 1 + altura(raiz->dir);
        }
        else if (raiz->dir == NULL) {
            return alturaEsq = 1 + altura(raiz->esq);
        }
        else {
            if (alturaEsq > alturaDir) {
                return 1 + altura(raiz->esq);
            }
            else {
                return 1 + altura(raiz->dir);
            }
        }
    }
}

/**
 * Funcao que navega em-ordem na BST e
 * imprime seus elementos.
 **/
void emOrdem(struct noBst* raiz) {
    if (raiz == NULL) {
        return;
    }

    emOrdem(raiz->esq);
 
    printf("%d", raiz->val);
    printf(", ");

    emOrdem(raiz->dir);
}

/**
 * Funcao que navega pre-ordem na BST e
 * imprime seus elementos.
 **/
void preOrdem(struct noBst* raiz) {
    if (raiz == NULL) {
        return;
    }

    printf("%d", raiz->val);
    printf(", ");
   
    preOrdem(raiz->esq);

    preOrdem(raiz->dir);
}

/**
 * Funcao que navega pos-ordem na BST e
 * imprime seus elementos.
 **/
void posOrdem(struct noBst* raiz) {
    if (raiz == NULL) {
        return;
    }

    posOrdem(raiz->esq);

    posOrdem(raiz->dir);

    printf("%d", raiz->val);
    printf(", ");
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * remove o no que contem o valor passado como
 * argumento. Tamanho deve ser decrementado.
 * Tamanho é passado por referência.
 **/
struct noBst* remover(struct noBst* raiz, int val, int* tamanho) {
    struct noBst* no_aux = raiz;
    if (raiz == NULL) {
        return NULL;
    }
    if ( (*tamanho) == 1 && raiz->val == val) {
        free(raiz);
        tamanho--;
    }
    else if (raiz->val == val) {
        if (raiz->esq == NULL && raiz->dir == NULL) { //caso 1: nó folha
            free(raiz);
            tamanho--;
            return NULL;
        }
        else if (raiz->esq != NULL && raiz->dir != NULL) { //caso 3: nó com 2 filhos
            int val_aux = max(raiz->esq);
            raiz->val = val_aux;
            no_aux = raiz->esq;
            while (no_aux != NULL) {
                no_aux = no_aux->dir;
            }
            raiz = no_aux;
            free(raiz);
            return 0;

        }
        else { //caso 2: nó com 1 filho
           if (raiz->dir != NULL) {
               no_aux = raiz->dir;
           }
           if (raiz->esq != NULL) {
               no_aux = raiz->esq;
           }
           free(raiz);
           tamanho--;
           return no_aux;
        }

    }
    else if (raiz->val > val) {
        struct noBst* no_aux_esq = remover(raiz->esq, val, tamanho);
        if (no_aux_esq == NULL) {
            raiz->esq = NULL;
        }
        else if (no_aux_esq != 0) {
            raiz->esq = no_aux_esq;
        }
            
    }
    else {
        struct noBst* no_aux_dir = remover(raiz->dir, val, tamanho);
        if (no_aux_dir == NULL) {
            raiz->dir = NULL;
        }
        else if (no_aux_dir != 0) {
            raiz->dir = no_aux_dir;
        }
    }
   
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * verifica se a mesma contém um dado valor.
 **/
bool buscar(struct noBst* raiz, int val) {
    if (raiz == NULL) {
        return false;
    }
    else if (raiz->val == val) {
        return true;
    }
    else if (raiz->val > val) {
        return buscar(raiz->esq, val);
    }
    else {
        return buscar(raiz->dir, val);
    }
}