#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>
using namespace std;

void atualizar(struct noBst* no);
struct noBst* balancear(struct noBst* no);
struct noBst* rebalancearEsqEsq(struct noBst* no);
struct noBst* rebalancearEsqDir(struct noBst* no);
struct noBst* rebalancearDirDir(struct noBst* no);
struct noBst* rebalancearDirEsq(struct noBst* no);

/**
 * Embora durante a aula eu disse que precisaríamos
 * das variáveis alturaEsq e alturaDir, na verdade não
 * é necessário. Depois de implementar que percebi algo
 * óbvio: para pegar a altura de uma sub-árvore basta
 * obter o valor da variável altura na sub-árvore. (:
 **/

struct noBst {
    int val;
    int altura;
    int balanco;
    struct noBst* esq;
    struct noBst* dir;
};

/**
 * Funcao que aloca um novo noBst, e
 * ajusta os ponteiros esq e dir para NULL,
 * e variáveis altura e balanco para 0.
 **/
struct noBst* alocarNovoNo(int val) {
    struct noBst* novoNo = (struct noBst*)malloc(sizeof(struct noBst));
    novoNo->val = val;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    atualizar(novoNo);

    return novoNo;
}

/**
 * Funcao que rotaciona uma arvore para a
 * direita e retorna a nova raiz.
 **/
struct noBst* rotacaoDireita(struct noBst* arvore) {
    struct noBst* aux_esq = arvore->esq;
    arvore->esq = arvore->esq->dir;
    aux_esq->dir = arvore;
    atualizar(aux_esq->dir);
    atualizar(aux_esq);
    return aux_esq;
}

/**
 * Funcao que rotaciona uma arvore para a
 * esquerda e retorna a nova raiz.
 **/
