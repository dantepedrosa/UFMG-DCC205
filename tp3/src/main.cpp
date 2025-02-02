#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>

#include "../include/Voo.hpp"
#include "../include/Pilha.hpp"
#include "../include/ListaEncadeada.hpp"
#include "../include/Filtro.hpp"
#include "../include/Sort.hpp"



// Imprime a lista de voos filtrados
void imprimirVoos(Voo** voos, int numVoos) {
    for (int i = 0; i < numVoos; i++) {
        Voo* voo = voos[i];
        std::cout << voo->preco << std::endl;
    }
}

// Lê voos de um arquivo
void leVoosdeArquivo(std::ifstream& inputFile, Voo** voos, int numLinhas) {
    std::string line;

    for (int i = 0; i < numLinhas; i++) {
        std::getline(inputFile, line);
        voos[i] = new Voo(line);
    }
}

// Lê voos da entrada padrão
void leVoosdeEntrada(Voo** voos, int numLinhas) {
    std::string line;
    for (int i = 0; i < numLinhas; i++) {
        std::getline(std::cin, line);
        voos[i] = new Voo(line);
    }
}


int main(int argc, char const* argv[]) {
    // Leitura de dados
    // ---------------------------------------------------

    bool fileEnabled = false;
    std::string filePath;

    switch (argc) {
        case 1:
            fileEnabled = false;
            return 1;
        case 2:
            fileEnabled = true;
            filePath = argv[1];
            break;
        default:
            std::cerr << "Uso: " << argv[0] << " <caminho_para_arquivo> [-f]"
                      << std::endl;
            return 1;
    }

    std::string line;
    std::istringstream iss;
    int numLinhas;

    Voo** voos;

    if (fileEnabled) {
        std::ifstream inputFile(filePath);
        std::getline(inputFile, line);
        numLinhas = std::stoi(line);

        voos = new Voo*[numLinhas];
        leVoosdeArquivo(inputFile, voos, numLinhas);

        inputFile.close();
    } else {
        std::getline(std::cin, line);
        numLinhas = std::stoi(line);

        voos = new Voo*[numLinhas];
        leVoosdeEntrada(voos, numLinhas);
    }

    // Expressão de filtro
    std::string expression = "((org==ATL))";
    ListaEncadeada<std::string> tokens = tokenize(expression);
    Node* root = parseExpression(tokens);

    // Exibe a árvore de expressão
    //std::cout << "Árvore de Expressão:" << std::endl;
    //printTree(root);

    // Filtra os voos usando a árvore de expressão
    ListaEncadeada<Voo*> voosFiltrados = filtrarVoos(root, voos, numLinhas);

    // Separa os 3 menores voos
    Voo* menoresVoos[3];

    separarMenoresVoos(voosFiltrados, menoresVoos, 3, "pds");

    // Imprime os voos filtrados
    imprimirVoos(menoresVoos, 3);

    for (int i = 0; i < numLinhas; i++) delete voos[i];
    delete[] voos;

    // Função lambda para liberar recursivamente os nós da árvore de expressão
    std::function<void(Node*)> deleteTree = [&](Node* node) {
        if (!node)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    };
    deleteTree(root);

    return 0;
}
