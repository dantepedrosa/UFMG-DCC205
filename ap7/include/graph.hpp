#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include "ListaEncadeada.hpp"

class Grafo {
private:
    ListaEncadeada<int>* vertices;
    int quantidadeVertices;
    int quantidadeArestas;

public:
    Grafo() : vertices(nullptr), quantidadeVertices(0), quantidadeArestas(0) {}

    ~Grafo() {
        delete[] vertices;
    }

    void InsereVertice(int quantidade) {
        if (vertices != nullptr) {
            delete[] vertices;
        }
        quantidadeVertices = quantidade;
        vertices = new ListaEncadeada<int>[quantidade];
    }

    void InsereAresta(int v, int w) {
        if (!vertices[v].Contem(w)) {
            vertices[v].InsereFinal(w);
            vertices[w].InsereFinal(v);
            quantidadeArestas++;
        }
    }

    int QuantidadeVertices() const {
        return quantidadeVertices;
    }

    int QuantidadeArestas() const {
        return quantidadeArestas;
    }

    int GrauMinimo() const {
        int grauMin = vertices[0].Tamanho();
        for (int i = 1; i < quantidadeVertices; ++i) {
            int grau = vertices[i].Tamanho();
            if (grau < grauMin) {
                grauMin = grau;
            }
        }
        return grauMin;
    }

    int GrauMaximo() const {
        int grauMax = vertices[0].Tamanho();
        for (int i = 1; i < quantidadeVertices; ++i) {
            int grau = vertices[i].Tamanho();
            if (grau > grauMax) {
                grauMax = grau;
            }
        }
        return grauMax;
    }

    bool EhCompleto() const {
        for (int i = 0; i < quantidadeVertices; ++i) {
            if (vertices[i].Tamanho() != quantidadeVertices - 1) {
                return false;
            }
        }
        return true;
    }

    void ImprimeVizinhos() const {
        for (int i = 0; i < quantidadeVertices; ++i) {
            std::cout << i << ":";
            vertices[i].Imprime();
        }
    }
};

#endif
