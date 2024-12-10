/**
 * @file OrdInd.hpp
 * @brief Declaração da classe OrdInd para manipulação de dados ordenados por índices.
 * 
 * Este arquivo contém a declaração da classe OrdInd, que permite carregar dados de um arquivo,
 * criar índices para atributos específicos, ordenar esses índices e imprimir os dados ordenados.
 * 
 * @date 2024
 * 
 * @author Dante Junqueira Pedrosa
 * @institution Universidade Federal de Minas Gerais (UFMG)
 * @course DCC205 - Estruturas de Dados
 */
#pragma once

#include <string>
#include "Sorts.hpp"


typedef ApontadorIndice* ApontadorIndicePtr;

class OrdInd
{
private:
    std::string** dados;        // Dados carregados (matriz de strings)
    int linhas;                 // Número de linhas
    int colunas;                // Número de colunas (atributos)
    std::string *atributos;     // Nomes dos atributos
    std::string *tipoAtributos; // Tipos de dados dos atributos
    ApontadorIndice*** indices;  // Índices ordenados por atributo
    

public:
    /**
     * @brief Construtor padrão da classe OrdInd.
     */
    OrdInd();

    /**
     * @brief Destrutor da classe OrdInd.
     */
    ~OrdInd();

    /**
     * @brief Carrega os dados de um arquivo.
     *
     * @param nomeentrada Nome do arquivo de entrada.
     * @return int Retorna 0 em caso de sucesso, ou um código de erro.
     */
    int CarregaArquivo(const std::string &nomeentrada);

    /**
     * @brief Retorna o número de atributos.
     *
     * @return int Número de atributos.
     */
    int NumAtributos() const;

    /**
     * @brief Obtém o nome de um atributo dado sua posição.
     *
     * @param pos Posição do atributo.
     * @param nome Referência para armazenar o nome do atributo.
     * @return int Retorna 0 em caso de sucesso, ou um código de erro.
     */
    int NomeAtributo(int pos, std::string &nome) const;

    /**
     * @brief Obtém o ID de um atributo dado seu nome.
     *
     * @param nome Nome do atributo.
     * @return int ID do atributo, ou -1 se não encontrado.
     */
    int IDAtributo(std::string nome);

    /**
     * @brief Cria um índice para um atributo específico.
     *
     * @param atribid ID do atributo.
     * @return int Retorna true em caso de sucesso, ou false em caso de falha.
     */
    int CriaIndice(int atribid);

    /**
     * @brief Ordena o índice de um atributo específico.
     *
     * @param atribid ID do atributo.
     * @return int Retorna 0 em caso de sucesso, ou um código de erro.
     */
    int OrdenaIndice(int atribid, std::string ordenacao);

    /**
     * @brief Imprime os dados ordenados pelo índice de um atributo específico.
     *
     * @param atribid ID do atributo.
     * @return int Retorna 0 em caso de sucesso, ou um código de erro.
     */
    int ImprimeOrdenadoIndice(int atribid) const;
};
