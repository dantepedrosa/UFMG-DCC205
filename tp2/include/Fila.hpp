#ifndef FILA_HPP
#define FILA_HPP

#include <stdexcept>

/**
 * @file Fila.hpp
 * @brief Declaração das classes TipoCelula e FilaEncadeada.
 */

template <typename TipoItem>
class TipoCelula {
public:
    TipoCelula() : prox(nullptr) {}

private:
    TipoItem item; // Item armazenado na célula
    TipoCelula *prox; // Ponteiro para a próxima célula

    template <typename T>
    friend class FilaEncadeada;
};

/**
 * @brief Classe que representa uma fila encadeada.
 */
template <typename TipoItem>
class FilaEncadeada {
public:
    FilaEncadeada() : frente(nullptr), tras(nullptr) {
        frente = new TipoCelula<TipoItem>();
        tras = frente;
    }

    ~FilaEncadeada() {
        finaliza();
        delete frente;
    }

    /**
     * @brief Enfileira um item na fila.
     * 
     * @param item Item a ser enfileirado.
     */
    void enfileira(TipoItem item) {
        TipoCelula<TipoItem>* novaCelula = new TipoCelula<TipoItem>();
        novaCelula->item = item;
        tras->prox = novaCelula;
        tras = novaCelula;
    }

    /**
     * @brief Desenfileira um item da fila.
     * 
     * @return TipoItem Item desenfileirado.
     * @throws std::runtime_error Se a fila estiver vazia.
     */
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

    /**
     * @brief Desenfileira um item da fila e retorna um ponteiro para ele.
     * 
     * @return TipoItem* Ponteiro para o item desenfileirado.
     * @throws std::runtime_error Se a fila estiver vazia.
     */
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

    /**
     * @brief Retorna o próximo item da fila sem removê-lo.
     * 
     * @return TipoItem Próximo item da fila.
     * @throws std::runtime_error Se a fila estiver vazia.
     */
    TipoItem peek() const {
        if (filaVazia()) {
            throw std::runtime_error("Fila vazia");
        }
        return frente->prox->item; // Retorna o próximo item da fila sem removê-lo
    }

    /**
     * @brief Verifica se a fila está vazia.
     * 
     * @return true Se a fila estiver vazia.
     * @return false Caso contrário.
     */
    bool filaVazia() const {
        return frente == tras;
    }

    

private:
    TipoCelula<TipoItem> *frente; // Ponteiro para a frente da fila
    TipoCelula<TipoItem> *tras; // Ponteiro para o final da fila

    /**
     * @brief Inicializa a fila encadeada.
     */
    void inicializa() {
        frente = new TipoCelula<TipoItem>();
        tras = frente;
    }

    /**
     * @brief Finaliza a fila encadeada, liberando todos os recursos.
     */
    void finaliza() {
        TipoCelula<TipoItem> *p = frente->prox;
        while (p != nullptr) {
            frente->prox = p->prox;
            delete p;
            p = frente->prox;
        }
        tras = frente;
    }
};

#endif // FILA_HPP
