#include "OrdInd.h"
#include <fstream>
#include <iostream>

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

// Carrega os dados de um arquivo .xcsv
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

// Métodos de acesso aos índices
std::vector<int> &OrdInd::getIndicesNome() { return indicesNome; }
std::vector<int> &OrdInd::getIndicesCPF() { return indicesCPF; }
std::vector<int> &OrdInd::getIndicesEndereco() { return indicesEndereco; }

// Acessa o dado correspondente ao índice e atributo
const std::string &OrdInd::getDado(int index, int atributo) const {
    return dados[index][atributo];
}

// Retorna o número total de registros
int OrdInd::getNumRegistros() const { return dados.size(); }
