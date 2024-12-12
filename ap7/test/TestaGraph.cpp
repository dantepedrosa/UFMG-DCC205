#include "../include/graph.hpp"
#include <iostream>
#include <cassert>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[92m"

void testQuantidadeVertices() {
    Grafo grafo;
    grafo.InsereVertice();
    grafo.InsereVertice();
    assert(grafo.QuantidadeVertices() == 2);
    std::cout << "Teste QuantidadeVertices passou!" << std::endl;
}

void testQuantidadeArestas() {
    Grafo grafo;
    grafo.InsereVertice();
    grafo.InsereVertice();
    grafo.InsereAresta(0, 1);
    assert(grafo.QuantidadeArestas() == 1);
    std::cout << "Teste QuantidadeArestas passou!" << std::endl;
}

void testGrauMinimoMaximo() {
    Grafo grafo;
    grafo.InsereVertice();
    grafo.InsereVertice();
    grafo.InsereVertice();
    grafo.InsereAresta(0, 1);
    grafo.InsereAresta(1, 2);
    assert(grafo.GrauMinimo() == 1);
    assert(grafo.GrauMaximo() == 2);
    std::cout << "Teste GrauMinimoMaximo passou!" << std::endl;
}

void testImprimeVizinhos() {
    Grafo grafo;
    grafo.InsereVertice();
    grafo.InsereVertice();
    grafo.InsereAresta(0, 1);
    std::cout << "Vizinhos do vértice 0: ";
    grafo.ImprimeVizinhos(0);
    std::cout << "Vizinhos do vértice 1: ";
    grafo.ImprimeVizinhos(1);
    std::cout << "Teste ImprimeVizinhos passou!" << std::endl;
}

int main() {
    testQuantidadeVertices();
    testQuantidadeArestas();
    testGrauMinimoMaximo();
    testImprimeVizinhos();
    std::cout << GREEN << "Todos os testes " << "passaram" << "!" << RESET << std::endl;
    return 0;
}