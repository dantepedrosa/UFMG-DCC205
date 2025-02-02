/**
 * @file main.cpp
 * @brief Sistema de processamento e filtragem de voos
 * @author Dante Junqueira Pedrosa
 * @date 2025
 */

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "../include/ArvoreDeExpressao.hpp"
#include "../include/ListaEncadeada.hpp"
#include "../include/Pilha.hpp"
#include "../include/Sort.hpp"
#include "../include/Voo.hpp"
#include "../include/IndiceVoos.hpp"
#include "../include/GerenciadorIndices.hpp"


/**
 * @brief Estrutura para armazenar dados de uma consulta de voos
 */
struct Consulta {
    std::string str;          // String original da consulta
    int numResultados;        // Número de resultados desejados
    std::string trigrama;     // Critério de ordenação
    std::string expression;   // Expressão de filtragem
};

/**
 * @brief Lê as consultas da entrada padrão
 * @param consultas Array de ponteiros para consultas a ser preenchido
 * @param numConsultas Número de consultas a serem lidas
 */
void leConsultasdeEntrada(Consulta** consultas, int numConsultas);

/**
 * @brief Lê as consultas de um arquivo
 * @param inputFile Arquivo de entrada
 * @param consultas Array de ponteiros para consultas a ser preenchido
 * @param numConsultas Número de consultas a serem lidas
 */
void leConsultasdeArquivo(std::ifstream& inputFile, Consulta** consultas, int numConsultas);

/**
 * @brief Separa os n menores voos de uma lista
 * @param lista Lista de voos
 * @param arrayDestino Array para armazenar os voos selecionados
 * @param n Número de voos a serem selecionados
 * @param trigrama Critério de ordenação
 */
void separarMenoresVoos(ListaEncadeada<Voo*>& lista, Voo** arrayDestino, int n, const std::string& trigrama);

/**
 * @brief Imprime a lista de voos filtrados
 * @param voos Array de ponteiros para voos
 * @param numVoos Número de voos a serem impressos
 */
void imprimirVoos(Voo** voos, int numVoos);

/**
 * @brief Lê voos de um arquivo
 * @param inputFile Arquivo de entrada
 * @param voos Array de ponteiros para voos a ser preenchido
 * @param numLinhas Número de linhas (voos) a serem lidas
 */
void leVoosdeArquivo(std::ifstream& inputFile, Voo** voos, int numLinhas);

/**
 * @brief Lê voos da entrada padrão
 * @param voos Array de ponteiros para voos a ser preenchido
 * @param numLinhas Número de linhas (voos) a serem lidas
 */
void leVoosdeEntrada(Voo** voos, int numLinhas);

/**
 * @brief Função principal do programa
 * @param argc Número de argumentos da linha de comando
 * @param argv Array de argumentos da linha de comando
 * @return 0 em caso de sucesso, 1 em caso de erro
 */
