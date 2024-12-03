#include "heap.hpp"
#include <algorithm>
#include <iostream>

Heap::Heap(int maxsize) {
    data = new int[maxsize];
    tamanho = 0;
}

Heap::~Heap() {
    delete[] data;
}

void Heap::Inserir(int x) {
    data[tamanho] = x;
    int i = tamanho;
    tamanho++;
    while (i != 0 && data[GetAncestral(i)] > data[i]) {
        std::swap(data[i], data[GetAncestral(i)]);
        i = GetAncestral(i);
    }
}

int Heap::Remover() {
    if (tamanho <= 0) {
        std::cerr << "Heap is empty" << std::endl;
        return -1;
    }
    if (tamanho == 1) {
        tamanho--;
        return data[0];
    }

    int root = data[0];
    data[0] = data[tamanho - 1];
    tamanho--;
    HeapifyPorBaixo(0);
    return root;
}

bool Heap::Vazio() {
    return tamanho == 0;
}

int Heap::GetAncestral(int posicao) {
    return (posicao - 1) / 2;
}

int Heap::GetSucessorEsq(int posicao) {
    return 2 * posicao + 1;
}

int Heap::GetSucessorDir(int posicao) {
    return 2 * posicao + 2;
}

void Heap::HeapifyPorBaixo(int posicao) {
    int smallest = posicao;
    int left = GetSucessorEsq(posicao);
    int right = GetSucessorDir(posicao);

    if (left < tamanho && data[left] < data[smallest])
        smallest = left;
    if (right < tamanho && data[right] < data[smallest])
        smallest = right;
    if (smallest != posicao) {
        std::swap(data[posicao], data[smallest]);
        HeapifyPorBaixo(smallest);
    }
}

void Heap::HeapifyPorCima(int posicao) {
    while (posicao != 0 && data[GetAncestral(posicao)] > data[posicao]) {
        std::swap(data[posicao], data[GetAncestral(posicao)]);
        posicao = GetAncestral(posicao);
    }
}