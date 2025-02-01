#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "Voo.hpp"


void leVoosdeArquivo(const std::string& filePath, Voo** voos, int numLinhas) {
    std::ifstream inputFile(filePath);

    std::string line;
    std::istringstream iss;

    for(int i = 0; i < numLinhas; i++){
        std::getline(inputFile, line);
        voos[i] = new Voo(line);
    }

    inputFile.close();
}

void leVoosdeEntrada(Voo** voos, int numLinhas) {
    std::string line;
    std::istringstream iss;

    for(int i = 0; i < numLinhas; i++){
        std::getline(std::cin, line);
        voos[i] = new Voo(line);
    }
}

int main(int argc, char const* argv[]) {
    
    // Leitura de dados
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
            std::cerr << "Uso: " << argv[0] << " <caminho_para_arquivo> [-f]" << std::endl;
            return 1;
    }

    std::string line;
    std::istringstream iss;
    int numLinhas;

    if(fileEnabled){
        std::ifstream inputFile(filePath);

        // Conseguir numero de linhas
        std::getline(inputFile, line);
        numLinhas = std::stoi(line);
        inputFile.close();
    } else {
        std::getline(std::cin, line);
        numLinhas = std::stoi(line);
    }

    Voo* voos[numLinhas];

    if(fileEnabled){
        leVoosdeArquivo(filePath, voos, numLinhas);
    } else {
        leVoosdeEntrada(voos, numLinhas);
    }

    // 
    // ---------------------------------------------------



    // Liberação de memória
    for (int i = 0; i < numLinhas; i++) {
        delete voos[i];
    }
    delete[] voos;

    return 0;
}
