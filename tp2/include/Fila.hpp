#ifndef FILA_HPP
#define FILA_HPP


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
        TipoItem item = celulaRemovida->item;
        frente->prox = celulaRemovida->prox;
        if (frente->prox == nullptr) {
            tras = frente;
        }
        delete celulaRemovida;
        return item;
    }

    bool filaVazia() const {
        return frente == tras;
    }

    void finaliza() {
        TipoCelula<TipoItem> *p = frente->prox;
        while (p != NULL) {
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
