#include "ListaAdjacencia.hpp"

// Construtor
ListaAdjacencia::ListaAdjacencia() : numVertices(0), numArestas(0) {}

// Destrutor
ListaAdjacencia::~ListaAdjacencia() {}

// Adicionar um vértice
void ListaAdjacencia::adicionarVertice() {
    ListaEncadeada<int> novaLista;
    adjList.InsereFinal(novaLista);
    numVertices++;
}

// Adicionar uma aresta entre os vértices v e w
void ListaAdjacencia::adicionarAresta(int v, int w) {
    adjList.GetItem(v).InsereFinal(w);
    adjList.GetItem(w).InsereFinal(v);
    numArestas++;
}

// Obter os vizinhos do vértice v
ListaEncadeada<int>& ListaAdjacencia::obterVizinhos(int v) {
    return adjList.GetItem(v);
}

// Obter o grau do vértice v
int ListaAdjacencia::obterGrau(int v) {
    return adjList.GetItem(v).Tamanho();
}

// Obter o número de vértices
int ListaAdjacencia::obterNumVertices()  {
    return numVertices;
}

// Obter o número de arestas
int ListaAdjacencia::obterNumArestas() {
    return numArestas;
}
