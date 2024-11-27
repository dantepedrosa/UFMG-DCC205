#include "Test.h"

int main(int argc, char* argv[]) {
    Test* pTest = new Test();
    pTest->Print();
    return 0;
}

/* TODO

#include "OrdInd.h"

int main() {
    int numRegistros = 5;  // Número de registros na base
    int numAtributos = 3;  // Nome, CPF, Endereço

    // Cria o objeto de ordenação
    OrdInd organizador(numRegistros, numAtributos);

    // Carrega os dados
    if (!organizador.carregaArquivo("entrada.xcsv")) {
        std::cerr << "Erro ao carregar o arquivo." << std::endl;
        return 1;
    }

    // Ordena e imprime as diferentes chaves
    organizador.ordenaPorNome();
    organizador.imprimePorNome();

    organizador.ordenaPorCPF();
    organizador.imprimePorCPF();

    organizador.ordenaPorEndereco();
    organizador.imprimePorEndereco();

    return 0;
}

*/