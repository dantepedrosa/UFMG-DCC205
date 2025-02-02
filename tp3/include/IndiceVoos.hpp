/**
 * @file IndiceVoos.hpp
 * @brief Implementação da árvore AVL para indexação de voos
 * @author Dante Junqueira Pedrosa
 * @date 2025
 */
#pragma once

#include <string>
#include "../include/ListaEncadeada.hpp"

/**
 * @brief Classe que implementa um índice de voos usando árvore AVL adaptada
 */
class IndiceVoos {
private:
    /**
     * @brief Estrutura de nó da árvore AVL
     */
    struct No {
        std::string chave;              // Chave do nó (ex: "GRU", "CNF" etc)
        ListaEncadeada<int> indices;    // Lista de índices dos voos com esta chave
        int altura;                     // Altura do nó
        No* esq;                        // Ponteiro para o filho à esquerda
        No* dir;                        // Ponteiro para o filho à direita

        No(const std::string& k) : chave(k), altura(1), esq(nullptr), dir(nullptr) {}
    };

    No* raiz;  // Raiz da árvore AVL

    // Métodos auxiliares privados
    int altura(No* n) const;
    int max(int a, int b) const;
    No* rotacaoDireita(No* y);
    No* rotacaoEsquerda(No* x);
    int fatorBalanceamento(No* n) const;
    No* inserir(No* node, const std::string& chave, int indiceVoo);

public:
    /**
     * @brief Construtor da classe IndiceVoos
     */
    IndiceVoos() : raiz(nullptr) {}

    /**
     * @brief Insere um voo no índice
     * @param chave Chave do índice
     * @param indiceVoo Índice do voo
     */
    void inserir(const std::string& chave, int indiceVoo) {
        raiz = inserir(raiz, chave, indiceVoo);
    }

    /**
     * @brief Busca voos no índice por chave
     * @param chave Chave do índice
     * @return Ponteiro para a lista de índices dos voos
     */
    ListaEncadeada<int>* buscar(const std::string& chave) {
        No* atual = raiz;
        while (atual) {
            if (chave < atual->chave)
                atual = atual->esq;
            else if (chave > atual->chave)
                atual = atual->dir;
            else
                return &(atual->indices);
        }
        return nullptr;
    }
};

// Implementações dos métodos auxiliares
int IndiceVoos::altura(No* n) const {
    return n ? n->altura : 0;
}

int IndiceVoos::max(int a, int b) const {
    return std::max(a, b);
}

IndiceVoos::No* IndiceVoos::rotacaoDireita(No* y) {
    No* x = y->esq;
    No* T = x->dir;

    x->dir = y;
    y->esq = T;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

IndiceVoos::No* IndiceVoos::rotacaoEsquerda(No* x) {
    No* y = x->dir;
    No* T = y->esq;

    y->esq = x;
    x->dir = T;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

int IndiceVoos::fatorBalanceamento(No* n) const {
    return n ? altura(n->esq) - altura(n->dir) : 0;
}

IndiceVoos::No* IndiceVoos::inserir(No* node, const std::string& chave, int indiceVoo) {
    if (!node) {
        No* novo = new No(chave);
        novo->indices.InsereFinal(indiceVoo);
        return novo;
    }

    if (chave < node->chave)
        node->esq = inserir(node->esq, chave, indiceVoo);
    else if (chave > node->chave)
        node->dir = inserir(node->dir, chave, indiceVoo);
    else
        node->indices.InsereFinal(indiceVoo);

    node->altura = 1 + max(altura(node->esq), altura(node->dir));
    int balanco = fatorBalanceamento(node);

    if (balanco > 1 && chave < node->esq->chave)
        return rotacaoDireita(node);

    if (balanco < -1 && chave > node->dir->chave)
        return rotacaoEsquerda(node);

    if (balanco > 1 && chave > node->esq->chave) {
        node->esq = rotacaoEsquerda(node->esq);
        return rotacaoDireita(node);
    }

    if (balanco < -1 && chave < node->dir->chave) {
        node->dir = rotacaoDireita(node->dir);
        return rotacaoEsquerda(node);
    }

    return node;
}