int main(int argc, char const* argv[]) {
    try {
        // Inicialização
        // ---------------------------------------------------

        bool fileEnabled = false;
        std::string filePath;
        std::string line;
        std::istringstream iss;
        int numLinhas;
        int numConsultas;
        
        Voo** voos;
        Consulta** consultas;
        GerenciadorIndices indices;  // Moved declaration here

        // Leitura de dados
        // Trata diferente para caso seja entrada padrão ou arquivo
        // ---------------------------------------------------
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

        if (fileEnabled) {
            std::ifstream inputFile(filePath);
            if (!inputFile.is_open()) {
                std::cerr << "Erro: não foi possível abrir o arquivo " << filePath << std::endl;
                return 1;
            }
            std::getline(inputFile, line);
            numLinhas = std::stoi(line);

            voos = new Voo*[numLinhas];
            leVoosdeArquivo(inputFile, voos, numLinhas);

            // Criar e preencher os índices após carregar os voos
            for (int i = 0; i < numLinhas; i++) {
                indices.inserirVoo(voos[i], i);
            }

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

            // Criar e preencher os índices após carregar os voos
            for (int i = 0; i < numLinhas; i++) {
                indices.inserirVoo(voos[i], i);
            }

            std::getline(std::cin, line);
            numConsultas = std::stoi(line);
            consultas = new Consulta*[numConsultas];
            leConsultasdeEntrada(consultas, numConsultas);
        }

        // Processamento de consultas
        // ---------------------------------------------------
        for (int i = 0; i < numConsultas; i++) {
            std::cout << consultas[i]->str << std::endl;

            // Cria a árvore de expressão e filtra os voos
            ArvoreDeExpressao arvore(consultas[i]->expression);
            ListaEncadeada<Voo*> voosFiltrados = arvore.filtrarVoos(voos, numLinhas);

            // Processar resultados
            int numResultados = std::min(consultas[i]->numResultados, voosFiltrados.GetTamanho());
            Voo* menoresVoos[numResultados];
            separarMenoresVoos(voosFiltrados, menoresVoos, numResultados, consultas[i]->trigrama);
            
            imprimirVoos(menoresVoos, numResultados);
        }

        // Liberação de memória
        // ---------------------------------------------------
        for (int i = 0; i < numLinhas; i++) delete voos[i];
        delete[] voos;

        for (int i = 0; i < numConsultas; i++) delete consultas[i];
        delete[] consultas;

    } catch (const std::exception& e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}


void leConsultasdeEntrada(Consulta** consultas, int numConsultas) {
    std::string line;

    for (int i = 0; i < numConsultas; i++) {
        std::getline(std::cin, line);   
        consultas[i] = new Consulta(); // Inicializar o array de Consulta
        consultas[i]->str = line;
        std::istringstream iss(line);
        iss >> consultas[i]->numResultados;
        iss >> consultas[i]->trigrama;
        iss >> consultas[i]->expression;
    }
}


void leConsultasdeArquivo(std::ifstream& inputFile, Consulta** consultas,
                          int numConsultas) {
    if (!inputFile.is_open()) {
        throw std::runtime_error("Erro: arquivo não está aberto para leitura");
    }
    
    std::string line;
    for (int i = 0; i < numConsultas; i++) {
        if (!std::getline(inputFile, line)) {
            std::cerr << "Erro: fim inesperado do arquivo na consulta " << i + 1 << std::endl;
            throw std::runtime_error("Número insuficiente de consultas no arquivo");
        }
        
        consultas[i] = new Consulta();
        consultas[i]->str = line;
        std::istringstream iss(line);
        
        if (!(iss >> consultas[i]->numResultados >> consultas[i]->trigrama >> consultas[i]->expression)) {
            std::cerr << "Erro: formato inválido na consulta " << i + 1 << std::endl;
            throw std::invalid_argument("Formato de consulta inválido");
        }
        
        // Validar trigrama
        if (consultas[i]->trigrama.length() != 3) {
            std::cerr << "Erro: trigrama deve ter exatamente 3 caracteres" << std::endl;
            throw std::invalid_argument("Trigrama inválido");
        }
        
        for (char c : consultas[i]->trigrama) {
            if (c != 'p' && c != 'd' && c != 's') {
                std::cerr << "Erro: caracteres do trigrama devem ser 'p', 'd' ou 's'" << std::endl;
                throw std::invalid_argument("Caractere inválido no trigrama");
            }
        }
    }
}


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


void imprimirVoos(Voo** voos, int numVoos) {
    for (int i = 0; i < numVoos; i++) {
        Voo* voo = voos[i];
        std::cout << voo->str << std::endl;
    }
}


void leVoosdeArquivo(std::ifstream& inputFile, Voo** voos, int numLinhas) {
    if (!inputFile.is_open()) {
        throw std::runtime_error("Erro: arquivo não está aberto para leitura");
    }
    
    std::string line;
    for (int i = 0; i < numLinhas; i++) {
        if (!std::getline(inputFile, line)) {
            std::cerr << "Erro: fim inesperado do arquivo na linha " << i + 1 << std::endl;
            throw std::runtime_error("Número insuficiente de linhas no arquivo");
        }
        try {
            voos[i] = new Voo(line);
        } catch (const std::exception& e) {
            std::cerr << "Erro ao processar voo da linha " << i + 1 << ": " << e.what() << std::endl;
            throw;
        }
    }
}


void leVoosdeEntrada(Voo** voos, int numLinhas) {
    std::string line;
    for (int i = 0; i < numLinhas; i++) {
        std::getline(std::cin, line);
        voos[i] = new Voo(line);
    }
}


