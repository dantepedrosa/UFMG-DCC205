#include <string>
#include <iostream>
#include <chrono>
#include "OrdInd.hpp"

void TestaTempoOrdenacao(std::string& atribName, std::string& sortAlgorithm, std::string& inputFile, std::string& outputFile){

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

int Teste(int argc, char ** argv){

    // Valida a entrada
    if (argc < 5) {
        std::cerr << "Uso: " << argv[0] << " <input_file> <sort>" << std::endl;
        return 1;
    }

    

    if(argc != 1)
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