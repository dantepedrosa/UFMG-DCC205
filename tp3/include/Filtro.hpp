#include <string>

#include "../include/Voo.hpp"
#include "../include/Pilha.hpp"
#include "../include/ListaEncadeada.hpp"

// Nó da árvore de expressão (parse tree)
struct Node {
    std::string value;
    Node* left;
    Node* right;

    Node(std::string val) : value(val), left(nullptr), right(nullptr) {}
};

// Função que converte a expressão em tokens
ListaEncadeada<std::string> tokenize(const std::string& expr) {
    ListaEncadeada<std::string> tokens;
    std::string temp;
    for (std::size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (std::isspace(c))
            continue;

        if (c == '(' || c == ')') {
            tokens.InsereFinal(std::string(1, c));
        } else if (c == '&' && i + 1 < expr.size() && expr[i + 1] == '&') {
            tokens.InsereFinal("&&");
            i++;
        } else if (c == '|' && i + 1 < expr.size() && expr[i + 1] == '|') {
            tokens.InsereFinal("||");
            i++;
        } else if (c == '=' && i + 1 < expr.size() && expr[i + 1] == '=') {
            tokens.InsereFinal("==");
            i++;
        } else if (c == '<' && i + 1 < expr.size() && expr[i + 1] == '=') {
            tokens.InsereFinal("<=");
            i++;
        } else if (c == '>' && i + 1 < expr.size() && expr[i + 1] == '=') {
            tokens.InsereFinal(">=");
            i++;
        } else if (c == '<') {
            tokens.InsereFinal("<");
        } else if (c == '>') {
            tokens.InsereFinal(">");
        } else if (c == '!') {
            tokens.InsereFinal("!");
        } else {
            temp += c;
            // Se o próximo caractere não for alfanumérico ou for final da string, empurra o token
            if (i + 1 == expr.size() || !std::isalnum(expr[i + 1])) {
                tokens.InsereFinal(temp);
                temp = "";
            }
        }
    }
    return tokens;
}

// Função que monta a árvore de expressão a partir dos tokens
Node* parseExpression(const ListaEncadeada<std::string>& tokens) {
    PilhaEncadeada<Node*> nodes;
    PilhaEncadeada<std::string> ops;
    for (int i = 0; i < tokens.GetTamanho(); i++) {
        std::string token = tokens.GetItem(i);
        if (token == "(") {
            ops.Empilha(token);
        } else if (token == ")") {
            while (!ops.Vazia() && ops.Topo() != "(") {
                Node* right = nodes.Desempilha();
                Node* left = nodes.Desempilha();
                Node* opNode = new Node(ops.Desempilha());
                opNode->left = left;
                opNode->right = right;
                nodes.Empilha(opNode);
            }
            if (!ops.Vazia()) {
                ops.Desempilha(); // remove o "("
            }
        } else if (token == "&&") {
            while (!ops.Vazia() && ops.Topo() != "(") {
                Node* right = nodes.Desempilha();
                Node* left = nodes.Desempilha();
                Node* opNode = new Node(ops.Desempilha());
                opNode->left = left;
                opNode->right = right;
                nodes.Empilha(opNode);
            }
            ops.Empilha(token);
        } else if (token == "==" || token == "<=") {
            ops.Empilha(token);
        } else {
            nodes.Empilha(new Node(token));
        }
    }
    while (!ops.Vazia()) {
        Node* right = nodes.Desempilha();
        Node* left = nodes.Desempilha();
        Node* opNode = new Node(ops.Desempilha());
        opNode->left = left;
        opNode->right = right;
        nodes.Empilha(opNode);
    }
    return nodes.Desempilha();
}

// Função para imprimir a árvore (para debug)
void printTree(Node* root, int level = 0) {
    if (!root)
        return;
    printTree(root->right, level + 1);
    std::cout << std::string(level * 4, ' ') << root->value << std::endl;
    printTree(root->left, level + 1);
}

// Função que avalia a árvore de expressão para um determinado Voo
bool evaluate(Node* root, Voo* voo) {
    // Se for nó folha, geralmente não deve ocorrer em expressões válidas
    if (!root->left && !root->right) {
        return false;
    }
    
    // Processa operadores lógicos e de comparação
    if (root->value == "&&") {
        return evaluate(root->left, voo) && evaluate(root->right, voo);
    } else if (root->value == "==") {
        // No nó de comparação, o lado esquerdo é o atributo e o direito é o valor esperado
        std::string atributo = root->left->value;
        std::string valor = root->right->value;
        if (atributo == "org") {
            return voo->origem == valor;
        } else if (atributo == "dst") {
            return voo->destino == valor;
        }
    } else if (root->value == "<=") {
        std::string atributo = root->left->value;
        float valor = std::stof(root->right->value);
        if (atributo == "prc") {
            return voo->preco <= valor;
        } else if (atributo == "dur") {
            return voo->duracao <= static_cast<std::time_t>(valor);
        }
    }
    return false;
}

// Função que filtra os voos aplicando a árvore de expressão
ListaEncadeada<Voo*> filtrarVoos(Node* root, Voo** voos, int numVoos) {
    ListaEncadeada<Voo*> voosFiltrados;
    for (int i = 0; i < numVoos; i++) {
        if (evaluate(root, voos[i])) {
            voosFiltrados.InsereFinal(voos[i]);
        }
    }
    return voosFiltrados;
}
