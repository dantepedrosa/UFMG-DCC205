#pragma once

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
class Lista {
public:
    Lista() : tamanho(0) {}
    int GetTamanho() const { return tamanho; }
    bool Vazia() const { return tamanho == 0; }
    virtual void InsereInicio(TipoItem item) = 0;
    virtual void InsereFinal(TipoItem item) = 0;
    virtual TipoItem RemoveInicio() = 0;
    virtual TipoItem RemoveFinal() = 0;
    virtual void Limpa() = 0;

protected:
    int tamanho;
};

template <typename TipoItem>
class ListaEncadeada : public Lista<TipoItem> {
public:
    ListaEncadeada() {
        this->tamanho = 0;
        primeiro = nullptr;
        ultimo = nullptr;
    }

    ~ListaEncadeada() {
        Limpa();
    }

    TipoItem GetItem(int pos) const {
        TipoCelula<TipoItem>* celula = Posiciona(pos, false);
        return celula->item;
    }

    void SetItem(TipoItem item, int pos) {
        TipoCelula<TipoItem>* celula = Posiciona(pos, false);
        celula->item = item;
    }

    void InsereInicio(TipoItem item) override {
        TipoCelula<TipoItem>* novaCelula = new TipoCelula<TipoItem>();
        novaCelula->item = item;
        novaCelula->prox = primeiro;
        primeiro = novaCelula;

        if (this->tamanho == 0) {
            ultimo = novaCelula;
        }

        this->tamanho++;
    }

    void InsereFinal(TipoItem item) override {
        TipoCelula<TipoItem>* novaCelula = new TipoCelula<TipoItem>();
        novaCelula->item = item;
        novaCelula->prox = nullptr;

        if (this->Vazia()) {
            primeiro = novaCelula;
        } else {
            ultimo->prox = novaCelula;
        }

        ultimo = novaCelula;
        this->tamanho++;
    }

    void InserePosicao(TipoItem item, int pos) {
        if (pos < 0 || pos > this->tamanho) {
            throw std::out_of_range("Posição inválida.");
        }

        if (pos == 0) {
            InsereInicio(item);
        } else if (pos == this->tamanho) {
            InsereFinal(item);
        } else {
            TipoCelula<TipoItem>* anterior = Posiciona(pos, true);
            TipoCelula<TipoItem>* novaCelula = new TipoCelula<TipoItem>();
            novaCelula->item = item;
            novaCelula->prox = anterior->prox;
            anterior->prox = novaCelula;
            this->tamanho++;
        }
    }

    TipoItem RemoveInicio() override {
        if (this->Vazia()) {
            throw std::underflow_error("Erro: Lista vazia.");
        }

        TipoCelula<TipoItem>* celulaRemover = primeiro;
        TipoItem item = celulaRemover->item;
        primeiro = primeiro->prox;

        if (primeiro == nullptr) {
            ultimo = nullptr;
        }

        delete celulaRemover;
        this->tamanho--;
        return item;
    }

    TipoItem RemoveFinal() override {
        if (this->Vazia()) {
            throw std::underflow_error("Erro: Lista vazia.");
        }

        if (this->tamanho == 1) {
            return RemoveInicio();
        }

        TipoCelula<TipoItem>* penultimo = Posiciona(this->tamanho - 2, false);
        TipoItem item = ultimo->item;
        delete ultimo;
        ultimo = penultimo;
        ultimo->prox = nullptr;
        this->tamanho--;
        return item;
    }

    TipoItem RemovePosicao(int pos) {
        if (pos < 0 || pos >= this->tamanho) {
            throw std::out_of_range("Posição inválida.");
        }

        if (pos == 0) {
            return RemoveInicio();
        }

        TipoCelula<TipoItem>* anterior = Posiciona(pos, true);
        TipoCelula<TipoItem>* celulaRemover = anterior->prox;
        TipoItem item = celulaRemover->item;
        anterior->prox = celulaRemover->prox;

        if (celulaRemover == ultimo) {
            ultimo = anterior;
        }

        delete celulaRemover;
        this->tamanho--;
        return item;
    }

    TipoItem Pesquisa(const TipoItem& chave) const {
        TipoCelula<TipoItem>* atual = primeiro;
        while (atual != nullptr) {
            if (atual->item == chave) {
                return atual->item;
            }
            atual = atual->prox;
        }
        throw std::runtime_error("Item não encontrado.");
    }

    void Imprime() const {
        TipoCelula<TipoItem>* atual = primeiro;
        std::cout << "Lista: ";
        while (atual != nullptr) {
            std::cout << atual->item << " ";
            atual = atual->prox;
        }
        std::cout << std::endl;
    }

    void Limpa() override {
        while (!this->Vazia()) {
            RemoveInicio();
        }
    }

private:
    TipoCelula<TipoItem>* primeiro;
    TipoCelula<TipoItem>* ultimo;

    TipoCelula<TipoItem>* Posiciona(int pos, bool antes) const {
        if (pos < 0 || pos >= this->tamanho) {
            throw std::out_of_range("Posição inválida.");
        }

        TipoCelula<TipoItem>* atual = primeiro;
        for (int i = 0; i < (antes ? pos - 1 : pos); i++) {
            atual = atual->prox;
        }
        return atual;
    }
};
