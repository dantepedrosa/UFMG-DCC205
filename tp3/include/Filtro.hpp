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
            if (!temp.empty()) {
                tokens.InsereFinal(temp);
                temp = "";
            }
            tokens.InsereFinal(std::string(1, c));
        } else if (c == '&' && i + 1 < expr.size() && expr[i + 1] == '&') {
            if (!temp.empty()) {
                tokens.InsereFinal(temp);
                temp = "";
            }
            tokens.InsereFinal("&&");
            i++;
        } else if (c == '|' && i + 1 < expr.size() && expr[i + 1] == '|') {
            if (!temp.empty()) {
                tokens.InsereFinal(temp);
                temp = "";
            }
            tokens.InsereFinal("||");
            i++;
        } else if (c == '=' && i + 1 < expr.size() && expr[i + 1] == '=') {
            if (!temp.empty()) {
                tokens.InsereFinal(temp);
                temp = "";
            }
            tokens.InsereFinal("==");
            i++;
        } else if (c == '<' && i + 1 < expr.size() && expr[i + 1] == '=') {
            if (!temp.empty()) {
                tokens.InsereFinal(temp);
                temp = "";
            }
            tokens.InsereFinal("<=");
            i++;
        } else if (c == '>' && i + 1 < expr.size() && expr[i + 1] == '=') {
            if (!temp.empty()) {
                tokens.InsereFinal(temp);
                temp = "";
            }
            tokens.InsereFinal(">=");
            i++;
        } else if (c == '<' || c == '>' || c == '!') {
            if (!temp.empty()) {
                tokens.InsereFinal(temp);
                temp = "";
            }
            tokens.InsereFinal(std::string(1, c));
        } else {
            // Incluir dígitos, letras e ponto decimal no token
            if (std::isalnum(c) || c == '.') {
                temp += c;
            }
            
            // Se o próximo caractere não for alfanumérico ou ponto decimal, ou for final da string
            if (i + 1 == expr.size() || 
                (!std::isalnum(expr[i + 1]) && expr[i + 1] != '.')) {
                if (!temp.empty()) {
                    tokens.InsereFinal(temp);
                    temp = "";
                }
            }
        }
    }
    return tokens;
}

// Define as precedências dos operadores
#define PREC_NOT 4    // !
#define PREC_COMP 3   // ==, !=, <=, >=, <, >
#define PREC_AND 2    // &&
#define PREC_OR  1    // ||
#define PREC_NONE 0   // outros

/**
 * @brief Retorna a precedência do operador
 * @param op Operador a ser avaliado
 * @return Valor numérico representando a precedência (maior valor = maior precedência)
 */
int getOperatorPrecedence(const std::string& op) {
    if (op == "!") return PREC_NOT;
    if (op == "==" || op == "!=" || op == "<=" || op == ">=" || op == "<" || op == ">") 
        return PREC_COMP;
    if (op == "&&") return PREC_AND;
    if (op == "||") return PREC_OR;
    return PREC_NONE;
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
        } 
        else if (token == ")") {
            while (!ops.Vazia() && ops.Topo() != "(") {
                std::string op = ops.Desempilha();
                if (op == "!") {
                    if (!nodes.Vazia()) {
                        No* operand = nodes.Desempilha();
                        No* opNode = new No(op);
                        opNode->left = operand;
                        nodes.Empilha(opNode);
                    }
                } else if (nodes.GetTamanho() >= 2) {
                    No* right = nodes.Desempilha();
                    No* left = nodes.Desempilha();
                    No* opNode = new No(op);
                    opNode->left = left;
                    opNode->right = right;
                    nodes.Empilha(opNode);
                }
            }
            if (!ops.Vazia()) {
                ops.Desempilha(); // Remove "("
            }
        } 
        else if (getOperatorPrecedence(token) > PREC_NONE) {
            while (!ops.Vazia() && ops.Topo() != "(" && 
                   getOperatorPrecedence(ops.Topo()) >= getOperatorPrecedence(token)) {
                std::string op = ops.Desempilha();
                if (op == "!") {
                    if (!nodes.Vazia()) {
                        No* operand = nodes.Desempilha();
                        No* opNode = new No(op);
                        opNode->left = operand;
                        nodes.Empilha(opNode);
                    }
                } else if (nodes.GetTamanho() >= 2) {
                    No* right = nodes.Desempilha();
                    No* left = nodes.Desempilha();
                    No* opNode = new No(op);
                    opNode->left = left;
                    opNode->right = right;
                    nodes.Empilha(opNode);
                }
            }
            ops.Empilha(token);
        } 
        else {
            nodes.Empilha(new No(token));
        }
    }

    while (!ops.Vazia()) {
        std::string op = ops.Desempilha();
        if (op == "(") continue;
        
        if (op == "!") {
            if (!nodes.Vazia()) {
                No* operand = nodes.Desempilha();
                No* opNode = new No(op);
                opNode->left = operand;
                nodes.Empilha(opNode);
            }
        } else if (nodes.GetTamanho() >= 2) {
            No* right = nodes.Desempilha();
            No* left = nodes.Desempilha();
            No* opNode = new No(op);
            opNode->left = left;
            opNode->right = right;
            nodes.Empilha(opNode);
        }
    }

    return nodes.Vazia() ? nullptr : nodes.Desempilha();
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
    try {
        float valor = std::stof(root->right->value);
        
        if (atributo == "prc") {
            if (operador == "<=") return voo->preco <= valor;
            if (operador == ">=") return voo->preco >= valor;
            if (operador == "<") return voo->preco < valor;
            if (operador == ">") return voo->preco > valor;
            if (operador == "==") return std::abs(voo->preco - valor) < 0.01;   // Para evitar problema com tolerancia
            if (operador == "!=") return std::abs(voo->preco - valor) >= 0.01;  // Para evitar problema com tolerancia
        }
        if (atributo == "sea") {
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
    } catch (const std::exception& e) {
        std::cerr << "Erro na conversão do valor: " << root->right->value << std::endl;
        return false;
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
