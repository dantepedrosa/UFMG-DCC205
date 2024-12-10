/**
 * @file TesteDesempenho.cpp
 * @brief Este arquivo contém a implementação de funções para testar o desempenho de algoritmos de ordenação.
 *
 * Ele carrega dados de um arquivo, cria um índice baseado em um atributo específico, ordena o índice usando um algoritmo de ordenação especificado,
 * e mede o tempo gasto em cada uma dessas operações.
 *
 * @date 2024
 *
 * @author Dante Junqueira Pedrosa
 * @institution Universidade Federal de Minas Gerais (UFMG)
 * @course DCC205 - Estruturas de Dados
 */

#include <string>
#include <iostream>
#include <chrono>
#include "OrdInd.hpp"

/**
 * @brief Testa o tempo de execução de diferentes etapas de ordenação de um índice.
 *
 * Esta função carrega dados de um arquivo, cria um índice baseado em um atributo específico, ordena o índice usando um algoritmo de ordenação especificado,
 * e mede o tempo gasto em cada uma dessas operações.
 *
 * @param atribName Nome do atributo pelo qual o índice será criado.
 * @param sortAlgorithm Nome do algoritmo de ordenação a ser utilizado (ex: "quick", "shell", "insertion").
 * @param inputFile Caminho para o arquivo de entrada contendo os dados.
 * @param outputFile Caminho para o arquivo de saída onde os dados ordenados serão armazenados.
 */
void TestaTempoOrdenacao(std::string &atribName, std::string &sortAlgorithm, std::string &inputFile, std::string &outputFile)
{

    OrdInd ordInd;
    ordInd.CarregaArquivo(inputFile);

    int atrbid = ordInd.IDAtributo(atribName);

    // Mede tempo gasto por CriaIndice
    auto start = std::chrono::high_resolution_clock::now();
    ordInd.CriaIndice(atrbid);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken by CriaIndice: " << duration.count() << " seconds" << std::endl;

    // Mede tempo gasto por OrdenaIndice
    start = std::chrono::high_resolution_clock::now();
    ordInd.OrdenaIndice(atrbid, sortAlgorithm);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken by OrdenaIndice (" << sortAlgorithm << "): " << duration.count() << " seconds" << std::endl;

    // Mede tempo gasto por ImprimeOrdenadoIndice
    start = std::chrono::high_resolution_clock::now();
    int result = ordInd.ImprimeOrdenadoIndice(atrbid);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken by ImprimeOrdenadoIndice: " << duration.count() << " seconds" << std::endl;
}

/**
 * @brief Função principal para testar o desempenho de algoritmos de ordenação.
 *
 * Esta função valida os argumentos de entrada, chama a função TestaTempoOrdenacao para medir o tempo de execução de diferentes etapas de ordenação,
 * e imprime os resultados.
 *
 * @param argc Número de argumentos de entrada.
 * @param argv Vetor de argumentos de entrada.
 * @return int Código de status da execução (0 para sucesso, 1 para erro).
 */
int Teste(int argc, char **argv)
{

    // Valida a entrada
    if (argc < 5)
    {
        std::cerr << "Uso: " << argv[0] << " <input_file> <sort>" << std::endl;
        return 1;
    }

    if (argc != 1)
    {
        std::string atribName = argv[1];
        std::string inputFile = argv[2];
        std::string sort = argv[3];
        std::string outputFile = argv[4];

        int result[3]; // TODO colocar resultado no vetor

        TestaTempoOrdenacao(atribName, sort, inputFile, outputFile, );

        return 0;
    }

    // Caso não tenha input, testar todos e gerar arquivos
    std::string algoritmos[3] = {"quick", "shell", "insertion"};

    return 0;
}