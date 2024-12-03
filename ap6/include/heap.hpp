#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
/*  Você pode inserir os includes necessários para que sua classe funcione.
 * Alteracoes no arquivo so podem ser feitas quando explicitadas
 */

/**
 * @class Heap
 * @brief Implementa uma estrutura de dados Heap.
 *
 * A classe Heap fornece métodos para inserir e remover elementos, além de verificar se o heap está vazio.
 */
class Heap
{

public:
    /**
     * @brief Construtor da classe Heap.
     *
     * @param maxsize Tamanho máximo do heap.
     */
    Heap(int maxsize);

    /**
     * @brief Destrutor da classe Heap.
     */
    ~Heap();

    /**
     * @brief Insere um elemento no heap.
     *
     * @param x Elemento a ser inserido.
     */
    void Inserir(int x);

    /**
     * @brief Remove e retorna o elemento raiz do heap.
     *
     * @return int Elemento removido.
     */
    int Remover();

    // Retorna true caso o heap esteja vazio, false caso contrário.
    /**
     * @brief Verifica se o heap está vazio.
     *
     * @return true Se o heap estiver vazio.
     * @return false Caso contrário.
     */
    bool Vazio();

private:
    /**
     * @brief Retorna o índice do ancestral de um dado nó.
     *
     * @param posicao Índice do nó atual.
     * @return int Índice do ancestral.
     */
    int GetAncestral(int posicao);

    /**
     * @brief Retorna o índice do sucessor esquerdo de um dado nó.
     *
     * @param posicao Índice do nó atual.
     * @return int Índice do sucessor esquerdo.
     */

    int GetSucessorEsq(int posicao);

    /**
     * @brief Retorna o índice do sucessor direito de um dado nó.
     *
     * @param posicao Índice do nó atual.
     * @return int Índice do sucessor direito.
     */
    int GetSucessorDir(int posicao);

    int tamanho;    ///< Tamanho atual do heap.
    int *data;      ///< Vetor que armazena os elementos do heap.

    /* Funções necessárias para implementar o Heapify recursivo
     * Você pode apagar elas caso decida implementar o Heapify iterativo
     */
    /**
     * @brief Realiza o Heapify de baixo para cima a partir de uma dada posição.
     *
     * @param posicao Índice do nó a partir do qual o Heapify será realizado.
     */
    void HeapifyPorBaixo(int posicao);

    /**
     * @brief Realiza o Heapify de cima para baixo a partir de uma dada posição.
     *
     * @param posicao Índice do nó a partir do qual o Heapify será realizado.
     */
    void HeapifyPorCima(int posicao);
};

#endif