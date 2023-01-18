#pragma once
#include <cstdlib>

void selectionSortOP(int** v, int tamanho) {
    int* ordenado = (int*)malloc(sizeof(int) * tamanho);

    for (int j = 0; j < tamanho; j++) {

        int i_min = 0;
        for (int i = 0; i < tamanho; i++) {
            if ((*v)[i] < (*v)[i_min]) {
                i_min = i;
            }
        }
        ordenado[j] = (*v)[i_min];
        (*v)[i_min] = INT_MAX;
    }
    *v = ordenado;
}

void selectionSortIP(int* v, int tamanho) {
    int aux = 0;
    for (int j = 0; j < tamanho - 1; j++) {
        int i_min = j;
        for (int i = j + 1; i < tamanho; i++) {
            if (v[i] < v[i_min]) {
                i_min = i;
            }
        }
        aux = v[j];
        v[j] = v[i_min];
        v[i_min] = aux;
        //troca(v, i, i_min);
    }
}




int particiona(int* v, int ini, int fim) {
    int aleatorio = (rand() % (fim - ini)) + ini;
    int aux = v[fim];
    v[fim] = v[aleatorio];
    v[aleatorio] = aux;

    int pIndex = ini;
    int pivo = v[fim];
    for (int i = ini; i < fim; i++) {
        if (v[i] <= pivo) {
            int temp = v[pIndex];
            v[pIndex] = v[i];
            v[i] = temp;
            pIndex++;
        }
    }
    int temp = v[pIndex];
    v[pIndex] = v[fim];
    v[fim] = temp;
    return pIndex;
}

void quickSort(int* v, int ini, int fim) {
    if (fim > ini) {
        int indexPivo = particiona(v, ini, fim);
        quickSort(v, ini, indexPivo - 1);
        quickSort(v, indexPivo + 1, fim);
    }
}