#include <iostream>
#include <stdexcept>

typedef int TipoItem;

class TipoCelula {
public:
    TipoCelula() {
        item = -1;
        prox = nullptr;
    }

private:
    TipoItem item;
    TipoCelula* prox;

    friend class PilhaEncadeada;
};

class Pilha {
public:
    Pilha() { tamanho = 0; }
    int GetTamanho() { return tamanho; }
    bool Vazia() { return tamanho == 0; }
    virtual void Empilha(TipoItem item) = 0;
    virtual TipoItem Desempilha() = 0;
    virtual void Limpa() = 0;

protected:
    int tamanho;
};

class PilhaEncadeada : public Pilha {
public:
    PilhaEncadeada() {
        topo = nullptr;
    }

    virtual ~PilhaEncadeada() {
        Limpa();
    }

    void Empilha(TipoItem item) override {
        TipoCelula* novaCelula = new TipoCelula();
        novaCelula->item = item;
        novaCelula->prox = topo;
        topo = novaCelula;
        tamanho++;
    }

    TipoItem Desempilha() override {
        if (Vazia()) {
            throw std::underflow_error("Erro: Pilha vazia.");
        }
        TipoCelula* celulaRemover = topo;
        TipoItem item = celulaRemover->item;
        topo = topo->prox;
        delete celulaRemover;
        tamanho--;
        return item;
    }

    void Limpa() override {
        while (!Vazia()) {
            Desempilha();
        }
    }

    void Mostrar() {
        TipoCelula* atual = topo;
        std::cout << "Pilha: ";
        while (atual != nullptr) {
            std::cout << atual->item << " ";
            atual = atual->prox;
        }
        std::cout << std::endl;
    }

private:
    TipoCelula* topo;
};