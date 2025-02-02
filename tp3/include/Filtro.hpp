/**
 * @file Filtro.hpp
 * @brief Arquivo contendo as definições para filtragem e processamento de consultas de voos
 * @author Dante Junqueira Pedrosa
 * @date 2025
 */

#include <string>
#include "../include/Voo.hpp"
#include "../include/Pilha.hpp"
#include "../include/ListaEncadeada.hpp"

/**
 * @brief Estrutura que representa um nó na árvore de expressão
 */
struct No {
    std::string value;   // Valor armazenado no nó
    No* left;          // Ponteiro para o filho esquerdo
    No* right;         // Ponteiro para o filho direito

    /**
     * @brief Construtor do nó
     * @param val Valor a ser armazenado no nó
     */
    No(std::string val) : value(val), left(nullptr), right(nullptr) {}
};

/**
 * @brief Converte uma expressão em uma lista de tokens
 * @param expr Expressão a ser tokenizada
 * @return Lista encadeada contendo os tokens
 */
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

/**
 * @brief Retorna a precedência do operador
 * @param op Operador a ser avaliado
 * @return Valor numérico representando a precedência (maior valor = maior precedência)
 */
int getOperatorPrecedence(const std::string& op) {
    if (op == "!") return 3;
    if (op == "<" || op == "<=" || op == ">" || op == ">=" || op == "==") return 2;
    if (op == "&&" || op == "||") return 1;
    return 0;
}

/**
 * @brief Monta uma árvore de expressão a partir de uma lista de tokens
 * @param tokens Lista de tokens a ser processada
 * @return Ponteiro para a raiz da árvore de expressão
 */
No* montaArvoreExpressao(const ListaEncadeada<std::string>& tokens) {
    PilhaEncadeada<No*> nodes;
    PilhaEncadeada<std::string> ops;

    for (int i = 0; i < tokens.GetTamanho(); i++) {
        std::string token = tokens.GetItem(i);
        
        if (token == "(") {
            ops.Empilha(token);
        } else if (token == ")") {
            while (!ops.Vazia() && ops.Topo() != "(") {
                std::string op = ops.Desempilha();
                if (op == "!") {
                    No* operand = nodes.Desempilha();
                    No* opNode = new No(op);
                    opNode->left = operand;
                    nodes.Empilha(opNode);
                } else {
                    No* right = nodes.Desempilha();
                    No* left = nodes.Desempilha();
                    No* opNode = new No(op);
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
                    No* operand = nodes.Desempilha();
                    No* opNode = new No(op);
                    opNode->left = operand;
                    nodes.Empilha(opNode);
                } else {
                    No* right = nodes.Desempilha();
                    No* left = nodes.Desempilha();
                    No* opNode = new No(op);
                    opNode->left = left;
                    opNode->right = right;
                    nodes.Empilha(opNode);
                }
            }
            ops.Empilha(token);
        } else {
            nodes.Empilha(new No(token));
        }
    }

    while (!ops.Vazia()) {
        std::string op = ops.Desempilha();
        if (op == "!") {
            No* operand = nodes.Desempilha();
            No* opNode = new No(op);
            opNode->left = operand;
            nodes.Empilha(opNode);
        } else {
            No* right = nodes.Desempilha();
            No* left = nodes.Desempilha();
            No* opNode = new No(op);
            opNode->left = left;
            opNode->right = right;
            nodes.Empilha(opNode);
        }
    }

    return nodes.Desempilha();
}

/**
 * @brief Imprime a árvore de expressão (função auxiliar para debug)
 * @param root Ponteiro para a raiz da árvore
 * @param level Nível atual na árvore (usado para indentação)
 */
void printTree(No* root, int level = 0) {
    if (!root)
        return;
    printTree(root->right, level + 1);
    std::cout << std::string(level * 4, ' ') << root->value << std::endl;
    printTree(root->left, level + 1);
}

/**
 * @brief Avalia uma expressão para um determinado voo
 * @param root Ponteiro para a raiz da árvore de expressão
 * @param voo Ponteiro para o voo a ser avaliado
 * @return true se o voo satisfaz a expressão, false caso contrário
 */
bool evaluate(No* root, Voo* voo) {
    if (!root) return false;
    
    // Trata operador unário
    if (root->value == "!") {
        return !evaluate(root->left, voo);
    }
    
    // Trata nós folha (não deve ocorrer em expressões válidas)
    if (!root->left && !root->right) {
        return false;
    }
    
    // Trata operadores lógicos
    if (root->value == "&&") {
        return evaluate(root->left, voo) && evaluate(root->right, voo);
    } else if (root->value == "||") {
        return evaluate(root->left, voo) || evaluate(root->right, voo);
    }
    
    // Trata operadores de comparação
    std::string atributo = root->left->value;
    std::string operador = root->value;
    
    // Comparações de string (org, dst)
    if (atributo == "org" || atributo == "dst") {
        std::string valor = root->right->value;
        if (operador == "==") {
            return (atributo == "org") ? voo->origem == valor : voo->destino == valor;
        } else if (operador == "!=") {
            return (atributo == "org") ? voo->origem != valor : voo->destino != valor;
        }
        return false;
    }
    
    // Comparações numéricas (prc, sea, sto, dur)
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

/**
 * @brief Libera recursivamente os nós da árvore de expressão
 * @param root Ponteiro para a raiz da árvore a ser liberada
 */
void deleteTree(No* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/**
 * @brief Filtra uma lista de voos de acordo com uma expressão
 * @param root Ponteiro para a raiz da árvore de expressão
 * @param voos Array de ponteiros para voos
 * @param numVoos Número de voos no array
 * @return Lista encadeada contendo os voos que satisfazem a expressão
 */
ListaEncadeada<Voo*> filtrarVoos(No* root, Voo** voos, int numVoos) {
    ListaEncadeada<Voo*> voosFiltrados;
    for (int i = 0; i < numVoos; i++) {
        if (evaluate(root, voos[i])) {
            voosFiltrados.InsereFinal(voos[i]);
        }
    }
    return voosFiltrados;
}
