/**
 * @file Sort.hpp
 * @brief Implementação dos algoritmos de ordenação
 * @author Dante Junqueira Pedrosa
 * @date 2025
 */

#pragma once

#include <iostream>
#include <string>
#include <ctime>

#include "Voo.hpp"

/**
 * @brief Compara dois voos com base no trigrama fornecido
 * @param x Primeiro voo
 * @param y Segundo voo
 * @param trigrama String contendo a ordem de comparação (p=preço, d=duração, s=paradas)
 * @return true se x deve vir antes de y na ordenação
 */
bool compare(const Voo* x, const Voo* y, const std::string& trigrama) {
    for (char var : trigrama) {
        switch (var) {
            case 'p': if (x->preco != y->preco) return x->preco < y->preco; break;
            case 'd': if (x->duracao != y->duracao) return x->duracao < y->duracao; break;
            case 's': if (x->paradas != y->paradas) return x->paradas < y->paradas; break;
        }
    }
    return false;
}

/**
 * @brief Implementa o algoritmo Insertion Sort para ordenação de voos
 * @param voos Array de ponteiros para voos
 * @param n Tamanho do array
 * @param trigrama Critério de ordenação
 */
void insertionsort(Voo* voos[], int n, const std::string& trigrama) {
    for (int i = 1; i < n; ++i) {
        Voo* key = voos[i];
        int j = i - 1;

        while (j >= 0 && compare(key, voos[j], trigrama)) {
            voos[j + 1] = voos[j];
            --j;
        }
        voos[j + 1] = key;
    }
}

/**
 * @brief Implementa o algoritmo Quick Sort para ordenação de voos
 * @param voos Array de ponteiros para voos
 * @param low Índice inicial do subarray
 * @param high Índice final do subarray
 * @param trigrama Critério de ordenação
 */
void quicksort(Voo* voos[], int low, int high, const std::string& trigrama) {
    if (low < high) {
        int pivot = low;
        int i = low, j = high;
        Voo* pivotVoo = voos[pivot];

        while (i < j) {
            while (i <= high && compare(voos[i], pivotVoo, trigrama)) i++;
            while (j >= low && compare(pivotVoo, voos[j], trigrama)) j--;

            if (i < j) std::swap(voos[i], voos[j]);
        }
        std::swap(voos[low], voos[j]);

        quicksort(voos, low, j - 1, trigrama);
        quicksort(voos, j + 1, high, trigrama);
    }
}