struct noBst* rotacaoEsquerda(struct noBst* arvore) {
    struct noBst* aux_dir = arvore->dir;
    arvore->dir = arvore->dir->esq;
    aux_dir->esq = arvore;
    atualizar(aux_dir->esq);
    atualizar(aux_dir);
    return aux_dir;
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * insere um novo valor na BST. Tamanho deve
 * ser incrementado.
 * Ambos tamanho e raiz são passados por referência.
 * Lembrar de atualizar altura e fator de balanco dos nós
 * antecessores do nó inserido, bem como balanceá-los caso
 * seja necessário.
 * Dica: reutilizar a função de inserir de BST, e lembrar
 * de como usar inteligentemente a recursão para conseguir
 * atualizar e balancear os nós antecessores.
 **/
void inserir(struct noBst** raiz, int val, int* tamanho) {
    if (*raiz == NULL) {
        (*raiz) = alocarNovoNo(val);
        (*tamanho)++;
    }
    else if (val <= (*raiz)->val) {
        inserir(&((*raiz)->esq), val, tamanho);
    }
    else {
        inserir(&((*raiz)->dir), val, tamanho);
    }
    atualizar(*raiz);
    balancear(*raiz);
}

/**
 * Funcao que recebe a raiz de uma BST e atualiza sua altura
 * e fator de balanço.
 * Lembre que a altura das sub-árvores direita e esquerda
 * não vão mudar, por isso a implementação não é tão complicada.
 **/
void atualizar(struct noBst* no) {
    if (no == NULL) {
        return;
    }
    if (no->esq != NULL && no->dir != NULL) {
        if (no->esq->altura >= no->dir->altura) {
            no->altura = no->esq->altura + 1;
        }
        else {
            no->altura = no->dir->altura + 1;
        }
        no->balanco = (no->dir->altura - no->esq->altura);
    }
    else if (no->esq == NULL && no->dir != NULL) {
        no->altura = no->dir->altura + 1;
        no->balanco = (no->dir->altura);
    }
    else if (no->dir == NULL && no->esq != NULL) {
        no->altura = no->esq->altura + 1;
        no->balanco = (0 - no->esq->altura);
    }
    else {
        no->altura = 0;
        no->balanco = 0;
    }
}

/**
 * Funcao que recebe a raiz de uma BST e identifica em qual caso
 * ela se encaixa para executar os procedimentos de balanceamento
 * corretos:
 *      - Caso 1: esquerda-esquerda e esquerda-cheio
 *      - Caso 2: esquerda-direita
 *      - Caso 3: direita-direita e direita-cheio
 *      - Caso 4: direita-esquerda
 * Dica: usar fator de balanço do nó e de uma de suas sub-árvores
 * para descobrir qual é o caso.
 **/
struct noBst* balancear(struct noBst* no) {
    if (no == NULL) {
        return NULL;
    }
    if(no->balanco == -2){ //CASO 1-2
        if (no->esq->balanco == -1) { //ESQ-ESQ
            no = rebalancearEsqEsq(no);
        }
        else if (no->esq->balanco == 1) { //ESQ-DIR
            no = rebalancearEsqDir(no);
        }
    }
    else if (no->balanco == 2) { //CASO 3-4
        if (no->dir->balanco == 1) { //DIR-DIR
            no = rebalancearDirDir(no);
        }
        else if (no->dir->balanco == -1) { //DIR-ESQ
            no = rebalancearDirEsq(no);
        }
    }
    else {
        return no;
    }
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 1.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBst* rebalancearEsqEsq(struct noBst* no) {
    return rotacaoDireita(no);
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 2.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBst* rebalancearEsqDir(struct noBst* no) {
    no->esq = rotacaoEsquerda(no->esq);
    return rebalancearEsqEsq(no);
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 3.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBst* rebalancearDirDir(struct noBst* no) {
    return rotacaoEsquerda(no);
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 4.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBst* rebalancearDirEsq(struct noBst* no) {
    no->dir = rotacaoDireita(no->dir);
    return rebalancearDirDir(no);
}

/**
 * Funcao que retorna o maior valor de uma árvore.
 * Mesma implementação da BST.
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

/**
 * Funcao que retorna o menor valor de uma árvore.
 * Mesma implementação da BST.
 **/
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
 * Funcao que retorna a altura de uma árvore.
 * A altura de uma árvore é dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 * Mesma implementação da BST.
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
 * Funcao que recebe a raiz de uma árvore, e
 * remove o nó que contem o valor passado como
 * argumento. Tamanho deve ser decrementado.
 * Tamanho é passado por referência.
 * Lembrar de atualizar altura e fator de balanco dos nós
 * antecessores do nó removido, bem como balanceá-los caso
 * seja necessário.
 * Dica: reutilizar a função de remover de BST, e lembrar
 * de como usar inteligentemente a recursão para conseguir
 * atualizar e balancear os nós antecessores.
 **/
struct noBst* remover(struct noBst* raiz, int val, int* tamanho) {
    struct noBst* no_aux = raiz;
    if (raiz == NULL) {
        return NULL;
    }
    if (raiz->val == val) {
        if (raiz->esq == NULL && raiz->dir == NULL) { //caso 1: nó folha
            free(raiz);
            tamanho--;
            //return raiz;
        }
        else if (raiz->esq != NULL && raiz->dir != NULL) { //caso 3: nó com 2 filhos
            if (raiz->esq->altura >= raiz->dir->altura) {
                int val_aux = max(raiz->esq);
                raiz->val = val_aux;
                no_aux = raiz->esq;
                while (no_aux != NULL) {
                    no_aux = no_aux->dir;
                }
                raiz = no_aux;
                free(raiz);
            }
            else if (raiz->esq->altura < raiz->dir->altura) {
                int val_aux = min(raiz->dir);
                raiz->val = val_aux;
                no_aux = raiz->dir;
                while (no_aux != NULL) {
                    no_aux = no_aux->esq;
                }
                raiz = no_aux;
                free(raiz); 
            }
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
        raiz->esq = remover(raiz->esq, val, tamanho);
    }
    else if (raiz->val < val) {
        raiz->dir = remover(raiz->dir, val, tamanho);
    }
    atualizar(raiz);
    balancear(raiz);
    return raiz;
}

void imprimir(queue<struct noBst*> nosImpressao);

/**
* Função que imprime a árvore.
* Pode ser útil para depuração.
**/
void imprimir(struct noBst* raiz) {
    queue<struct noBst*> nosImpressao;
    nosImpressao.push(raiz);
    imprimir(nosImpressao);
}

void imprimir(queue<struct noBst*> nosImpressao) {

    queue<struct noBst*> nosImpressaoProxNivel;

    while (!nosImpressao.empty()) {
        struct noBst* noImpressao = nosImpressao.front();
        //add filhos na fila
        if (noImpressao != NULL) {
            if (noImpressao->esq != NULL)
                nosImpressaoProxNivel.push(noImpressao->esq);
            else
                nosImpressaoProxNivel.push(NULL);
            if (noImpressao->dir != NULL)
                nosImpressaoProxNivel.push(noImpressao->dir);
            else
                nosImpressaoProxNivel.push(NULL);
        }
        nosImpressao.pop();

        if (noImpressao != NULL) {
            cout << to_string(noImpressao->val) << " | ";
        }
        else {
            cout << "N | ";
        }
    }
    cout << endl << endl;
    if (!nosImpressaoProxNivel.empty())
        imprimir(nosImpressaoProxNivel);
}