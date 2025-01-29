#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <cstdlib>
#include <cstdio>

template <typename T>
struct No {
    T chave;
    No *esq;
    No *dir;
    int altura;
};

template <typename T>
int max(int a, int b) {
    return (a > b) ? a : b;
}

template <typename T>
int altura(No<T> *n) {
    return n ? n->altura : 0;
}

template <typename T>
No<T> *novoNo(T chave) {
    No<T> *no = (No<T> *)malloc(sizeof(No<T>));
    no->chave = chave;
    no->esq = nullptr;
    no->dir = nullptr;
    no->altura = 1;
    return no;
}

template <typename T>
No<T> *rotacaoDireita(No<T> *y) {
    No<T> *x = y->esq;
    No<T> *T = x->dir;
    x->dir = y;
    y->esq = T;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    return x;
}

template <typename T>
No<T> *rotacaoEsquerda(No<T> *x) {
    No<T> *y = x->dir;
    No<T> *T = y->esq;
    y->esq = x;
    x->dir = T;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    return y;
}

template <typename T>
int fatorBalanceamento(No<T> *n) {
    return n ? altura(n->esq) - altura(n->dir) : 0;
}

template <typename T>
No<T> *inserir(No<T> *raiz, T chave) {
    if (!raiz) return novoNo(chave);
    if (chave < raiz->chave) raiz->esq = inserir(raiz->esq, chave);
    else if (chave > raiz->chave) raiz->dir = inserir(raiz->dir, chave);
    else return raiz;
    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    int balanco = fatorBalanceamento(raiz);
    if (balanco > 1 && chave < raiz->esq->chave) return rotacaoDireita(raiz);
    if (balanco < -1 && chave > raiz->dir->chave) return rotacaoEsquerda(raiz);
    if (balanco > 1 && chave > raiz->esq->chave) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    if (balanco < -1 && chave < raiz->dir->chave) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }
    return raiz;
}

template <typename T>
No<T> *minValorNo(No<T> *no) {
    No<T> *atual = no;
    while (atual->esq) atual = atual->esq;
    return atual;
}

template <typename T>
No<T> *remover(No<T> *raiz, T chave) {
    if (!raiz) return raiz;
    if (chave < raiz->chave) raiz->esq = remover(raiz->esq, chave);
    else if (chave > raiz->chave) raiz->dir = remover(raiz->dir, chave);
    else {
        if (!raiz->esq || !raiz->dir) {
            No<T> *temp = raiz->esq ? raiz->esq : raiz->dir;
            if (!temp) {
                temp = raiz;
                raiz = nullptr;
            } else *raiz = *temp;
            free(temp);
        } else {
            No<T> *temp = minValorNo(raiz->dir);
            raiz->chave = temp->chave;
            raiz->dir = remover(raiz->dir, temp->chave);
        }
    }
    if (!raiz) return raiz;
    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    int balanco = fatorBalanceamento(raiz);
    if (balanco > 1 && fatorBalanceamento(raiz->esq) >= 0) return rotacaoDireita(raiz);
    if (balanco > 1 && fatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    if (balanco < -1 && fatorBalanceamento(raiz->dir) <= 0) return rotacaoEsquerda(raiz);
    if (balanco < -1 && fatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }
    return raiz;
}

template <typename T>
void preOrdem(No<T> *raiz) {
    if (raiz) {
        printf("%d ", raiz->chave);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

template <typename T>
void inOrdem(No<T> *raiz) {
    if (raiz) {
        inOrdem(raiz->esq);
        printf("%d ", raiz->chave);
        inOrdem(raiz->dir);
    }
}

template <typename T>
void posOrdem(No<T> *raiz) {
    if (raiz) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->chave);
    }
}

#endif // AVL_TREE_HPP
