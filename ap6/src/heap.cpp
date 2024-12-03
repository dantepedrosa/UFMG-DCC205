#include "./include/heap.hpp"

Heap::Heap(int maxsize) {
    this->tamanho = 0;
    this->data = new int[maxsize];

}

Heap::~Heap() {
    delete[] data;
}

void Heap::Inserir(int x) {
    data[tamanho] = x;
    int index = tamanho;
    tamanho++;
    int ancestral = GetAncestral(index);
    while(index > 0 && data[index] > data[ancestral]) {
        std::swap(data[index], data[ancestral]);
        index = ancestral;
        ancestral = GetAncestral(index);
    }
}

int Heap::Remover() {
    int removido = data[0];
    data[0] = data[tamanho-1];
    tamanho--;
    HeapifyPorBaixo(0);
    return removido;
}

bool Heap::Vazio() {
    if (tamanho == 0)
        return 1;
    else 
        return 0;
}

int Heap::GetAncestral(int posicao) {
    return (posicao-1)/2;
}

int Heap::GetSucessorEsq(int posicao) {
    return (2*posicao) + 1;
}

int Heap::GetSucessorDir(int posicao) {
    return (2*posicao) + 2;
}

void Heap::HeapifyPorBaixo(int posicao) {
    int maior = posicao;
    int esquerda = (2 * posicao) + 1;
    int direita = (2 * posicao) + 2;

    if (esquerda < tamanho && data[esquerda] > data[maior]) {
        maior = esquerda;
    }

    if (direita < tamanho && data[direita] > data[maior]) {
        maior = direita;
    }

    if (maior != posicao) {
        std::swap(data[posicao], data[maior]);
        HeapifyPorBaixo(maior);
    }
}

void Heap::HeapifyPorCima(int posicao) {
    int ancestral = GetAncestral(posicao);
    if (posicao > 0 && data[posicao] > data[ancestral]) {
        std::swap(data[posicao], data[ancestral]);
        HeapifyPorCima(ancestral);
    }
}
