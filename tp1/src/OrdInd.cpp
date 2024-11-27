#include "OrdInd.h"
#include <iostream>
#include <fstream>
#include <cstring>

// Construtor
OrdInd::OrdInd(int numRegistros, int numAtributos) {
    dados = new Matriz(numRegistros, numAtributos);
    indicesNome = new Vetor(numRegistros);
    indicesCPF = new Vetor(numRegistros);
    indicesEndereco = new Vetor(numRegistros);
}

// Destrutor
OrdInd::~OrdInd() {
    delete dados;
    delete indicesNome;
    delete indicesCPF;
    delete indicesEndereco;
}

// Carrega arquivo
bool OrdInd::carregaArquivo(const char *nomeEntrada) {
    std::ifstream arquivo(nomeEntrada);
    if (!arquivo.is_open()) return false;

    char linha[256];
    int registro = 0;
    while (arquivo.getline(linha, sizeof(linha)) && registro < dados->linhas) {
        char *token = strtok(linha, ",");
        int coluna = 0;
        while (token != nullptr && coluna < dados->colunas) {
            dados->set(registro, coluna, token);
            token = strtok(nullptr, ",");
            coluna++;
        }
        registro++;
    }
    arquivo.close();
    return true;
}

// Cria índice
void OrdInd::criaIndice(int atribid) {
    Vetor *indice = nullptr;
    switch (atribid) {
        case 0: indice = indicesNome; break;
        case 1: indice = indicesCPF; break;
        case 2: indice = indicesEndereco; break;
        default: throw std::invalid_argument("ID de atributo inválido.");
    }
    for (int i = 0; i < indice->size(); i++) {
        (*indice)[i] = i;
    }
}

// QuickSort
void OrdInd::quickSort(Vetor &indice, int low, int high, int atributo) {
    if (low < high) {
        int pi = partition(indice, low, high, atributo);
        quickSort(indice, low, pi - 1, atributo);
        quickSort(indice, pi + 1, high, atributo);
    }
}

int OrdInd::partition(Vetor &indice, int low, int high, int atributo) {
    const char *pivot = dados->get(indice[high], atributo);
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(dados->get(indice[j], atributo), pivot) < 0) {
            i++;
            std::swap(indice[i], indice[j]);
        }
    }
    std::swap(indice[i + 1], indice[high]);
    return i + 1;
}

// Ordena índice
void OrdInd::ordenaIndice(int atribid) {
    Vetor *indice = nullptr;
    switch (atribid) {
        case 0: indice = indicesNome; break;
        case 1: indice = indicesCPF; break;
        case 2: indice = indicesEndereco; break;
        default: throw std::invalid_argument("ID de atributo inválido.");
    }
    quickSort(*indice, 0, indice->size() - 1, atribid);
}

// Imprime
void OrdInd::imprimeOrdenadoIndice(int atribid) {
    Vetor *indice = nullptr;
    switch (atribid) {
        case 0: indice = indicesNome; break;
        case 1: indice = indicesCPF; break;
        case 2: indice = indicesEndereco; break;
        default: throw std::invalid_argument("ID de atributo inválido.");
    }

    for (int i = 0; i < indice->size(); i++) {
        int idx = (*indice)[i];
        for (int j = 0; j < dados->colunas; j++) {
            std::cout << dados->get(idx, j) << " ";
        }
        std::cout << std::endl;
    }
}

// Retorna o valor armazenado em uma célula da matriz
const char *OrdInd::getDado(int linha, int coluna) const {
    if (linha < 0 || linha >= dados->linhas || coluna < 0 || coluna >= dados->colunas) {
        throw std::out_of_range("Índices fora dos limites da matriz.");
    }
    return dados->get(linha, coluna);
}

// Modifica o valor armazenado em uma célula da matriz
void OrdInd::setDado(int linha, int coluna, const char *valor) {
    if (linha < 0 || linha >= dados->linhas || coluna < 0 || coluna >= dados->colunas) {
        throw std::out_of_range("Índices fora dos limites da matriz.");
    }
    dados->set(linha, coluna, valor);
}
