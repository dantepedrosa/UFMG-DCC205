#include "lista_adjacencia.hpp"

ListaAdjacencia::ListaAdjacencia() : numVertices(0), numArestas(0) {}

ListaAdjacencia::~ListaAdjacencia() {}

void ListaAdjacencia::adicionarVertice() {
    adjList.push_back(std::list<int>());
    numVertices++;
}

void ListaAdjacencia::adicionarAresta(int v, int w) {
    adjList[v].push_back(w);
    adjList[w].push_back(v);
    numArestas++;
}

const std::list<int>& ListaAdjacencia::obterVizinhos(int v) const {
    return adjList[v];
}

int ListaAdjacencia::obterGrau(int v) const {
    return adjList[v].size();
}

int ListaAdjacencia::obterNumVertices() const {
    return numVertices;
}

int ListaAdjacencia::obterNumArestas() const {
    return numArestas;
}