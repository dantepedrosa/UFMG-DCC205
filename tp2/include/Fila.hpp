#ifndef FILA_HPP
#define FILA_HPP

#include <stdexcept>

template <typename TipoItem>
class TipoCelula {
public:
    TipoCelula() : prox(nullptr) {}

private:
    TipoItem item;
    TipoCelula *prox;

    template <typename T>
    friend class FilaEncadeada;
};

template <typename TipoItem>
class FilaEncadeada {
public:
    FilaEncadeada() : frente(nullptr), tras(nullptr) {}

    ~FilaEncadeada() {
        finaliza();
        delete frente;
    }

    void inicializa() {
        frente = new TipoCelula<TipoItem>();
        tras = frente;
    }

    void enfileira(TipoItem item) {
        TipoCelula<TipoItem> *novaCelula = new TipoCelula<TipoItem>();
        novaCelula->item = item;
        tras->prox = novaCelula;
        tras = novaCelula;
    }

    TipoItem desenfileira() {
        if (filaVazia()) {
            throw std::runtime_error("Fila vazia");
        }
        TipoCelula<TipoItem> *celulaRemovida = frente->prox;
        TipoItem item = celulaRemovida->item; // Copia o objeto para retorno
        frente->prox = celulaRemovida->prox;
        if (frente->prox == nullptr) {
            tras = frente;
        }
        delete celulaRemovida; // Libera a célula removida
        return item;          // Retorna o objeto copiado
    }

    TipoItem* desenfileiraPonteiro() {
        if (filaVazia()) {
            throw std::runtime_error("Fila vazia");
        }
        TipoCelula<TipoItem> *celulaRemovida = frente->prox;
        TipoItem *item = new TipoItem(celulaRemovida->item); // Aloca o objeto dinamicamente
        frente->prox = celulaRemovida->prox;
        if (frente->prox == nullptr) {
            tras = frente;
        }
        delete celulaRemovida; // Libera a célula removida
        return item;           // Retorna um ponteiro para o objeto
    }

    TipoItem peek() const {
        if (filaVazia()) {
            throw std::runtime_error("Fila vazia");
        }
        return frente->prox->item; // Retorna o próximo item da fila sem removê-lo
    }

    bool filaVazia() const {
        return frente == tras;
    }

    void finaliza() {
        TipoCelula<TipoItem> *p = frente->prox;
        while (p != nullptr) {
            frente->prox = p->prox;
            delete p;
            p = frente->prox;
        }
        tras = frente;
    }

private:
    TipoCelula<TipoItem> *frente;
    TipoCelula<TipoItem> *tras;
};

#endif // FILA_HPP
