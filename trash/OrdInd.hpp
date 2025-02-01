/**
 * @file OrdInd.hpp
 * @brief Declaração e implementação da classe OrdInd para manipulação de dados
 * ordenados por índices.
 *
 * Este arquivo contém a declaração e implementação da classe OrdInd, que
 * permite carregar dados de um arquivo, criar índices para atributos
 * específicos, ordenar esses índices e imprimir os dados ordenados.
 *
 * @date 2024
 *
 * @author Dante Junqueira Pedrosa
 * @institution Universidade Federal de Minas Gerais (UFMG)
 * @course DCC205 - Estruturas de Dados
 */

#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Sort.hpp"

struct ApontadorIndice
{

    std::string chave; // Chave, para utilizar na ordenação das entradas
    int pos;           // Posição da respectiva entrada na lista original inalterada

    bool operator>(const ApontadorIndice &other) const
    {
        return chave > other.chave;
    }

    bool operator<(const ApontadorIndice &other) const
    {
        return chave < other.chave;
    }

    bool operator==(const ApontadorIndice &other) const
    {
        return chave == other.chave;
    }

    bool operator>=(const ApontadorIndice &other) const
    {
        return chave >= other.chave;
    }

    bool operator<=(const ApontadorIndice &other) const
    {
        return chave <= other.chave;
    }
};
typedef ApontadorIndice *ApontadorIndicePtr;

class OrdInd {
   private:
    std::string **dados;         // Dados carregados (matriz de strings)
    int linhas;                  // Número de linhas
    int colunas;                 // Número de colunas (atributos)
    std::string *atributos;      // Nomes dos atributos
    std::string *tipoAtributos;  // Tipos de dados dos atributos
    ApontadorIndice ***indices;  // Índices ordenados por atributo

   public:
    /**
     * @brief Construtor padrão da classe OrdInd.
     */
    OrdInd()
        : dados(nullptr),
          linhas(0),
          colunas(0),
          atributos(nullptr),
          tipoAtributos(nullptr),
          indices(nullptr) {
        // Inicializa todos os membros como 0 ou nullptr
    }

    /**
     * @brief Destrutor da classe OrdInd.
     */
    ~OrdInd() {
        // Destroi todos os apontadores presentes em dados
        if (dados) {
            for (int i = 0; i < linhas; ++i) {
                delete[] dados[i];
            }
            delete[] dados;
        }

        delete[] atributos;
        delete[] tipoAtributos;

        // Destrói todos os apontadores presentes em índices
        if (indices) {
            for (int i = 0; i < colunas; ++i) {
                delete[] indices[i];
            }
            delete[] indices;
        }
    }

    /**
     * @brief Carrega os dados de um arquivo.
     *
     * @param nomeentrada Nome do arquivo de entrada.
     * @return int Retorna 0 em caso de sucesso, ou um código de erro.
     */
    int CarregaArquivo(const std::string &nomeentrada) {
        // Testar se arquivo foi aberto
        std::ifstream Arquivo(nomeentrada);
        if (!Arquivo.is_open()) {
            std::cerr << "Error opening file: " << nomeentrada << std::endl;
            return -1;
        }

        // Inicialização de parâmetros usados múltiplas vezes
        std::string strLinha;
        std::string substr;

        // Ler quantidade de colunas
        getline(Arquivo, strLinha);
        this->colunas = stoi(strLinha);

        // Inicializa arrays de atributos e tipoAtributos
        this->atributos = new std::string[this->colunas];
        this->tipoAtributos = new std::string[this->colunas];

        // Inicializa array de indices
        this->indices = new ApontadorIndice **[this->colunas];
        for (int i = 0; i < this->colunas; ++i) {
            this->indices[i] = new ApontadorIndice *[this->linhas];
            for (int j = 0; j < this->linhas; ++j) {
                this->indices[i][j] = nullptr;
            }
        }

        // Ler nomes de colunas e tipo de dados
        for (int i = 0; i < this->colunas; i++) {
            getline(Arquivo, strLinha);
            std::stringstream ss(strLinha);
            getline(ss, substr, ',');
            this->atributos[i] = substr;
            getline(ss, substr, ',');
            this->tipoAtributos[i] = substr;
        }

        // Ler quantidade de entradas de dados
        getline(Arquivo, strLinha);
        this->linhas = stoi(strLinha);

        // Inicializa matriz de dados
        this->dados = new std::string *[this->linhas];
        for (int i = 0; i < this->linhas; ++i) {
            this->dados[i] = new std::string[this->colunas];
        }

        // Ler entradas de dados e armazenar em dados
        for (int i = 0; i < this->linhas; i++) {
            getline(Arquivo, strLinha);
            std::stringstream ss(strLinha);

            for (int j = 0; j < this->colunas; j++) {
                getline(ss, substr, ',');
                dados[i][j] = substr;
            }
        }
        return 0;
    }

