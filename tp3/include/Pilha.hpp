#include <iostream>
#include <stdexcept>

#ifndef TIPO_CELULA_HPP
#define TIPO_CELULA_HPP

template <typename TipoItem>
class TipoCelula {
public:
    TipoCelula() : prox(nullptr) {}
    TipoItem item;
    TipoCelula* prox;
};

#endif

template <typename TipoItem>
class Pilha {
public:
    Pilha() : tamanho(0) {}
    int GetTamanho() const { return tamanho; }
    bool Vazia() const { return tamanho == 0; }
    virtual void Empilha(TipoItem item) = 0;
    virtual TipoItem Desempilha() = 0;
    virtual void Limpa() = 0;

protected:
    int tamanho;
};

template <typename TipoItem>
class PilhaEncadeada : public Pilha<TipoItem> {
public:
    PilhaEncadeada() : topo(nullptr) {}
    virtual ~PilhaEncadeada() { this->Limpa(); }

    void Empilha(TipoItem item) override {
        TipoCelula<TipoItem>* novaCelula = new TipoCelula<TipoItem>();
        novaCelula->item = item;
        novaCelula->prox = topo;
        topo = novaCelula;
        this->tamanho++;
    }

    TipoItem Desempilha() override {
        if (this->Vazia()) {
            throw std::underflow_error("Erro: Pilha vazia.");
        }
        TipoCelula<TipoItem>* celulaRemover = topo;
        TipoItem item = celulaRemover->item;
        topo = topo->prox;
        delete celulaRemover;
        this->tamanho--;
        return item;
    }

    TipoItem Topo() const {
        if (this->Vazia()) {
            throw std::underflow_error("Erro: Pilha vazia.");
        }
        return topo->item;
    }

    void Limpa() override {
        while (!this->Vazia()) {
            Desempilha();
        }
    }

    void Mostrar() const {
        TipoCelula<TipoItem>* atual = topo;
        std::cout << "Pilha: ";
        while (atual != nullptr) {
            std::cout << atual->item << " ";
            atual = atual->prox;
        }
        std::cout << std::endl;
    }

private:
    TipoCelula<TipoItem>* topo;
};
