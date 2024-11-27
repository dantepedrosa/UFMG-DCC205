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

// Declaração das funções externas
void quickSort(std::vector<int> &indices, OrdInd &ordind, int atributo);
void bubbleSort(std::vector<int> &indices, OrdInd &ordind, int atributo);
void selectionSort(std::vector<int> &indices, OrdInd &ordind, int atributo);

int main() {
    int numRegistros = 5;
    int numAtributos = 3;

    // Instancia o objeto de dados
    OrdInd organizador(numRegistros, numAtributos);

    if (!organizador.carregaArquivo("entrada.xcsv")) {
        std::cerr << "Erro ao carregar o arquivo." << std::endl;
        return 1;
    }

    // Ordena usando QuickSort
    quickSort(organizador.getIndicesNome(), organizador, 0);
    std::cout << "Ordenado por Nome:\n";
    for (int idx : organizador.getIndicesNome()) {
        std::cout << organizador.getDado(idx, 0) << "\n";
    }

    // Ordena usando BubbleSort
    bubbleSort(organizador.getIndicesCPF(), organizador, 1);
    std::cout << "Ordenado por CPF:\n";
    for (int idx : organizador.getIndicesCPF()) {
        std::cout << organizador.getDado(idx, 1) << "\n";
    }

    // Ordena usando SelectionSort
    selectionSort(organizador.getIndicesEndereco(), organizador, 2);
    std::cout << "Ordenado por Endereço:\n";
    for (int idx : organizador.getIndicesEndereco()) {
        std::cout << organizador.getDado(idx, 2) << "\n";
    }

    return 0;
}
