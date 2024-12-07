/*

#include "ListaEncadeada.hpp"


template <class TipoItem>
ListaEncadeada<TipoItem>::ListaEncadeada() 
{
    primeiro = new TipoCelula<TipoItem>;
    ultimo = primeiro;
}


template <class TipoItem>
ListaEncadeada<TipoItem>::~ListaEncadeada() 
{
    Limpa();
    delete primeiro;
}


template <class TipoItem>
TipoItem ListaEncadeada<TipoItem>::GetItem(int pos)
{
    TipoCelula<TipoItem> *p;

    p = Posiciona(pos);
    return p->item;
}


template <class TipoItem>
void ListaEncadeada<TipoItem>::SetItem(TipoItem item, int pos) 
{
    TipoCelula<TipoItem> *p;

    p = Posiciona(pos);
    p->item = item;
}


template <class TipoItem>
void ListaEncadeada<TipoItem>::InsereInicio(TipoItem item)
{
    TipoCelula<TipoItem> *nova;
    nova->item = item;
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    tamanho++;
}


template <class TipoItem>
void ListaEncadeada<TipoItem>::InsereFinal(TipoItem item) 
{
    TipoCelula<TipoItem> *nova;
    nova = new TipoCelula<TipoItem>();
    nova->item = item;
    ultimo->prox = nova;
    ultimo = nova;
    tamanho++;
}


template <class TipoItem>
void ListaEncadeada<TipoItem>::InserePosicao(TipoItem item, int pos) 
{
    TipoCelula<TipoItem> *nova, *p;

    p = Posiciona(pos, true);
    nova = new TipoCelula<TipoItem>();
    nova->item = item;
    nova->prox = p->prox;
    p->prox = nova;
    tamanho++;
}


template <class TipoItem>
bool ListaEncadeada<TipoItem>::Troca(int pos1, int pos2)
{
    if (pos1 < 0 || pos1 >= tamanho || pos2 < 0 || pos2 >= tamanho) {
        return false;   // Posição inválida
    }

    if (pos1 == pos2) {
        return true;    // Não há o que trocar
    }

    TipoCelula<TipoItem> *p1 = Posiciona(pos1);
    TipoCelula<TipoItem> *p2 = Posiciona(pos2);

    TipoItem temp = p1->item;
    p1->item = p2->item;
    p2->item = temp;

    return true;
}

template <class TipoItem>
TipoItem ListaEncadeada<TipoItem>::RemoveInicio()
{
    // TODO: Implement RemoveInicio
}

template <class TipoItem>
TipoItem ListaEncadeada<TipoItem>::RemoveFinal() 
{
    // TODO: Implement RemoveFinal
}

template <class TipoItem>
TipoItem ListaEncadeada<TipoItem>::RemovePosicao(int pos)
{
    // TODO: Implement RemovePosicao
}

template <class TipoItem>
void ListaEncadeada<TipoItem>::Imprime() 
{
    // TODO: Implement Imprime
}

template <class TipoItem>
void ListaEncadeada<TipoItem>::Limpa() 
{
    // TODO: Implement Limpa
}

template <class TipoItem>
TipoCelula<TipoItem>* ListaEncadeada<TipoItem>::Posiciona(int pos, bool antes=false) 
{
    TipoCelula<TipoItem> *p;
    int i;

    if (pos < 0 || pos > tamanho)
        throw std::invalid_argument("Posição inválida");

    p = primeiro;
    for (i = 0; i < pos; i++)
        p = p->prox;

    if (antes)
        p = p->prox;

    return p;

}

*/