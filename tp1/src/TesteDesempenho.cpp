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
void TestaTempoOrdenacao(int atrbid, std::string &sortAlgorithm, std::string &inputFile, std::chrono::duration<double>* result)
{

    OrdInd ordInd;
    if (ordInd.CarregaArquivo(inputFile) != 0) {
        std::cerr << "Error loading file: " << inputFile << std::endl;
        return;
    }
    //int atrbid = ordInd.IDAtributo(atribName);

    // Mede tempo gasto por CriaIndice
    auto start = std::chrono::high_resolution_clock::now();
    ordInd.CriaIndice(atrbid);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    result[0] = duration;
    //std::cout << "Time taken by CriaIndice: " << duration.count() << " seconds" << std::endl;

    // Mede tempo gasto por OrdenaIndice
    start = std::chrono::high_resolution_clock::now();
    ordInd.OrdenaIndice(atrbid, sortAlgorithm);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    result[1] = duration;
    //std::cout << "Time taken by OrdenaIndice (" << sortAlgorithm << "): " << duration.count() << " seconds" << std::endl;


    // Mede tempo gasto por ImprimeOrdenadoIndice
    start = std::chrono::high_resolution_clock::now();
    ordInd.ImprimeOrdenadoIndice(atrbid);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    result[2] = duration;
    //std::cout << "Time taken by ImprimeOrdenadoIndice: " << duration.count() << " seconds" << std::endl;

   
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

         // TODO colocar resultado no vetor

        //TestaTempoOrdenacao(atribName, sort, inputFile, outputFile, );

        return 0;
    }
    


    // Caso não tenha input, testar todos e gerar arquivos
    std::string algoritmos[3] = {"quick", "shell", "insertion"};
    std::string atributos[3] = {"name", "id", "address"};

    std::string inputFile;
    std::chrono::duration<double>  result[3];

    for(int i = 500; i <= 5000; i+= 500){
        inputFile = "cad/cad.r" + std::to_string(i) + ".p1000.xcsv";
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {

                TestaTempoOrdenacao(j, algoritmos[k], inputFile, result);
                std::cout <<"linhas "<< i << ",algoritmo " << algoritmos[k] << ",atributo " << j << ",resultado " << result[0].count() << "," << result[1].count() << std::endl;
            }
        }
    }
    

    return 0;
}