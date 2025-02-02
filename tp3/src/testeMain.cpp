/**
 * @file testMain.cpp
 * @brief Arquivo de teste de processamento para o sistema de processamento e filtragem de voos
 * @author Dante Junqueira Pedrosa
 * @date 2025
 */

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <chrono>

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
 * @param arquivoQueries Arquivo de entrada
 * @param consultas Array de ponteiros para consultas a ser preenchido
 * @param numConsultas Número de consultas a serem lidas
 */
void leConsultasdeArquivo(std::ifstream& arquivoQueries, Consulta** consultas, int numConsultas);

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
 * @param arquivoDados Arquivo de entrada
 * @param voos Array de ponteiros para voos a ser preenchido
 * @param numLinhas Número de linhas (voos) a serem lidas
 */
void leVoosdeArquivo(std::ifstream& arquivoDados, Voo** voos, int numLinhas);

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

        if (argc < 2) {
            std::cerr << "Erro: número insuficiente de argumentos" << std::endl;
            return 1;
        }

        int numDados = std::stoi(argv[1]);

        // Define variaveis para captura de tempo 
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
        std::chrono::duration<double> tInit, tLeituraDados, tFinal;
        
        // Capture o tempo de início
        start = std::chrono::high_resolution_clock::now();

        std::string dadosPath = "./test/inputs/input_flights.txt";
        std::string queriesPath = "./test/inputs/input_queries.txt";
        std::string line;
        std::istringstream iss;
        int numConsultasTotal;
        
        Voo** voos;
        
        GerenciadorIndices indices;  // Moved declaration here

        // Leitura de dados
        // Trata diferente para caso seja entrada padrão ou arquivo
        // ---------------------------------------------------

        std::ifstream arquivoDados(dadosPath);
        if (!arquivoDados.is_open()) {
            std::cerr << "Erro: não foi possível abrir o arquivo " << dadosPath << std::endl;
            return 1;
        }

        // Captura tempo de inicialização
        end = std::chrono::high_resolution_clock::now();
        tInit = end - start;
        // Capture o tempo
        start = std::chrono::high_resolution_clock::now();

        voos = new Voo*[numDados];
        leVoosdeArquivo(arquivoDados, voos, numDados);

        // Criar e preencher os índices após carregar os voos
        for (int i = 0; i < numDados; i++) {
            indices.inserirVoo(voos[i], i);
        }

        // Lê expressões de consulta
        std::ifstream arquivoQueries(queriesPath);
        std::getline(arquivoQueries, line);
        numConsultasTotal = std::stoi(line);
        Consulta*** consultas = new Consulta**[numConsultasTotal];
        int numConsultas;
        for (int i = 0; i < numConsultasTotal; i++) {
            std::getline(arquivoQueries, line);
            numConsultas = std::stoi(line);
            consultas[i] = new Consulta*[numConsultas];
            leConsultasdeArquivo(arquivoQueries, consultas[i], numConsultas);
        }

        arquivoQueries.close();
        arquivoDados.close();

        // Captura tempo de leitura de dados
        end = std::chrono::high_resolution_clock::now();
        tLeituraDados = end - start;
        std::chrono::duration<double> tConsultaMedio[numConsultasTotal];

        // Processamento de consultas
        // ---------------------------------------------------
        for (int i = 0; i < numConsultasTotal; i++) {

            //std::cout << "Testando " << i+2 << " consultas em " << numDados << " voos." << std::endl;

            // Capture o tempo de início
            start = std::chrono::high_resolution_clock::now();

            for (int j = 0; j < numConsultas; j++) {
                
                

                // Cria a árvore de expressão e filtra os voos
                ArvoreDeExpressao arvore(consultas[i][j]->expression);
                ListaEncadeada<Voo*> voosFiltrados = arvore.filtrarVoos(voos, numDados);

                // Processar resultados
                int numResultados = std::min(consultas[i][j]->numResultados, voosFiltrados.GetTamanho());
                Voo* menoresVoos[numResultados];
                separarMenoresVoos(voosFiltrados, menoresVoos, numResultados, consultas[i][j]->trigrama);
                
                //imprimirVoos(menoresVoos, numResultados);
            }

            // Captura tempo de consulta com n consultas
            end = std::chrono::high_resolution_clock::now();
            tConsultaMedio[i] = (end - start)/numConsultas;

        }

        // Capture o tempo de início
        start = std::chrono::high_resolution_clock::now();

        // Liberação de memória
        // ---------------------------------------------------
        for (int i = 0; i < numDados; i++) delete voos[i];
        delete[] voos;

        for (int i = 0; i < numConsultasTotal; i++) {
            for (int j = 0; j < numConsultas; j++) {
                delete consultas[i][j];
            }
            delete[] consultas[i];
        }
        delete[] consultas;

        // Captura tempo final
        end = std::chrono::high_resolution_clock::now();
        tFinal = end - start;

        std::cout 
            << numDados << " " 
            << tInit.count() << " " 
            << tLeituraDados.count() << " " 
            << tConsultaMedio[0].count() << " "
            << tConsultaMedio[1].count() << " "
            << tConsultaMedio[2].count() << " "
            << tConsultaMedio[3].count() << " "
            << tFinal.count() << " "
            << std::endl;

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


void leConsultasdeArquivo(std::ifstream& arquivoDados, Consulta** consultas,
                          int numConsultas) {
    if (!arquivoDados.is_open()) {
        throw std::runtime_error("Erro: arquivo não está aberto para leitura");
    }
    
    std::string line;
    for (int i = 0; i < numConsultas; i++) {
        if (!std::getline(arquivoDados, line)) {
            std::cerr << "Erro: fim inesperado do arquivo na consulta " << i + 1 << std::endl;
            throw std::runtime_error("Número insuficiente de consultas no arquivo");
        }
        
        consultas[i] = new Consulta();
        consultas[i]->str = line;
        std::istringstream iss(line);
        
        if (!(iss >> consultas[i]->numResultados >> consultas[i]->trigrama >> consultas[i]->expression)) {
            std::cerr << "Erro: formato inválido na consulta " << i + 1 << std::endl;
            std::cerr << "Consulta " << consultas[i]->str << std::endl;
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


void leVoosdeArquivo(std::ifstream& arquivoDados, Voo** voos, int numLinhas) {
    if (!arquivoDados.is_open()) {
        throw std::runtime_error("Erro: arquivo não está aberto para leitura");
    }
    
    std::string line;
    for (int i = 0; i < numLinhas; i++) {
        if (!std::getline(arquivoDados, line)) {
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
