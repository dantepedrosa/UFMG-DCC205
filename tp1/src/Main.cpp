/**
 * @file Main.cpp
 * @brief Programa principal para execução de algoritmos de ordenação em índices.
 *
 * Este arquivo contém a função principal que valida a entrada do usuário, carrega
 * um arquivo de dados e executa três algoritmos de ordenação (quick sort, shell sort,
 * e insertion sort) em três diferentes atributos. O resultado da ordenação é impresso
 * para cada combinação de algoritmo e atributo.
 *
 * Uso: ./tp1.out <input_file>
 *
 * @param argc Número de argumentos passados pela linha de comando.
 * @param argv Vetor de strings contendo os argumentos passados pela linha de comando.
 * @return Código de status da execução do programa.
 * 
 * @author Dante Junqueira Pedrosa
 * @institution Universidade Federal de Minas Gerais (UFMG)
 * @course DCC205 - Estruturas de Dados
 */

#include "OrdInd.hpp"
#include <string>
#include <iostream>

int main(int argc, char **argv)
{

    // Valida a entrada
    if (argc < 2)
    {
        std::cerr << "Uso: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];

    OrdInd ordInd;
    int result;
    ordInd.CarregaArquivo(inputFile);

    // Nomeação dos 3 algoritmos
    std::string algoritmos[3] = {"quick", "shell", "insertion"};

    // Cicla por todos os algoritmos
    for (int i = 0; i < 3; i++)
    {
        // Cicla por todos os atributos
        for (int j = 0; j < 3; j++)
        {
            // Executa com o algoritmo
            ordInd.CriaIndice(j);
            ordInd.OrdenaIndice(j, algoritmos[i]);
            result = ordInd.ImprimeOrdenadoIndice(j);
        }
    }

    return 0;
}
