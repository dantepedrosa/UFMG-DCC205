/**
 * @file Filtro.hpp
 * @brief Sistema de filtragem de voos usando árvore de expressão
 * @author Dante Junqueira Pedrosa
 * @date 2025
 * 
 * Este arquivo contém a implementação de uma árvore de expressão para
 * filtrar voos com base em expressões booleanas complexas.
 */

#pragma once

#include <string>
#include "../include/Voo.hpp"
#include "../include/Pilha.hpp"
#include "../include/ListaEncadeada.hpp"

// Define as precedências dos operadores
#define PREC_NOT 4    // Precedência do operador NOT (!)
#define PREC_COMP 3   // Precedência dos operadores de comparação (==, !=, <=, >=, <, >)
#define PREC_AND 2    // Precedência do operador AND (&&)
#define PREC_OR  1    // Precedência do operador OR (||)
#define PREC_NONE 0   // Precedência para tokens não-operadores

/**
 * @brief Classe que implementa uma árvore de expressão para filtragem de voos
 * 
 * Esta classe permite construir e avaliar expressões booleanas complexas
 * para filtrar voos com base em múltiplos critérios como:
 * - Origem (org)
 * - Destino (dst)
 * - Preço (prc)
 * - Assentos disponíveis (sea)
 * - Número de paradas (sto)
 * - Duração do voo (dur)
 */
class ArvoreDeExpressao {
private:
    /**
     * @brief Estrutura de nó da árvore de expressão
     */
    struct No {
        std::string value;  // Valor armazenado no nó (operador ou operando)
        No* left;          // Ponteiro para o filho esquerdo
        No* right;         // Ponteiro para o filho direito

        /**
         * @brief Construtor do nó
         * @param val Valor a ser armazenado no nó
         */
        No(std::string val) : value(val), left(nullptr), right(nullptr) {}
    };

    No* root;  // Raiz da árvore de expressão

    /**
     * @brief Converte uma string em uma lista de tokens
     * @param expr String contendo a expressão
     * @return Lista de tokens
     */
    ListaEncadeada<std::string> tokenizar(const std::string& expr);

    /**
     * @brief Constrói a árvore de expressão a partir dos tokens
     * @param tokens Lista de tokens da expressão
     * @return Ponteiro para a raiz da árvore construída
     */
    No* montaArvoreExpressao(const ListaEncadeada<std::string>& tokens);

    /**
     * @brief Retorna a precedência do operador
     * @param op String contendo o operador
     * @return Valor numérico da precedência
     */
    int getOperatorPrecedence(const std::string& op);

    /**
     * @brief Avalia a expressão para um voo específico
     * @param node Nó atual da árvore
     * @param voo Voo a ser avaliado
     * @return true se o voo satisfaz a expressão, false caso contrário
     */
    bool evaluate(No* node, Voo* voo);

    /**
     * @brief Libera a memória da árvore recursivamente
     * @param node Nó atual a ser liberado
     */
    void deleteTree(No* node);

public:
    /**
     * @brief Construtor que inicializa a árvore com uma expressão
     * @param expr String contendo a expressão booleana
     */
    ArvoreDeExpressao(const std::string& expr) : root(nullptr) {
        ListaEncadeada<std::string> tokens = tokenizar(expr);
        root = montaArvoreExpressao(tokens);
    }

    /**
     * @brief Destrutor que libera a memória da árvore
     */
    ~ArvoreDeExpressao() {
        deleteTree(root);
    }

    /**
     * @brief Filtra um array de voos de acordo com a expressão
     * @param voos Array de ponteiros para voos
     * @param numVoos Número de voos no array
     * @return Lista encadeada contendo os voos que satisfazem a expressão
     */
    ListaEncadeada<Voo*> filtrarVoos(Voo** voos, int numVoos) {
        ListaEncadeada<Voo*> voosFiltrados;
        for (int i = 0; i < numVoos; i++) {
            if (evaluate(root, voos[i])) {
                voosFiltrados.InsereFinal(voos[i]);
            }
        }
        return voosFiltrados;
    }

    #ifdef DEBUG
    /**
     * @brief Imprime a árvore para debugging
     */
    void printTree() {
        printTreeRecursive(root, 0);
    }
    
private:
    /**
     * @brief Função auxiliar recursiva para impressão da árvore
     * @param node Nó atual
     * @param level Nível de indentação
     */
    void printTreeRecursive(No* node, int level);
    #endif
};

ListaEncadeada<std::string> ArvoreDeExpressao::tokenizar(const std::string& expr) {
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

ArvoreDeExpressao::No* ArvoreDeExpressao::montaArvoreExpressao(const ListaEncadeada<std::string>& tokens) {
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

int ArvoreDeExpressao::getOperatorPrecedence(const std::string& op) {
    if (op == "!") return PREC_NOT;
    if (op == "==" || op == "!=" || op == "<=" || op == ">=" || op == "<" || op == ">") 
        return PREC_COMP;
    if (op == "&&") return PREC_AND;
    if (op == "||") return PREC_OR;
    return PREC_NONE;
}

bool ArvoreDeExpressao::evaluate(No* root, Voo* voo) {
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

void ArvoreDeExpressao::deleteTree(No* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

#ifdef DEBUG
void ArvoreDeExpressao::printTreeRecursive(No* node, int level) {
    if (!node) return;
    printTreeRecursive(node->right, level + 1);
    std::cout << std::string(level * 4, ' ') << node->value << std::endl;
    printTreeRecursive(node->left, level + 1);
}
#endif
