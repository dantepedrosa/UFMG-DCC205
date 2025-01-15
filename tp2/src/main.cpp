#include <iostream>
#include <string>
#include "DataHora.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.csv>" << std::endl;
        return 1;
    }

    std::string nomeArquivo = argv[1];
    // ... código para processar o arquivo ...

    return 0;
}