    /**
     * @brief Retorna o número de atributos.
     *
     * @return int Número de atributos.
     */
    int NumAtributos() const {
        return colunas;  // Retorna o número de colunas
    }

    /**
     * @brief Obtém o nome de um atributo dado sua posição.
     *
     * @param pos Posição do atributo.
     * @param nome Referência para armazenar o nome do atributo.
     * @return int Retorna 0 em caso de sucesso, ou um código de erro.
     */
    int NomeAtributo(int pos, std::string &nome) const {
        // Validação de entrada
        if (pos < 0 || pos >= colunas) {
            std::cerr << "ID " << pos << " não representa nenhum atributo"
                      << std::endl;
            return -1;
        }

        // Salva o nome do atributo no endereço de nome
        nome = atributos[pos];

        return 0;
    }

    /**
     * @brief Obtém o ID de um atributo dado seu nome.
     *
     * @param nome Nome do atributo.
     * @return int ID do atributo, ou -1 se não encontrado.
     */
    int IDAtributo(std::string nome) {
        for (int i = 0; i < colunas; i++) {
            if (!atributos[i].compare(nome)) return i;  // Caso tenha encontrado
        }

        return -1;  // Caso não encontrado
    }

    /**
     * @brief Cria um índice para um atributo específico.
     *
     * @param atribid ID do atributo.
     * @return int Retorna true em caso de sucesso, ou false em caso de falha.
     */
    int CriaIndice(int atribid) {
        // Validação da entrada
        if (atribid < 0 || atribid >= colunas) {
            std::cerr << "atribid " << atribid << " fora dos limites"
                      << std::endl;
            return -1;
        }

        indices[atribid] = new ApontadorIndice *[linhas];

        // Para cada item de indice, salva o dado e o atributo
        for (int i = 0; i < linhas; ++i) {
            indices[atribid][i] = new ApontadorIndice;
            indices[atribid][i]->chave = dados[i][atribid];
            indices[atribid][i]->pos = i;
        }

        return 0;
    }

    /**
     * @brief Ordena o índice de um atributo específico.
     *
     * @param atribid ID do atributo.
     * @param ordenacao Algoritmo de ordenação a ser utilizado.
     * @return int Retorna 0 em caso de sucesso, ou um código de erro.
     */
    int OrdenaIndice(int atribid, std::string ordenacao) {
        // Validação de entrada
        if (atribid < 0 || atribid >= colunas) {
            std::cerr << "atribid " << atribid << " fora dos limites"
                      << std::endl;
            return -1;
        }

        quicksort(indices[atribid], linhas);

        return 0;
    }
    /**
     * @brief Imprime os dados ordenados pelo índice de um atributo
     * específico.
     *
     * @param atribid ID do atributo.
     * @return int Retorna 0 em caso de sucesso, ou um código de erro.
     */
    int ImprimeOrdenadoIndice(int atribid) const {
        // Validação de entrada
        if (atribid < 0 || atribid >= colunas) {
            std::cerr << "atribid " << atribid << " fora dos limites"
                      << std::endl;
            return -1;
        }

        std::cout << colunas << std::endl;  // Quantidade de colunas

        for (int i = 0; i < colunas; i++) {
            std::cout << atributos[i] << "," << tipoAtributos[i]
                      << std::endl;  // Nome e tipo de atributo
        }

        std::cout << linhas << std::endl;  // Quantidade de linhas

        // Matriz de dados
        for (int i = 0; i < linhas; ++i) {
            int pos = indices[atribid][i]->pos;
            for (int j = 0; j < colunas; ++j) {
                std::cout << dados[pos][j];
                if (j < colunas - 1) {
                    std::cout << ",";
                }
            }
            std::cout << std::endl;
        }

        return 0;
    }
};
