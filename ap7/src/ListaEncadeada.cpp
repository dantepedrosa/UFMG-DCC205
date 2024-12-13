#include "ListaEncadeada.hpp"

// Construtor
template <typename TipoItem>
ListaEncadeada<TipoItem>::ListaEncadeada() : primeiro(nullptr), ultimo(nullptr), tamanho(0) {}

// Destrutor
template <typename TipoItem>
ListaEncadeada<TipoItem>::~ListaEncadeada() {
    Limpa();
}

// Adicionar um elemento no início da lista
template <typename TipoItem>
void ListaEncadeada<TipoItem>::InsereInicio(TipoItem valor) {
    TipoCelula<TipoItem>* novo = new TipoCelula<TipoItem>();
    novo->item = valor;
    novo->prox = primeiro;
    primeiro = novo;
    if (tamanho == 0) {
        ultimo = novo;
    }
    tamanho++;
}

// Adicionar um elemento no final da lista
template <typename TipoItem>
void ListaEncadeada<TipoItem>::InsereFinal(TipoItem valor) {
    TipoCelula<TipoItem>* novo = new TipoCelula<TipoItem>();
    novo->item = valor;
    novo->prox = nullptr;
    if (tamanho == 0) {
        primeiro = novo;
    } else {
        ultimo->prox = novo;
    }
    ultimo = novo;
    tamanho++;
}

// Remover um elemento do início da lista
template <typename TipoItem>
TipoItem ListaEncadeada<TipoItem>::RemoveInicio() {
    if (Vazia()) {
        throw std::runtime_error("Lista vazia");
    }
    TipoCelula<TipoItem>* temp = primeiro;
    TipoItem valor = temp->item;
    primeiro = primeiro->prox;
    delete temp;
    tamanho--;
    if (tamanho == 0) {
        ultimo = nullptr;
    }
    return valor;
}

// Remover um elemento do final da lista
template <typename TipoItem>
TipoItem ListaEncadeada<TipoItem>::RemoveFinal() {
    if (Vazia()) {
        throw std::runtime_error("Lista vazia");
    }
    TipoCelula<TipoItem>* temp = primeiro;
    if (tamanho == 1) {
        primeiro = ultimo = nullptr;
    } else {
        while (temp->prox != ultimo) {
            temp = temp->prox;
        }
        temp->prox = nullptr;
        delete ultimo;
        ultimo = temp;
    }
    tamanho--;
    return temp->item;
}

// Verificar se a lista está vazia
template <typename TipoItem>
bool ListaEncadeada<TipoItem>::Vazia()  {
    return tamanho == 0;
}

// Obter o tamanho da lista
template <typename TipoItem>
int ListaEncadeada<TipoItem>::Tamanho()  {
    return tamanho;
}

// Imprimir a lista
template <typename TipoItem>
void ListaEncadeada<TipoItem>::Imprime()  {
    TipoCelula<TipoItem>* temp = primeiro;
    while (temp != nullptr) {
        std::cout << temp->item << " ";
        temp = temp->prox;
    }
    std::cout << std::endl;
}

// Limpa a lista
template <typename TipoItem>
void ListaEncadeada<TipoItem>::Limpa() {
    while (!Vazia()) {
        RemoveInicio();
    }
}
