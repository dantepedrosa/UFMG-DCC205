/**
 * @file main.cpp
 * @brief Programa principal para processamento de consultas de voos
 * @author Dante Junqueira Pedrosa
 * @date 2025
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

/* EXCLUSIVAMENTE PARA TESTES
#include "doctest.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
bool confereOutput(Voo** voos, int numVoos, std::string consulta, std::string filePath);
*/

/**
 * @brief Estrutura para armazenar dados de uma consulta
 */
struct Consulta {
    std::string str;          // String original da consulta
    int numResultados;        // Número de resultados desejados
    std::string trigrama;     // Critério de ordenação
    std::string expression;   // Expressão de filtragem
};

void leConsultasdeEntrada(Consulta** consultas, int numConsultas);
void leConsultasdeArquivo(std::ifstream& inputFile, Consulta** consultas, int numConsultas);
void separarMenoresVoos(ListaEncadeada<Voo*>& lista, Voo** arrayDestino, int n, const std::string& trigrama);
void imprimirVoos(Voo** voos, int numVoos);
void leVoosdeArquivo(std::ifstream& inputFile, Voo** voos, int numLinhas);
void leVoosdeEntrada(Voo** voos, int numLinhas);


int main(int argc, char const* argv[]) {

    // Inicialização
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

    // Leitura de dados
    // ---------------------------------------------------
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
    // ---------------------------------------------------
    for (int i = 0; i < numConsultas; i++) {
        std::cout << consultas[i]->str << std::endl;

        ListaEncadeada<std::string> tokens = tokenizar(consultas[i]->expression);
        No* root = montaArvoreExpressao(tokens);
        ListaEncadeada<Voo*> voosFiltrados = filtrarVoos(root, voos, numLinhas);

        // Separa os primeiros n voos na ordenação especificada
        int numResultados = std::min(consultas[i]->numResultados, voosFiltrados.GetTamanho());
        Voo* menoresVoos[numResultados];

        separarMenoresVoos(voosFiltrados, menoresVoos, numResultados, consultas[i]->trigrama);
        imprimirVoos(menoresVoos, numResultados);
        //confereOutput(menoresVoos, numResultados, consultas[i]->str, filePath);
        
        deleteTree(root);   // Apaga a árvore de expressão
    }

    // Liberação de memória
    // ---------------------------------------------------
    for (int i = 0; i < numLinhas; i++) delete voos[i];
    delete[] voos;

    for (int i = 0; i < numConsultas; i++) delete consultas[i];
    delete[] consultas;

    return 0;
}

/* EXCLUSIVAMENTE PARA TESTES 
bool confereOutput(Voo** voos, int numVoos, std::string consulta, std::string filePath) {
    size_t pos = filePath.find("inputs/input_");
    if (pos != std::string::npos) {
        filePath.replace(pos, 12, "outputs/output_");
    }

    std::ifstream inputFile(filePath);
    std::string line;

    std::getline(inputFile, line);
    CHECK(line == consulta);
    for (int i = 0; i < numVoos; i++) {
        std::getline(inputFile, line);
        if (line != voos[i]->str) {
            return false;
        }
    }

    inputFile.close();

    return true;
}
*/

/**
 * @brief Lê as consultas da entrada padrão
 * @param consultas Array de ponteiros para consultas a ser preenchido
 * @param numConsultas Número de consultas a serem lidas
 */
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

/**
 * @brief Lê as consultas de um arquivo
 * @param inputFile Arquivo de entrada
 * @param consultas Array de ponteiros para consultas a ser preenchido
 * @param numConsultas Número de consultas a serem lidas
 */
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

/**
 * @brief Separa os n menores voos de uma lista
 * @param lista Lista de voos
 * @param arrayDestino Array para armazenar os voos selecionados
 * @param n Número de voos a serem selecionados
 * @param trigrama Critério de ordenação
 */
void separarMenoresVoos(ListaEncadeada<Voo*>& lista, Voo** arrayDestino, int n,
                        const std::string& trigrama) {

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

/**
 * @brief Imprime a lista de voos filtrados
 * @param voos Array de ponteiros para voos
 * @param numVoos Número de voos a serem impressos
 */
void imprimirVoos(Voo** voos, int numVoos) {
    for (int i = 0; i < numVoos; i++) {
        Voo* voo = voos[i];
        std::cout << voo->str << std::endl;
    }
}

/**
 * @brief Lê voos de um arquivo
 * @param inputFile Arquivo de entrada
 * @param voos Array de ponteiros para voos a ser preenchido
 * @param numLinhas Número de linhas (voos) a serem lidas
 */
void leVoosdeArquivo(std::ifstream& inputFile, Voo** voos, int numLinhas) {
    std::string line;

    for (int i = 0; i < numLinhas; i++) {
        std::getline(inputFile, line);
        voos[i] = new Voo(line);
    }
}

/**
 * @brief Lê voos da entrada padrão
 * @param voos Array de ponteiros para voos a ser preenchido
 * @param numLinhas Número de linhas (voos) a serem lidas
 */
void leVoosdeEntrada(Voo** voos, int numLinhas) {
    std::string line;
    for (int i = 0; i < numLinhas; i++) {
        std::getline(std::cin, line);
        voos[i] = new Voo(line);
    }
}


