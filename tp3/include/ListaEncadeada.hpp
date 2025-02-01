#ifndef LISTA_ENCADEADA_HPP
#define LISTA_ENCADEADA_HPP

#include <iostream>

template <typename T>
class ListaEncadeada {
private:
    struct No {
        T dado;
        No* prox;
    };
    No* inicio;

public:
    ListaEncadeada() : inicio(nullptr) {}

    ~ListaEncadeada() {
        No* atual = inicio;
        while (atual) {
            No* temp = atual;
            atual = atual->prox;
            delete temp;
        }
    }

    void InsereFinal(T dado) {
        No* novo = new No{dado, nullptr};
        if (!inicio) {
            inicio = novo;
        } else {
            No* atual = inicio;
            while (atual->prox) {
                atual = atual->prox;
            }
            atual->prox = novo;
        }
    }

    bool Contem(T dado) const {
        No* atual = inicio;
        while (atual) {
            if (atual->dado == dado) {
                return true;
            }
            atual = atual->prox;
        }
        return false;
    }

    int Tamanho() const {
        int tamanho = 0;
        No* atual = inicio;
        while (atual) {
            tamanho++;
            atual = atual->prox;
        }
        return tamanho;
    }

    void Imprime() const {
        No* atual = inicio;
        while (atual) {
            std::cout << " " << atual->dado;
            atual = atual->prox;
        }
        std::cout << std::endl;
    }
};

#endif
