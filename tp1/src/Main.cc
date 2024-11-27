/*

#include "Test.h"

int main(int argc, char* argv[]) {
    Test* pTest = new Test();
    pTest->Print();
    return 0;
}
*/

#include "OrdInd.h"
#include <iostream>

int main() {
    int numRegistros = 5, numAtributos = 3;

    OrdInd organizador(numRegistros, numAtributos);

    if (!organizador.carregaArquivo("entrada.xcsv")) {
        std::cerr << "Erro ao carregar o arquivo." << std::endl;
        return 1;
    }

    organizador.criaIndice(0); // Nome
    organizador.ordenaIndice(0);
    organizador.imprimeOrdenadoIndice(0);

    organizador.criaIndice(1); // CPF
    organizador.ordenaIndice(1);
    organizador.imprimeOrdenadoIndice(1);

    organizador.criaIndice(2); // Endereço
    organizador.ordenaIndice(2);
    organizador.imprimeOrdenadoIndice(2);

    return 0;
}
