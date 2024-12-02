#include "OrdInd.h"
#include <iostream>
#include <fstream>
#include <cstring>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: bin/tp1.out <arquivo_de_entrada.xcsv>" << std::endl;
        return 1;
    }

    const char *nomeArquivo = argv[1];

    // Abrir o arquivo de entrada
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return 1;
    }

    // Ler cabeçalho
    int numColunas, numRegistros;
    std::string linha;
    std::getline(arquivo, linha);
    numColunas = std::stoi(linha);

    // Ignorar descrições de colunas
    for (int i = 0; i < numColunas; i++) {
        std::getline(arquivo, linha);
    }

    // Ler número de registros
    std::getline(arquivo, linha);
    numRegistros = std::stoi(linha);

    // Inicializar a classe OrdInd
    OrdInd organizador(numRegistros, numColunas);

    // Ler registros
    int registroAtual = 0;
    while (std::getline(arquivo, linha) && registroAtual < numRegistros) {
        char *token = strtok(&linha[0], ",");
        for (int coluna = 0; coluna < numColunas; coluna++) {
            organizador.setDado(registroAtual, coluna, token);
            token = strtok(nullptr, ",");
        }
        registroAtual++;
    }
    arquivo.close();

    // Algoritmos e chaves
    auto algoritmos = {"QuickSort", "BubbleSort", "SelectionSort"};
    auto chaves = {0, 1, 2}; // Nome, ID, Endereço

    // Iterar pelos algoritmos e chaves
    for (const auto &algoritmo : algoritmos) {
        for (const auto &chave : chaves) {
            // Criar índice
            organizador.criaIndice(chave);

            // Ordenar de acordo com o algoritmo
            if (algoritmo == "QuickSort") {
                organizador.ordenaIndiceQuickSort(chave);
            } else if (algoritmo == "BubbleSort") {
                organizador.ordenaIndiceBubbleSort(chave);
            } else if (algoritmo == "SelectionSort") {
                organizador.ordenaIndiceSelectionSort(chave);
            }

            // Imprimir saída formatada
            std::cout << numColunas << std::endl;
            std::cout << "name,s\nid,s\naddress,s\npayload,s\n";
            std::cout << numRegistros << std::endl;
            organizador.imprimeOrdenadoIndice(chave);
        }
    }

    return 0;
}
