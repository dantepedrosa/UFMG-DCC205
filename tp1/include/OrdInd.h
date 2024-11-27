#ifndef ORDIND_H
#define ORDIND_H

#include "Matriz.h"
#include "Vetor.h"

class OrdInd {
private:
    Matriz *dados;
    Vetor *indicesNome;
    Vetor *indicesCPF;
    Vetor *indicesEndereco;

    void quickSort(Vetor &indice, int low, int high, int atributo);
    int partition(Vetor &indice, int low, int high, int atributo);

public:
    OrdInd(int numRegistros, int numAtributos);
    ~OrdInd();

    bool carregaArquivo(const char *nomeEntrada);
    void criaIndice(int atribid);
    void ordenaIndice(int atribid);
    void imprimeOrdenadoIndice(int atribid);
    const char *getDado(int linha, int coluna) const;
    void setDado(int linha, int coluna, const char *valor);
};

#endif // ORDIND_H
