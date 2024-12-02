#ifndef ORDIND_H
#define ORDIND_H

#include "Matriz.h"
#include "Vetor.h"
#include "Sorts.h" 


class OrdInd {
private:
    Matriz *dados;
    Vetor *indicesNome;
    Vetor *indicesCPF;
    Vetor *indicesEndereco;

    Vetor *getIndice(int atribid);

public:
    OrdInd(int numRegistros, int numAtributos);
    ~OrdInd();

    // Métodos para acessar e modificar dados
    void setDado(int linha, int coluna, const char *valor);
    const char *getDado(int linha, int coluna) const;

    // Criação e ordenação de índices
    void criaIndice(int atribid);
    void ordenaIndiceQuickSort(int atribid);
    void ordenaIndiceBubbleSort(int atribid);
    void ordenaIndiceSelectionSort(int atribid);

    // Imprimir registros
    void imprimeOrdenadoIndice(int atribid) const;
};

#endif // ORDIND_H
