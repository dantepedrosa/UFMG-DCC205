#include "graph.hpp"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <operação>" << endl;
        return 1;
    }

    string operacao = argv[1];
    Grafo grafo;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        grafo.InsereVertice();
    }

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            int vizinho;
            cin >> vizinho;
            grafo.InsereAresta(i, vizinho);
        }
    }

    if (operacao == "-d") {
        cout << grafo.QuantidadeVertices() << endl;
        cout << grafo.QuantidadeArestas() << endl;
        cout << grafo.GrauMinimo() << endl;
        cout << grafo.GrauMaximo() << endl;
    } else if (operacao == "-n") {
        for (int i = 0; i < grafo.QuantidadeVertices(); i++) {
            grafo.ImprimeVizinhos(i);
        }
    } else if (operacao == "-k") {
        cout << (grafo.EhCompleto() ? 1 : 0) << endl;
    } else {
        cerr << "Operação desconhecida: " << operacao << endl;
        return 1;
    }

    return 0;
}