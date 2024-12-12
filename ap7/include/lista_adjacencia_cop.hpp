#ifndef LISTA_ADJACENCIA_HPP
#define LISTA_ADJACENCIA_HPP

#include <list>
#include <vector>

class ListaAdjacencia {
public:
    ListaAdjacencia();
    ~ListaAdjacencia();

    void adicionarVertice();
    void adicionarAresta(int v, int w);
    const std::list<int>& obterVizinhos(int v) const;
    int obterGrau(int v) const;
    int obterNumVertices() const;
    int obterNumArestas() const;

private:
    int numVertices;
    int numArestas;
    std::vector<std::list<int>> adjList;
};

#endif // LISTA_ADJACENCIA_HPP