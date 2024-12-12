#include "graph.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

Grafo::Grafo() : numVertices(0), numArestas(0) {}

Grafo::~Grafo() {}

void Grafo::InsereVertice() {
    adjList.push_back(list<int>());
    numVertices++;
}

void Grafo::InsereAresta(int v, int w) {
    adjList[v].push_back(w);
    adjList[w].push_back(v);
    numArestas++;
}

int Grafo::QuantidadeVertices() {
    return numVertices;
}

int Grafo::QuantidadeArestas() {
    return numArestas;
}

int Grafo::GrauMinimo() {
    int minGrau = adjList[0].size();
    for (const auto& lista : adjList) {
        if (lista.size() < minGrau) {
            minGrau = lista.size();
        }
    }
    return minGrau;
}

int Grafo::GrauMaximo() {
    int maxGrau = adjList[0].size();
    for (const auto& lista : adjList) {
        if (lista.size() > maxGrau) {
            maxGrau = lista.size();
        }
    }
    return maxGrau;
}

void Grafo::ImprimeVizinhos(int v) {
    for (const auto& vizinho : adjList[v]) {
        cout << vizinho << " ";
    }
    cout << endl;
}