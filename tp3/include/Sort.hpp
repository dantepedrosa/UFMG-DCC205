#pragma once

#include <iostream>
#include <string>
#include <ctime>

#include "Voo.hpp"

// Função de comparação com base no trigrama
bool compare(const Voo* x, const Voo* y, const std::string& trigrama) {
    for (char var : trigrama) {
        switch (var) {
            case 'p': if (x->preco != y->preco) return x->preco < y->preco; break;
            case 'd': if (x->duracao != y->duracao) return x->duracao < y->duracao; break;
            case 's': if (x->numParadas != y->numParadas) return x->numParadas < y->numParadas; break;
        }
    }
    return false;
}

// Implementação do QuickSort
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

// Função de ordenação
void sort(Voo* voos[], int numLinhas, const std::string& trigrama) {
    quicksort(voos, 0, numLinhas - 1, trigrama);
}