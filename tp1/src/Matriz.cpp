#include "Matriz.h"

// Construtor
Matriz::Matriz(int linhas, int colunas) {
    this->linhas = linhas;
    this->colunas = colunas;
    dados = new char **[linhas];
    for (int i = 0; i < linhas; i++) {
        dados[i] = new char *[colunas];
        for (int j = 0; j < colunas; j++) {
            dados[i][j] = nullptr;
        }
    }
}

// Destrutor
Matriz::~Matriz() {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            delete[] dados[i][j];
        }
        delete[] dados[i];
    }
    delete[] dados;
}

// Define um valor
void Matriz::set(int linha, int coluna, const char *valor) {
    if (dados[linha][coluna] != nullptr) {
        delete[] dados[linha][coluna];
    }
    dados[linha][coluna] = new char[strlen(valor) + 1];
    strcpy(dados[linha][coluna], valor);
}

// Obtém um valor
const char *Matriz::get(int linha, int coluna) const {
    return dados[linha][coluna];
}
