#include "OrdInd.hpp"
#include <cassert>
#include <iostream>

void testCarregaArquivo() {
    OrdInd ordInd;
    int result = ordInd.CarregaArquivo("input.xcsv");
    assert(result == 0);
    std::cout << "testCarregaArquivo passed." << std::endl;
}

void testNumAtributos() {
    OrdInd ordInd;
    ordInd.CarregaArquivo("input.xcsv");
    int numAtributos = ordInd.NumAtributos();
    assert(numAtributos == 3); // Supondo que o arquivo tenha 3 atributos
    std::cout << "testNumAtributos passed." << std::endl;
}

void testNomeAtributo() {
    OrdInd ordInd;
    ordInd.CarregaArquivo("input.xcsv");
    std::string nome;
    int result = ordInd.NomeAtributo(0, nome);
    assert(result == 0);
    assert(nome == "NomeAtributo1"); // Supondo que o primeiro atributo seja "NomeAtributo1"
    std::cout << "testNomeAtributo passed." << std::endl;
}

void testIDAtributo() {
    OrdInd ordInd;
    ordInd.CarregaArquivo("input.xcsv");
    int id = ordInd.IDAtributo("NomeAtributo1");
    assert(id == 0); // Supondo que "NomeAtributo1" seja o primeiro atributo
    std::cout << "testIDAtributo passed." << std::endl;
}

void testCriaIndice() {
    OrdInd ordInd;
    ordInd.CarregaArquivo("input.xcsv");
    int result = ordInd.CriaIndice(0);
    assert(result == 0);
    std::cout << "testCriaIndice passed." << std::endl;
}

void testOrdenaIndice() {
    OrdInd ordInd;
    ordInd.CarregaArquivo("input.xcsv");
    ordInd.CriaIndice(0);
    int result = ordInd.OrdenaIndice(0, "quick");
    assert(result == 0);
    std::cout << "testOrdenaIndice passed." << std::endl;
}

void testImprimeOrdenadoIndice() {
    OrdInd ordInd;
    ordInd.CarregaArquivo("input.xcsv");
    ordInd.CriaIndice(0);
    ordInd.OrdenaIndice(0, "quick");
    int result = ordInd.ImprimeOrdenadoIndice(0);
    assert(result == 0);
    std::cout << "testImprimeOrdenadoIndice passed." << std::endl;
}

int main() {
    testCarregaArquivo();
    testNumAtributos();
    testNomeAtributo();
    testIDAtributo();
    testCriaIndice();
    testOrdenaIndice();
    testImprimeOrdenadoIndice();
    std::cout << "All tests passed." << std::endl;
    return 0;
}