#include "graph.hpp"
#include <iostream>

int main(int argc, char** argv) {
    Grafo grafo;
    int quantidadeVertices;
    std::cin >> quantidadeVertices;
    grafo.InsereVertice(quantidadeVertices);
    for (int i = 0; i < quantidadeVertices; i++) {
        int quantidadeVizinhos;
        std::cin >> quantidadeVizinhos;
        for (int j = 0; j < quantidadeVizinhos; j++) {
            int vizinho;
            std::cin >> vizinho;
            grafo.InsereAresta(i, vizinho);
        }
    }

    if (argc > 1) {
        std::string comando = argv[1];
        if (comando == "-d") {
            std::cout << grafo.QuantidadeVertices() << std::endl;
            std::cout << grafo.QuantidadeArestas() << std::endl;
            std::cout << grafo.GrauMinimo() << std::endl;
            std::cout << grafo.GrauMaximo() << std::endl;
        } else if (comando == "-n") {
            grafo.ImprimeVizinhos();
        } else if (comando == "-k") {
            std::cout << (grafo.EhCompleto() ? 1 : 0) << std::endl;
        }
    }

    return 0;
}
