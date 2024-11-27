#include "Vetor.h"

// Construtor
Vetor::Vetor(int tamanho) {
    this->tamanho = tamanho;
    dados = new int[tamanho];
    for (int i = 0; i < tamanho; i++) {
        dados[i] = i; // Inicializa índices sequenciais
    }
}

// Destrutor
Vetor::~Vetor() {
    delete[] dados;
}

// Acessa elemento
int &Vetor::operator[](int i) {
    return dados[i];
}

// Obtém tamanho
int Vetor::size() const {
    return tamanho;
}
