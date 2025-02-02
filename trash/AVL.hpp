#pragma once

#include <iostream>
#include <algorithm>

class AVLTree {
private:
    /**
     * @brief Estrutura que representa um nó da árvore.
     */
    struct No {
        int chave;      ///< Chave do nó
        int altura;     ///< Altura do nó
        No* esq;        ///< Ponteiro para o filho à esquerda
        No* dir;        ///< Ponteiro para o filho à direita

        No(int k) : chave(k), altura(1), esq(nullptr), dir(nullptr) {}
    };

    No* raiz;  ///< Ponteiro para a raiz da árvore

    // Métodos auxiliares privados - apenas declarações
    int altura(No* n) const;
    int max(int a, int b) const;
    No* rotacaoDireita(No* y);
    No* rotacaoEsquerda(No* x);
    int fatorBalanceamento(No* n) const;
    No* inserir(No* node, int chave);
    No* minValorNo(No* node);
    No* remover(No* node, int chave);
    void preOrdem(No* node) const;
    void inOrdem(No* node) const;
    void posOrdem(No* node) const;
    void destruir(No* node);

public:
    /**
     * @brief Construtor da árvore AVL.
     */
    AVLTree() : raiz(nullptr) {}

    /**
     * @brief Destrutor da árvore AVL.
     */
    ~AVLTree() { destruir(raiz); }

    /**
     * @brief Insere uma chave na árvore AVL.
     * @param chave Chave a ser inserida.
     */
    void inserir(int chave) { raiz = inserir(raiz, chave); }

    /**
     * @brief Remove uma chave da árvore AVL.
     * @param chave Chave a ser removida.
     */
    void remover(int chave) { raiz = remover(raiz, chave); }

    /**
     * @brief Exibe os elementos da árvore em pré-ordem.
     */
    void preOrdem() const;

    /**
     * @brief Exibe os elementos da árvore em ordem.
     */
    void inOrdem() const;

    /**
     * @brief Exibe os elementos da árvore em pós-ordem.
     */
    void posOrdem() const;
};

// Implementações dos métodos privados
inline int AVLTree::altura(No* n) const {
    return n ? n->altura : 0;
}

inline int AVLTree::max(int a, int b) const {
    return std::max(a, b);
}

inline AVLTree::No* AVLTree::rotacaoDireita(No* y) {
    No* x = y->esq;
    No* T = x->dir;

    // Executa a rotação
    x->dir = y;
    y->esq = T;

    // Atualiza as alturas
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    // Retorna nova raiz
    return x;
}

inline AVLTree::No* AVLTree::rotacaoEsquerda(No* x) {
    No* y = x->dir;
    No* T = y->esq;

    // Executa a rotação
    y->esq = x;
    x->dir = T;

    // Atualiza as alturas
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    // Retorna nova raiz
    return y;
}

inline int AVLTree::fatorBalanceamento(No* n) const {
    return n ? altura(n->esq) - altura(n->dir) : 0;
}

inline AVLTree::No* AVLTree::inserir(No* node, int chave) {
    // Inserção normal em árvore binária de busca.
    if (!node)
        return new No(chave);

    if (chave < node->chave)
        node->esq = inserir(node->esq, chave);
    else if (chave > node->chave)
        node->dir = inserir(node->dir, chave);
    else  // Chaves duplicadas não são permitidas.
        return node;

    // Atualiza a altura deste nó.
    node->altura = 1 + max(altura(node->esq), altura(node->dir));

    // Calcula o fator de balanceamento deste nó.
    int balanco = fatorBalanceamento(node);

    // Caso 1 - Rotação à direita.
    if (balanco > 1 && chave < node->esq->chave)
        return rotacaoDireita(node);

    // Caso 2 - Rotação à esquerda.
    if (balanco < -1 && chave > node->dir->chave)
        return rotacaoEsquerda(node);

    // Caso 3 - Rotacão dupla: esquerda no filho esquerdo.
    if (balanco > 1 && chave > node->esq->chave) {
        node->esq = rotacaoEsquerda(node->esq);
        return rotacaoDireita(node);
    }

    // Caso 4 - Rotação dupla: direita no filho direito.
    if (balanco < -1 && chave < node->dir->chave) {
        node->dir = rotacaoDireita(node->dir);
        return rotacaoEsquerda(node);
    }

    return node;
}

inline AVLTree::No* AVLTree::minValorNo(No* node) {
    No* atual = node;
    while (atual && atual->esq != nullptr)
        atual = atual->esq;
    return atual;
}

inline AVLTree::No* AVLTree::remover(No* node, int chave) {
    if (!node)
        return node;

    // Realiza a remoção de forma semelhante à de uma árvore binária de busca.
    if (chave < node->chave)
        node->esq = remover(node->esq, chave);
    else if (chave > node->chave)
        node->dir = remover(node->dir, chave);
    else {
        // Nó com apenas um filho ou nenhum filho.
        if (!node->esq || !node->dir) {
            No* temp = node->esq ? node->esq : node->dir;

            // Caso sem filho.
            if (!temp) {
                temp = node;
                node = nullptr;
            } else { // Um filho.
                *node = *temp;
            }
            delete temp;
        } else {
            // Nó com dois filhos: pega o sucessor (menor na subárvore direita).
            No* temp = minValorNo(node->dir);
            node->chave = temp->chave;
            node->dir = remover(node->dir, temp->chave);
        }
    }

    // Se a árvore tinha apenas um nó.
    if (!node)
        return node;

    // Atualiza a altura.
    node->altura = 1 + max(altura(node->esq), altura(node->dir));

    // Calcula o fator de balanceamento.
    int balanco = fatorBalanceamento(node);

    // Balanceamento da árvore.
    if (balanco > 1 && fatorBalanceamento(node->esq) >= 0)
        return rotacaoDireita(node);

    if (balanco > 1 && fatorBalanceamento(node->esq) < 0) {
        node->esq = rotacaoEsquerda(node->esq);
        return rotacaoDireita(node);
    }

    if (balanco < -1 && fatorBalanceamento(node->dir) <= 0)
        return rotacaoEsquerda(node);

    if (balanco < -1 && fatorBalanceamento(node->dir) > 0) {
        node->dir = rotacaoDireita(node->dir);
        return rotacaoEsquerda(node);
    }

    return node;
}

inline void AVLTree::preOrdem(No* node) const {
    if (node) {
        std::cout << node->chave << " ";
        preOrdem(node->esq);
        preOrdem(node->dir);
    }
}

inline void AVLTree::inOrdem(No* node) const {
    if (node) {
        inOrdem(node->esq);
        std::cout << node->chave << " ";
        inOrdem(node->dir);
    }
}

inline void AVLTree::posOrdem(No* node) const {
    if (node) {
        posOrdem(node->esq);
        posOrdem(node->dir);
        std::cout << node->chave << " ";
    }
}

inline void AVLTree::destruir(No* node) {
    if (node) {
        destruir(node->esq);
        destruir(node->dir);
        delete node;
    }
}

// Implementações dos métodos públicos
void AVLTree::preOrdem() const {
    preOrdem(raiz);
    std::cout << std::endl;
}

void AVLTree::inOrdem() const {
    inOrdem(raiz);
    std::cout << std::endl;
}

void AVLTree::posOrdem() const {
    posOrdem(raiz);
    std::cout << std::endl;
}

