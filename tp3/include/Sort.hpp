#pragma once

#include <iostream>
#include <string>
#include <ctime>

#include "Voo.hpp"
#include "ListaEncadeada.hpp"

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

// Implementação do Selection Sort utilizando os métodos GetItem e SetItem
void selectionSortListaEncadeada(ListaEncadeada<Voo*>& lista, const std::string& trigrama) {
    int tamanho = lista.GetTamanho();
    for (int i = 0; i < tamanho - 1; i++) {
        int indiceMin = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (compare(lista.GetItem(j), lista.GetItem(indiceMin), trigrama)) {
                indiceMin = j;
            }
        }
        // Troca se o menor elemento não estiver na posição i
        if (indiceMin != i) {
            Voo* temp = lista.GetItem(i);
            lista.SetItem(lista.GetItem(indiceMin), i);
            lista.SetItem(temp, indiceMin);
        }
    }
}

// Função para separar os n menores voos da lista encadeada e armazená-los em arrayDestino
void separarMenoresVoos(ListaEncadeada<Voo*>& lista, Voo** arrayDestino, int n, const std::string& trigrama) {
    // Ordena a lista usando Selection Sort
    selectionSortListaEncadeada(lista, trigrama);

    // Copia os n primeiros voos da lista ordenada para o array de destino
    for (int i = 0; i < n && i < lista.GetTamanho(); i++) {
        arrayDestino[i] = lista.GetItem(i);
    }
}