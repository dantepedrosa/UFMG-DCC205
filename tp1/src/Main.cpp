#include "OrdInd.hpp"
#include <string>
#include <iostream>

int main(int argc, char ** argv){

    // Valida a entrada
    if (argc < 2) {
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
            // Testa com algoritmo
            ordInd.CriaIndice(j);
            ordInd.OrdenaIndice(j, algoritmos[i]);
            result = ordInd.ImprimeOrdenadoIndice(j);
        }
    }
    
    return 0;
}
