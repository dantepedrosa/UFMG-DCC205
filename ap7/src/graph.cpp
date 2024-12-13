#include "graph.hpp"
#include <iostream>

Grafo::Grafo() {}

Grafo::~Grafo() {}

void Grafo::InsereVertice() {
    vertices.adicionarVertice();
}

void Grafo::InsereAresta(int v, int w) {
    vertices.adicionarAresta(v, w);
}

int Grafo::QuantidadeVertices() {
    return vertices.obterNumVertices();
}

int Grafo::QuantidadeArestas() {
    return vertices.obterNumArestas();
}

int Grafo::GrauMinimo() {
    int minGrau = vertices.obterGrau(0);
    for (int i = 1; i < vertices.obterNumVertices(); i++) {
        int grau = vertices.obterGrau(i);
        if (grau < minGrau) {
            minGrau = grau;
        }
    }
    return minGrau;
}

int Grafo::GrauMaximo() {
    int maxGrau = vertices.obterGrau(0);
    for (int i = 1; i < vertices.obterNumVertices(); i++) {
        int grau = vertices.obterGrau(i);
        if (grau > maxGrau) {
            maxGrau = grau;
        }
    }
    return maxGrau;
}

void Grafo::ImprimeVizinhos(int v) {
    ListaEncadeada<int>* vizinhos = vertices.obterVizinhos(v);
    for (int i = 0; i < vizinhos->Tamanho(); i++) {
        std::cout << vizinhos->GetItem(i) << " ";
    }
    std::cout << std::endl;
}
