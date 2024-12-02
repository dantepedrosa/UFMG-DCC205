#include "./include/heap.hpp"

Heap::Heap(int maxsize) {
    this->tamanho = 0;
    this->data = new int[maxsize];

}

Heap::~Heap() {
    // TODO
}

void Heap::Inserir(int x) {
    data[tamanho] = x;
    int index = tamanho;
    tamanho++;
    int ancestral = GetAncestral(index);
    while(index > 0 && data[index] > data[ancestral]) {
        int tmp = data[ancestral];
        data[ancestral] = data[index];
        data[tamanho] = tmp;

        index = ancestral;
        ancestral = GetAncestral(index);
    }
}

int Heap::Remover() {
    // TODO
}

bool Heap::Vazio() {
    // TODO
}

int Heap::GetAncestral(int posicao) {
    // TODO
}

int Heap::GetSucessorEsq(int posicao) {
    // TODO
}

int Heap::GetSucessorDir(int posicao) {
    // TODO
}

void Heap::HeapifyPorBaixo(int posicao) {
    // TODO
}

void Heap::HeapifyPorCima(int posicao) {
    // TODO
}
