#ifndef SORTS_HPP
#define SORTS_HPP

#include "ListaEncadeada.hpp"
#include "OrdInd.hpp"

/**
 * @brief Ordena um array de ApontadorIndice usando o algoritmo Insertion Sort.
 * 
 * @param arr Array de ApontadorIndice a ser ordenado.
 * @param n Tamanho do array.
 */
void insertionSort(ApontadorIndice arr[], int n);

/**
 * @brief Ordena um array de ApontadorIndice usando o algoritmo Shell Sort.
 * 
 * @param arr Array de ApontadorIndice a ser ordenado.
 * @param n Tamanho do array.
 */
void shellSort(ApontadorIndice arr[], int n);

/**
 * @brief Ordena um array de ApontadorIndice usando o algoritmo QuickSort.
 * 
 * @param arr Array de ApontadorIndice a ser ordenado.
 * @param low Índice inicial.
 * @param high Índice final.
 */
void quicksort(ApontadorIndice* arr[], int low, int high);

/**
 * @brief Função auxiliar para particionar o array no algoritmo QuickSort.
 * 
 * @param arr Array de ApontadorIndice a ser particionado.
 * @param low Índice inicial.
 * @param high Índice final.
 * @param i Ponteiro para o índice i.
 * @param j Ponteiro para o índice j.
 */
void quicksort_part(ApontadorIndice arr[], int low, int high, int *i, int *j);

/**
 * @brief Função auxiliar para ordenar o array no algoritmo QuickSort.
 * 
 * @param arr Array de ApontadorIndice a ser ordenado.
 * @param low Índice inicial.
 * @param high Índice final.
 */
void quicksort_ord(ApontadorIndice arr[], int low, int high);

/**
 * @brief Ordena um array de ApontadorIndice usando o algoritmo Bucket Sort.
 * 
 * @param arr Array de ApontadorIndice a ser ordenado.
 * @param n Tamanho do array.
 */
void bucketSort(ApontadorIndice arr[], int n);

#endif // SORTS_HPP