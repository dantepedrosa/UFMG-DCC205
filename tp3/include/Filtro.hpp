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
ListaEncadeada<std::string> tokenizar(const std::string& expr) {
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


// Função que retorna a precedência do operador
int getOperatorPrecedence(const std::string& op) {
    if (op == "!") return 3;
    if (op == "<" || op == "<=" || op == ">" || op == ">=" || op == "==") return 2;
    if (op == "&&" || op == "||") return 1;
    return 0;
}

// Função que monta a árvore de expressão a partir dos tokens
Node* montaArvoreExpressao(const ListaEncadeada<std::string>& tokens) {
    PilhaEncadeada<Node*> nodes;
    PilhaEncadeada<std::string> ops;

    for (int i = 0; i < tokens.GetTamanho(); i++) {
        std::string token = tokens.GetItem(i);
        
        if (token == "(") {
            ops.Empilha(token);
        } else if (token == ")") {
            while (!ops.Vazia() && ops.Topo() != "(") {
                std::string op = ops.Desempilha();
                if (op == "!") {
                    Node* operand = nodes.Desempilha();
                    Node* opNode = new Node(op);
                    opNode->left = operand;
                    nodes.Empilha(opNode);
                } else {
                    Node* right = nodes.Desempilha();
                    Node* left = nodes.Desempilha();
                    Node* opNode = new Node(op);
                    opNode->left = left;
                    opNode->right = right;
                    nodes.Empilha(opNode);
                }
            }
            if (!ops.Vazia()) ops.Desempilha(); // Remove "("
        } else if (getOperatorPrecedence(token) > 0) {
            while (!ops.Vazia() && ops.Topo() != "(" && 
                   getOperatorPrecedence(ops.Topo()) >= getOperatorPrecedence(token)) {
                std::string op = ops.Desempilha();
                if (op == "!") {
                    Node* operand = nodes.Desempilha();
                    Node* opNode = new Node(op);
                    opNode->left = operand;
                    nodes.Empilha(opNode);
                } else {
                    Node* right = nodes.Desempilha();
                    Node* left = nodes.Desempilha();
                    Node* opNode = new Node(op);
                    opNode->left = left;
                    opNode->right = right;
                    nodes.Empilha(opNode);
                }
            }
            ops.Empilha(token);
        } else {
            nodes.Empilha(new Node(token));
        }
    }

    while (!ops.Vazia()) {
        std::string op = ops.Desempilha();
        if (op == "!") {
            Node* operand = nodes.Desempilha();
            Node* opNode = new Node(op);
            opNode->left = operand;
            nodes.Empilha(opNode);
        } else {
            Node* right = nodes.Desempilha();
            Node* left = nodes.Desempilha();
            Node* opNode = new Node(op);
            opNode->left = left;
            opNode->right = right;
            nodes.Empilha(opNode);
        }
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
    if (!root) return false;
    
    // Handle unary operator
    if (root->value == "!") {
        return !evaluate(root->left, voo);
    }
    
    // Handle leaf nodes
    if (!root->left && !root->right) {
        return false;
    }
    
    // Handle logical operators
    if (root->value == "&&") {
        return evaluate(root->left, voo) && evaluate(root->right, voo);
    } else if (root->value == "||") {
        return evaluate(root->left, voo) || evaluate(root->right, voo);
    }
    
    // Handle comparison operators
    std::string atributo = root->left->value;
    std::string operador = root->value;
    
    // String comparisons (org, dst)
    if (atributo == "org" || atributo == "dst") {
        std::string valor = root->right->value;
        if (operador == "==") {
            return (atributo == "org") ? voo->origem == valor : voo->destino == valor;
        } else if (operador == "!=") {
            return (atributo == "org") ? voo->origem != valor : voo->destino != valor;
        }
        return false;
    }
    
    // Numeric comparisons (prc, sea, sto, dur)
    float valor = std::stof(root->right->value);
    
    if (atributo == "prc") {
        if (operador == "<=") return voo->preco <= valor;
        if (operador == ">=") return voo->preco >= valor;
        if (operador == "<")  return voo->preco < valor;
        if (operador == ">")  return voo->preco > valor;
        if (operador == "==") return voo->preco == valor;
        if (operador == "!=") return voo->preco != valor;
    } 
    else if (atributo == "sea") {
        if (operador == "<=") return voo->assentos <= valor;
        if (operador == ">=") return voo->assentos >= valor;
        if (operador == "<")  return voo->assentos < valor;
        if (operador == ">")  return voo->assentos > valor;
        if (operador == "==") return voo->assentos == valor;
        if (operador == "!=") return voo->assentos != valor;
    }
    else if (atributo == "sto") {
        if (operador == "<=") return voo->paradas <= valor;
        if (operador == ">=") return voo->paradas >= valor;
        if (operador == "<")  return voo->paradas < valor;
        if (operador == ">")  return voo->paradas > valor;
        if (operador == "==") return voo->paradas == valor;
        if (operador == "!=") return voo->paradas != valor;
    }
    else if (atributo == "dur") {
        std::time_t duracao = static_cast<std::time_t>(valor);
        if (operador == "<=") return voo->duracao <= duracao;
        if (operador == ">=") return voo->duracao >= duracao;
        if (operador == "<")  return voo->duracao < duracao;
        if (operador == ">")  return voo->duracao > duracao;
        if (operador == "==") return voo->duracao == duracao;
        if (operador == "!=") return voo->duracao != duracao;
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
