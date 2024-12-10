/**
 * @file Sorts.hpp
 * @brief Declaração de funções de ordenação para o tipo ApontadorIndice.
 *
 * Este arquivo contém as declarações das funções de ordenação que serão
 * utilizadas para ordenar arrays do tipo ApontadorIndice. As funções
 * implementadas incluem Insertion Sort, Shell Sort e QuickSort.
 *
 * @date 2024
 *
 * @author Dante Junqueira Pedrosa
 * @institution Universidade Federal de Minas Gerais (UFMG)
 * @course DCC205 - Estruturas de Dados
 */

#pragma once

#include <string>

/**
 * @struct ApontadorIndice
 * @brief Estrutura que representa um índice apontador.
 *
 * A estrutura ApontadorIndice contém uma chave e uma posição. A chave é uma
 * string utilizada para ordenar as entradas, enquanto a posição é um inteiro
 * que indica a posição da respectiva entrada na lista original inalterada.
 *
 * @var ApontadorIndice::chave
 * Chave utilizada para ordenar as entradas.
 *
 * @var ApontadorIndice::pos
 * Posição da respectiva entrada na lista original inalterada.
 */
struct ApontadorIndice
{

    std::string chave; // Chave, para utilizar na ordenação das entradas
    int pos;           // Posição da respectiva entrada na lista original inalterada

    bool operator>(const ApontadorIndice &other) const
    {
        return chave > other.chave;
    }

    bool operator<(const ApontadorIndice &other) const
    {
        return chave < other.chave;
    }

    bool operator==(const ApontadorIndice &other) const
    {
        return chave == other.chave;
    }

    bool operator>=(const ApontadorIndice &other) const
    {
        return chave >= other.chave;
    }

    bool operator<=(const ApontadorIndice &other) const
    {
        return chave <= other.chave;
    }
};
typedef ApontadorIndice *ApontadorIndicePtr;

/**
 * @brief Ordena um array de ApontadorIndice usando o algoritmo Insertion Sort.
 *
 * @param arr Array de ApontadorIndice a ser ordenado.
 * @param n Tamanho do array.
 */
void insertionSort(ApontadorIndice *arr[], int n);

/**
 * @brief Ordena um array de ApontadorIndice usando o algoritmo Shell Sort.
 *
 * @param arr Array de ApontadorIndice a ser ordenado.
 * @param n Tamanho do array.
 */
void shellSort(ApontadorIndice *arr[], int n);

/**
 * @brief Ordena um array de ApontadorIndice usando o algoritmo QuickSort.
 *
 * @param arr Array de ApontadorIndice a ser ordenado.
 * @param low Índice inicial.
 * @param high Índice final.
 */
void quicksort(ApontadorIndice *arr[], int n);

/**
 * @brief Função auxiliar para particionar o array no algoritmo QuickSort.
 *
 * @param arr Array de ApontadorIndice a ser particionado.
 * @param low Índice inicial.
 * @param high Índice final.
 * @param i Ponteiro para o índice i.
 * @param j Ponteiro para o índice j.
 */
void quicksort_part(ApontadorIndice *arr[], int low, int high, int *i, int *j);

/**
 * @brief Função auxiliar para ordenar o array no algoritmo QuickSort.
 *
 * @param arr Array de ApontadorIndice a ser ordenado.
 * @param low Índice inicial.
 * @param high Índice final.
 */
void quicksort_ord(ApontadorIndice *arr[], int low, int high);