#include "OrdInd.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream arquivo("entrada.xcsv");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    // Variáveis para leitura do cabeçalho
    int numColunas, numRegistros;
    std::string linha;

    // Ler o número de colunas
    std::getline(arquivo, linha);
    numColunas = std::stoi(linha);

    // Ignorar as próximas linhas que indicam os nomes e formatos
    for (int i = 0; i < numColunas; i++) {
        std::getline(arquivo, linha); // Exemplo: "name,s"
    }

    // Ler o número de registros
    std::getline(arquivo, linha);
    numRegistros = std::stoi(linha);

    // Inicializar a estrutura OrdInd
    OrdInd organizador(numRegistros, numColunas);

    // Ler os registros do arquivo
    int registroAtual = 0;
    while (std::getline(arquivo, linha) && registroAtual < numRegistros) {
        std::istringstream stream(linha);
        std::string campo;
        for (int coluna = 0; coluna < numColunas; coluna++) {
            std::getline(stream, campo, ',');
            organizador.setDado(registroAtual, coluna, campo.c_str());
        }
        registroAtual++;
    }

    arquivo.close();

    // Criar índices para Nome, CPF e Endereço (assumindo colunas 0, 1 e 2)
    organizador.criaIndice(0); // Nome
    organizador.ordenaIndice(0);
    std::cout << "Ordenado por Nome:\n";
    organizador.imprimeOrdenadoIndice(0);

    organizador.criaIndice(1); // CPF
    organizador.ordenaIndice(1);
    std::cout << "\nOrdenado por CPF:\n";
    organizador.imprimeOrdenadoIndice(1);

    organizador.criaIndice(2); // Endereço
    organizador.ordenaIndice(2);
    std::cout << "\nOrdenado por Endereço:\n";
    organizador.imprimeOrdenadoIndice(2);

    return 0;
}
