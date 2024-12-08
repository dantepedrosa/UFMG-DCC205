#include <cassert>
#include <iostream>
#include "OrdInd.hpp"

void testCarregaArquivo()
{
    OrdInd ordInd;
    int result = ordInd.CarregaArquivo("cad/input.xcsv");
    assert(result == 0);
    std::cout << "testCarregaArquivo passed." << std::endl;
}

void testNumAtributos()
{
    OrdInd ordInd;
    ordInd.CarregaArquivo("cad/input.xcsv");
    int numAtributos = ordInd.NumAtributos();
    assert(numAtributos == 4); // Supondo que o arquivo tenha 3 atributos
    std::cout << "testNumAtributos passed." << std::endl;
}

void testNomeAtributo()
{
    OrdInd ordInd;
    ordInd.CarregaArquivo("cad/input.xcsv");
    std::string nome;
    int result = ordInd.NomeAtributo(0, nome);
    assert(result == 0);
    assert(nome == "name"); // Supondo que o primeiro atributo seja "NomeAtributo1"
    std::cout << "testNomeAtributo passed." << std::endl;
}

void testIDAtributo()
{
    OrdInd ordInd;
    ordInd.CarregaArquivo("cad/input.xcsv");
    int id = ordInd.IDAtributo("name");
    assert(id == 0); // Supondo que "NomeAtributo1" seja o primeiro atributo
    std::cout << "testIDAtributo passed." << std::endl;
}

void testCriaIndice()
{
    OrdInd ordInd;
    ordInd.CarregaArquivo("cad/input.xcsv");
    int result = ordInd.CriaIndice(0);
    assert(result == 0);
    std::cout << "testCriaIndice passed." << std::endl;
}

void testOrdenaIndice()
{
    OrdInd ordInd;
    ordInd.CarregaArquivo("cad/input.xcsv");
    ordInd.CriaIndice(0);
    int result = ordInd.OrdenaIndice(0, "quick");
    assert(result == 0);
    std::cout << "testOrdenaIndice passed." << std::endl;
}

void testImprimeOrdenadoIndiceQuick()
{
    OrdInd ordInd;
    ordInd.CarregaArquivo("cad/input.xcsv");
    ordInd.CriaIndice(0);
    ordInd.OrdenaIndice(0, "quick");
    int result = ordInd.ImprimeOrdenadoIndice(0);
    assert(result == 0);
    std::cout << "testImprimeOrdenadoIndice with quick passed." << std::endl;
}

void testImprimeOrdenadoIndiceShell()
{
    OrdInd ordInd;
    ordInd.CarregaArquivo("cad/input.xcsv");
    ordInd.CriaIndice(0);
    ordInd.OrdenaIndice(0, "shell");
    int result = ordInd.ImprimeOrdenadoIndice(0);
    assert(result == 0);
    std::cout << "testImprimeOrdenadoIndice with shell passed." << std::endl;
}

void testImprimeOrdenadoIndice()
{
    OrdInd ordInd;
    int result;
    ordInd.CarregaArquivo("cad/input.xcsv");
    // Testa com quick sort
    ordInd.CriaIndice(0);
    ordInd.OrdenaIndice(0, "quick");
    result = ordInd.ImprimeOrdenadoIndice(0);
    assert(result == 0);
    std::cout << std::endl;
    // Testa com shell sort
    ordInd.CriaIndice(1);
    ordInd.OrdenaIndice(1, "shell");
    result = ordInd.ImprimeOrdenadoIndice(1);
    assert(result == 0);
    std::cout << std::endl;
    // Testa com insertion sort
    ordInd.CriaIndice(2);
    ordInd.OrdenaIndice(2, "insertion");
    result = ordInd.ImprimeOrdenadoIndice(2);
    assert(result == 0);
    std::cout << std::endl;

    std::cout << "testImprimeOrdenadoIndice passed." << std::endl;
}

void testImprimeOrdenadoIndiceTodos()
{
    OrdInd ordInd;
    int result;
    ordInd.CarregaArquivo("cad/input.xcsv");

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
            assert(result == 0);
        }
    }

    std::cout << "testImprimeOrdenadoIndice TODOS passed." << std::endl;
}

int main()
{
    // testCarregaArquivo();
    // testNumAtributos();
    // testNomeAtributo();
    // testIDAtributo();
    // testCriaIndice();
    //testOrdenaIndice();
    //testImprimeOrdenadoIndice();
    testImprimeOrdenadoIndiceTodos();
    std::cout << "All tests passed." << std::endl;
    return 0;
}