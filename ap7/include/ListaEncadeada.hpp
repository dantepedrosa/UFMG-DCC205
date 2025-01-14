#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

#include <stdexcept>
#include <iostream>

template <typename TipoItem>
class ListaEncadeada;

template <typename TipoItem>
class TipoCelula {
    friend class ListaEncadeada<TipoItem>; // Permite acesso de ListaEncadeada aos atributos privados
private:
    TipoItem item;
    TipoCelula* prox;
};

template <typename TipoItem>
class ListaEncadeada {
public:
    ListaEncadeada();
    ~ListaEncadeada();
    void InsereInicio(TipoItem valor);
    void InsereFinal(TipoItem valor);
    TipoItem RemoveInicio();
    TipoItem RemoveFinal();
    bool Vazia() const;
    int Tamanho() const;
    TipoItem& GetItem(int pos); // Retorna uma referência ao item
    void Imprime() const; // Adiciona a declaração do método Imprime
    void Limpa(); // Adiciona a declaração do método Limpa

private:
    TipoCelula<TipoItem>* primeiro;
    TipoCelula<TipoItem>* ultimo;
    int tamanho;
};

#endif // LISTAENCADEADA_HPP

