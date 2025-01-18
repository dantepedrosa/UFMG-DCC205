/*
O TAD fila tem por objetivo controlar os pacientes aguardando para cada procedimento
e, se for o caso, em cada prioridade. Idealmente você deve implementar um único TAD
que será instanciado múltiplas vezes, um para cada fila a ser simulada.
As operações a serem suportadas pelo TAD são as tradicionais:
1. Inicializa
2. Enfileira
3. Desenfileira
4. FilaVazia
5. Finaliza
Em termos de estatísticas, é importante registrar o tempo que um dado paciente ficou na
fila e o tamanho da fila em cada intervalo de tempo, com vistas a calcular a contenção
pelo procedimento. As estatísticas devem ser geradas quando da finalização da fila
 */
#include "../include/Fila.hpp"
#include <stdexcept>

template <typename TipoItem>
TipoCelula<TipoItem>::TipoCelula() : prox(nullptr) {}

template <typename TipoItem>
FilaEncadeada<TipoItem>::FilaEncadeada() : frente(nullptr), tras(nullptr) {}

template <typename TipoItem>
FilaEncadeada<TipoItem>::~FilaEncadeada() {
    finaliza();
}

template <typename TipoItem>
void FilaEncadeada<TipoItem>::inicializa() {
    finaliza();
    frente = tras = nullptr;
}

template <typename TipoItem>
void FilaEncadeada<TipoItem>::enfileira(TipoItem item) {
    TipoCelula<TipoItem> *novaCelula = new TipoCelula<TipoItem>();
    novaCelula->item = item;
    if (filaVazia()) {
        frente = tras = novaCelula;
    } else {
        tras->prox = novaCelula;
        tras = novaCelula;
    }
}

template <typename TipoItem>
TipoItem FilaEncadeada<TipoItem>::desenfileira() {
    if (filaVazia()) {
        throw std::runtime_error("Fila vazia");
    }
    TipoCelula<TipoItem> *celulaRemovida = frente;
    TipoItem item = celulaRemovida->item;
    frente = frente->prox;
    if (frente == nullptr) {
        tras = nullptr;
    }
    delete celulaRemovida;
    return item;
}

template <typename TipoItem>
bool FilaEncadeada<TipoItem>::filaVazia() const {
    return frente == nullptr;
}

template <typename TipoItem>
void FilaEncadeada<TipoItem>::finaliza() {
    while (!filaVazia()) {
        desenfileira();
    }
}

// Explicit template instantiation
template class FilaEncadeada<int>;
template class FilaEncadeada<float>;
template class FilaEncadeada<double>;
template class FilaEncadeada<std::string>;

