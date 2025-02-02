/**
 * @file main.cpp
 * @brief Programa principal para processamento de consultas de voos
 * @author Meirielen Andrade
 * @date 2023
 */

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/Filtro.hpp"
#include "../include/ListaEncadeada.hpp"
#include "../include/Pilha.hpp"
#include "../include/Sort.hpp"
#include "../include/Voo.hpp"

/**
 * @brief Separa os n menores voos de uma lista
 * @param lista Lista de voos
 * @param arrayDestino Array para armazenar os voos selecionados
 * @param n Número de voos a serem selecionados
 * @param trigrama Critério de ordenação
 */
void separarMenoresVoos(ListaEncadeada<Voo*>& lista, Voo** arrayDestino, int n,
                        const std::string& trigrama) {
    std::cout << "Separando os " << n << " menores voos..." << std::endl;

    Voo* temp[lista.GetTamanho()];

    // Ordena a lista usando Selection Sort
    for (int i = 0; i < lista.GetTamanho(); i++) {
        temp[i] = lista.GetItem(i);
    }

    insertionsort(temp, lista.GetTamanho(), trigrama);
    quicksort(temp, 0, lista.GetTamanho() - 1, trigrama);

    // Copia os n primeiros voos da lista ordenada para o array de destino
    for (int i = 0; i < n && i < lista.GetTamanho(); i++) {
        arrayDestino[i] = temp[i];
    }
}

// Imprime a lista de voos filtrados
void imprimirVoos(Voo** voos, int numVoos) {
    for (int i = 0; i < numVoos; i++) {
        Voo* voo = voos[i];
        std::cout << voo->str << std::endl;
    }
}

// Lê voos de um arquivo
void leVoosdeArquivo(std::ifstream& inputFile, Voo** voos, int numLinhas) {
    std::string line;

    for (int i = 0; i < numLinhas; i++) {
        std::getline(inputFile, line);
        voos[i] = new Voo(line);
    }
}

// Lê voos da entrada padrão
void leVoosdeEntrada(Voo** voos, int numLinhas) {
    std::string line;
    for (int i = 0; i < numLinhas; i++) {
        std::getline(std::cin, line);
        voos[i] = new Voo(line);
    }
}

/**
 * @brief Estrutura para armazenar dados de uma consulta
 */
struct Consulta {
    std::string str;          // String original da consulta
    int numResultados;        // Número de resultados desejados
    std::string trigrama;     // Critério de ordenação
    std::string expression;   // Expressão de filtragem
};

void leConsultasdeArquivo(std::ifstream& inputFile, Consulta** consultas,
                          int numConsultas) {
    std::string line;

    for (int i = 0; i < numConsultas; i++) {
        std::getline(inputFile, line);
        consultas[i] = new Consulta(); // Initialize the Consulta object
        consultas[i]->str = line;
        std::istringstream iss(line);
        iss >> consultas[i]->numResultados;
        iss >> consultas[i]->trigrama;
        iss >> consultas[i]->expression;
    }
}

void leConsultasdeEntrada(Consulta** consultas, int numConsultas) {
    std::string line;

    for (int i = 0; i < numConsultas; i++) {
        std::getline(std::cin, line);   
        consultas[i] = new Consulta(); // Initialize the Consulta object
        consultas[i]->str = line;
        std::istringstream iss(line);
        iss >> consultas[i]->numResultados;
        iss >> consultas[i]->trigrama;
        iss >> consultas[i]->expression;
    }
}

int main(int argc, char const* argv[]) {
    // Leitura de dados
    // ---------------------------------------------------

    bool fileEnabled = false;
    std::string filePath;

    switch (argc) {
        case 1:
            fileEnabled = false;
            return 1;
        case 2:
            fileEnabled = true;
            filePath = argv[1];
            break;
        default:
            std::cerr << "Uso: " << argv[0] << " <caminho_para_arquivo> [-f]"
                      << std::endl;
            return 1;
    }

    std::string line;
    std::istringstream iss;
    int numLinhas;
    int numConsultas;
    
    Voo** voos;
    Consulta** consultas;

    if (fileEnabled) {
        std::ifstream inputFile(filePath);
        std::getline(inputFile, line);
        numLinhas = std::stoi(line);

        voos = new Voo*[numLinhas];
        leVoosdeArquivo(inputFile, voos, numLinhas);

        std::getline(inputFile, line);
        numConsultas = std::stoi(line);
        consultas = new Consulta*[numConsultas];
        leConsultasdeArquivo(inputFile, consultas, numConsultas);

        inputFile.close();
    } else {
        std::getline(std::cin, line);
        numLinhas = std::stoi(line);

        voos = new Voo*[numLinhas];
        leVoosdeEntrada(voos, numLinhas);

        std::getline(std::cin, line);
        numConsultas = std::stoi(line);
        consultas = new Consulta*[numConsultas];
        leConsultasdeEntrada(consultas, numConsultas);
    }

    // Processamento de consultas
    for (int i = 0; i < numConsultas; i++) {
        std::cout << "Consulta: " << consultas[i]->str << std::endl;

        ListaEncadeada<std::string> tokens = tokenizar(consultas[i]->expression);
        No* root = montaArvoreExpressao(tokens);

        ListaEncadeada<Voo*> voosFiltrados = filtrarVoos(root, voos, numLinhas);

        // Separa os 3 menores voos
        int numResultados;
        if(consultas[i]->numResultados > voosFiltrados.GetTamanho()) {
            numResultados = voosFiltrados.GetTamanho();
        } else {
            numResultados = consultas[i]->numResultados;
        }
        Voo* menoresVoos[numResultados];

        separarMenoresVoos(voosFiltrados, menoresVoos, numResultados, consultas[i]->trigrama);

        // Imprime os voos filtrados
        imprimirVoos(menoresVoos, numResultados);

        // Função lambda para liberar recursivamente os nós da árvore de
        // expressão
        std::function<void(No*)> deleteTree = [&](No* node) {
            if (!node) return;
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        };
        deleteTree(root);
    }

    // Liberação de memória
    // ---------------------------------------------------
    for (int i = 0; i < numLinhas; i++) delete voos[i];
    delete[] voos;

    for (int i = 0; i < numConsultas; i++) delete consultas[i];
    delete[] consultas;

    return 0;
}
