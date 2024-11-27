#include "OrdInd.h"
#include <iostream>
#include <fstream>
#include <algorithm>

// Construtor
OrdInd::OrdInd(int numRegistros, int numAtributos) {
    dados.resize(numRegistros, std::vector<std::string>(numAtributos));
    indicesNome.resize(numRegistros);
    indicesCPF.resize(numRegistros);
    indicesEndereco.resize(numRegistros);

    // Inicializa os índices sequenciais
    for (int i = 0; i < numRegistros; ++i) {
        indicesNome[i] = i;
        indicesCPF[i] = i;
        indicesEndereco[i] = i;
    }
}

// Função de comparação genérica
bool OrdInd::compara(int i, int j, int atributo) const {
    return dados[i][atributo] < dados[j][atributo];
}

// Carrega os dados do arquivo .xcsv
bool OrdInd::carregaArquivo(const std::string &nomeEntrada) {
    std::ifstream arquivo(nomeEntrada);
    if (!arquivo.is_open()) return false;

    std::string linha;
    int registro = 0;
    while (std::getline(arquivo, linha) && registro < dados.size()) {
        size_t pos = 0;
        for (int atributo = 0; atributo < dados[registro].size(); ++atributo) {
            pos = linha.find(',');
            if (pos != std::string::npos) {
                dados[registro][atributo] = linha.substr(0, pos);
                linha.erase(0, pos + 1);
            } else {
                dados[registro][atributo] = linha;
                break;
            }
        }
        ++registro;
    }

    arquivo.close();
    return true;
}

// Ordena os índices por Nome
void OrdInd::ordenaPorNome() {
    std::sort(indicesNome.begin(), indicesNome.end(),
              [this](int i, int j) { return compara(i, j, 0); });
}

// Ordena os índices por CPF
void OrdInd::ordenaPorCPF() {
    std::sort(indicesCPF.begin(), indicesCPF.end(),
              [this](int i, int j) { return compara(i, j, 1); });
}

// Ordena os índices por Endereço
void OrdInd::ordenaPorEndereco() {
    std::sort(indicesEndereco.begin(), indicesEndereco.end(),
              [this](int i, int j) { return compara(i, j, 2); });
}

// Imprime os registros na ordem de Nome
void OrdInd::imprimePorNome() {
    std::cout << "Ordenado por Nome:\n";
    for (int idx : indicesNome) {
        for (const auto &campo : dados[idx]) {
            std::cout << campo << " ";
        }
        std::cout << std::endl;
    }
}

// Imprime os registros na ordem de CPF
void OrdInd::imprimePorCPF() {
    std::cout << "Ordenado por CPF:\n";
    for (int idx : indicesCPF) {
        for (const auto &campo : dados[idx]) {
            std::cout << campo << " ";
        }
        std::cout << std::endl;
    }
}

// Imprime os registros na ordem de Endereço
void OrdInd::imprimePorEndereco() {
    std::cout << "Ordenado por Endereço:\n";
    for (int idx : indicesEndereco) {
        for (const auto &campo : dados[idx]) {
            std::cout << campo << " ";
        }
        std::cout << std::endl;
    }
}
