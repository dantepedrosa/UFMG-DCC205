/**
 * @file ListaEncadeada.hpp
 * @brief Declaração da classe ListaEncadeada para manipulação de listas encadeadas.
 * 
 * Este arquivo contém a definição da classe template ListaEncadeada e TipoCelula, que implementam
 * respectivamente uma lista encadeada com várias operações para inserção e o formato de calula 
 * usado pela lista, com funções como remoção, pesquisa e impressão de itens.
 */

#pragma once

/**
 * @class TipoCelula
 * @brief Classe que representa uma célula de uma lista encadeada.
 * 
 * @tparam TipoItem Tipo do item armazenado na célula.
 */
template <typename TipoItem>
class TipoCelula
{
public:
/**
 * @brief Construtor padrão da classe TipoCelula.
 */
    TipoCelula();

private:
    TipoItem item;                  // Item armazenado na célula.
    TipoCelula *prox;               // Ponteiro para a próxima célula na lista encadeada.

    friend class ListaEncadeada;    // Permite acesso de ListaEncadeada aos atributos privados
};

/**
 * @file ListaEncadeada.hpp
 * @brief Declaração da classe ListaEncadeada para manipulação de listas encadeadas.
 * 
 * Este arquivo contém a definição da classe template ListaEncadeada, que implementa
 * uma lista encadeada com várias operações para inserção, remoção, pesquisa e impressão
 * de itens.
 */

/**
 * @class ListaEncadeada
 * @brief Classe template para manipulação de listas encadeadas.
 * 
 * @tparam TipoItem Tipo dos itens armazenados na lista.
 */
template <typename TipoItem>
class ListaEncadeada
{
public:

    /**
     * @brief Construtor padrão da classe ListaEncadeada.
     */
    ListaEncadeada();

    /**
     * @brief Destrutor da classe ListaEncadeada.
     */
    ~ListaEncadeada();

    /**
     * @brief Obtém o item na posição especificada.
     * 
     * @param pos Posição do item a ser obtido.
     * @return TipoItem Item na posição especificada.
     */
    TipoItem GetItem(int pos);

    /**
     * @brief Define o item na posição especificada.
     * 
     * @param item Item a ser definido.
     * @param pos Posição onde o item será definido.
     */
    void SetItem(TipoItem item, int pos);

    /**
     * @brief Insere um item no início da lista.
     * 
     * @param item Item a ser inserido.
     */
    void InsereInicio(TipoItem item);

    /**
     * @brief Insere um item no final da lista.
     * 
     * @param item Item a ser inserido.
     */
    void InsereFinal(TipoItem item);

    /**
     * @brief Insere um item na posição especificada.
     * 
     * @param item Item a ser inserido.
     * @param pos Posição onde o item será inserido.
     */
    void InserePosicao(TipoItem item, int pos);

    /**
     * @brief Remove e retorna o item do início da lista.
     * 
     * @return TipoItem Item removido do início da lista.
     */
    TipoItem RemoveInicio();

    /**
     * @brief Remove e retorna o item do final da lista.
     * 
     * @return TipoItem Item removido do final da lista.
     */
    TipoItem RemoveFinal();

    /**
     * @brief Remove e retorna o item na posição especificada.
     * 
     * @param pos Posição do item a ser removido.
     * @return TipoItem Item removido da posição especificada.
     */
    TipoItem RemovePosicao(int pos);

    /**
     * @brief Pesquisa um item na lista com base na chave especificada.
     * 
     * @param c Chave do item a ser pesquisado.
     * @return TipoItem Item encontrado com a chave especificada.
     */
    TipoItem Pesquisa(TipoChave c);

    /**
     * @brief Verifica se a lista encadeada está vazia.
     * 
     * @return true Se a lista estiver vazia.
     * @return false Se a lista não estiver vazia.
     */
    bool Vazia();

    /**
     * @brief Returns the size of the linked list.
     * 
     * This function returns the number of elements currently stored in the linked list.
     * 
     * @return int The size of the linked list.
     */
    int Tamanho();

    /**
     * @brief Imprime todos os itens da lista.
     */
    void Imprime();

    /**
     * @brief Remove todos os itens da lista.
     */
    void Limpa();

private:

    TipoCelula *primeiro;       // Ponteiro para a primeira célula da lista.
    TipoCelula *ultimo;         // Ponteiro para a última célula da lista.
    int tamanho;                // Tamanho da lista

    /**
     * @brief Posiciona o ponteiro na posição especificada.
     * 
     * @param pos Posição onde o ponteiro será posicionado.
     * @param antes Indica se o ponteiro deve ser posicionado antes da posição especificada.
     * @return TipoCelula* Ponteiro para a célula na posição especificada.
     */
    TipoCelula *Posiciona(int pos, bool antes);
};

template <typename TipoItem>
TipoItem ListaEncadeada<TipoItem>::GetItem(int pos) {
    TipoCelula<TipoItem>* atual = primeiro;
    for (int i = 0; i < pos; i++) {
        atual = atual->prox;
    }
    return atual->item;
}
