#include <iostream>
#include <stack>
#include <vector>

#include "Voo.hpp"

using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    string temp;
    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (isspace(c)) continue;

        if (c == '(' || c == ')') {
            tokens.push_back(string(1, c));
        } else if (c == '&' && i + 1 < expr.size() && expr[i + 1] == '&') {
            tokens.push_back("&&");
            i++;
        } else if (c == '=' && i + 1 < expr.size() && expr[i + 1] == '=') {
            tokens.push_back("==");
            i++;
        } else if (c == '<' && i + 1 < expr.size() && expr[i + 1] == '=') {
            tokens.push_back("<=");
            i++;
        } else {
            temp += c;
            if (i + 1 == expr.size() || !isalnum(expr[i + 1])) {
                tokens.push_back(temp);
                temp = "";
            }
        }
    }
    return tokens;
}

Node* parseExpression(const vector<string>& tokens) {
    stack<Node*> nodes;
    stack<string> ops;
    for (const string& token : tokens) {
        if (token == "(") {
            ops.push(token);
        } else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                Node* right = nodes.top(); nodes.pop();
                Node* left = nodes.top(); nodes.pop();
                Node* opNode = new Node(ops.top()); ops.pop();
                opNode->left = left;
                opNode->right = right;
                nodes.push(opNode);
            }
            ops.pop();
        } else if (token == "&&") {
            while (!ops.empty() && ops.top() != "(") {
                Node* right = nodes.top(); nodes.pop();
                Node* left = nodes.top(); nodes.pop();
                Node* opNode = new Node(ops.top()); ops.pop();
                opNode->left = left;
                opNode->right = right;
                nodes.push(opNode);
            }
            ops.push(token);
        } else if (token == "==" || token == "<=") {
            ops.push(token);
        } else {
            nodes.push(new Node(token));
        }
    }
    return nodes.top();
}

void printTree(Node* root, int level = 0) {
    if (!root) return;
    printTree(root->right, level + 1);
    cout << string(level * 4, ' ') << root->value << endl;
    printTree(root->left, level + 1);
}

// Exemplo da função de avaliação
bool evaluate(Node* root, Voo* voo) {
    // Se for nó folha, pode ser um literal (ex.: "DEN", "ORD", "500", "8400") ou um identificador (ex.: "org", "prc")
    // Mas, na prática, os nós folhas são utilizados nos operadores, então essa parte é acionada nos nós de comparação.
    if (!root->left && !root->right) {
        // Em geral, não devemos chegar aqui sem que um operador tenha sido processado.
        return false;
    }
    
    // Processa operadores lógicos ou de comparação
    if (root->value == "&&") {
        // Operador lógico AND: avalia ambos os lados
        return evaluate(root->left, voo) && evaluate(root->right, voo);
    } else if (root->value == "==") {
        // Para '==', supomos que o nó esquerdo é o nome do atributo e o direito o valor esperado.
        std::string atributo = root->left->value;
        std::string valor = root->right->value;
        if (atributo == "org") {
            return voo->origem == valor;
        } else if (atributo == "dst") {
            return voo->destino == valor;
        }
        // Acrescente outros atributos se necessário
    } else if (root->value == "<=") {
        // Para '<=', o nó esquerdo é o nome do atributo e o direito é o valor numérico (armazenado como string)
        std::string atributo = root->left->value;
        // Converte a string para float (ou para int, se for o caso)
        float valor = std::stof(root->right->value);
        if (atributo == "prc") {
            return voo->preco <= valor;
        } else if (atributo == "dur") {
            // Supondo que 'duracao' está em segundos (time_t) e o valor comparado também
            return voo->duracao <= static_cast<std::time_t>(valor);
        }
        // Outros atributos podem ser processados de forma similar.
    }
    // Se houver outros operadores (por exemplo, >=, >, <) acrescente-os aqui.
    
    // Se não for reconhecido, retorne false
    return false;
}


int main() {
    string expression = "(((org==DEN)&&(dst==ORD))&&((prc<=500)&&(dur<=8400)))";
    vector<string> tokens = tokenize(expression);
    Node* root = parseExpression(tokens);
    printTree(root);
    return 0;
}
