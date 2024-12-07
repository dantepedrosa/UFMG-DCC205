#include <algorithm>
#include "OrdInd.hpp"

/**
 * @brief Implementação do algoritmo de ordenação QuickSort
 *
 * @param arr Array a ser ordenado
 * @param low Índice inicial
 * @param high Índice final
 */

void quicksort(ApontadorIndice arr[], int low, int high);

void quicksort_ord(ApontadorIndice arr[], int low, int high);

void quicksort_part(ApontadorIndice arr[], int low, int high, int *i, int *j);

/**
 * @brief Implementação do algoritmo de ordenação Shell Sort
 *
 * @param arr Array a ser ordenado
 * @param n Tamanho do array
 */

void shellSort(ApontadorIndice arr[], int n);

/**
 * @brief Implementação do algoritmo de ordenação Insertion Sort
 *
 * @param arr Array a ser ordenado
 * @param n Tamanho do array
 */

void insertionSort(ApontadorIndice arr[], int n);

/**
 * @brief Implementação do algoritmo de ordenação Bucket Sort
 *
 * @param arr Array a ser ordenado
 * @param n Tamanho do array
 */

void bucketSort(ApontadorIndice arr[], int n);

//=============================================================================

void quicksort_part(ApontadorIndice arr[], int low, int high, int *i, int *j)
{
    *i = low;
    *j = high;

    ApontadorIndice pivot = arr[(high + low) / 2]; // Pivot utilizado como metade do tamanho do vetor

    do
    {
        while (arr[*i].chave < pivot.chave)
            (*i)++;
        while (arr[*j].chave > pivot.chave)
            (*j)--;
        if (*i <= *j)
        {
            std::swap(arr[*i], arr[*j]);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}


void quicksort_ord(ApontadorIndice arr[], int low, int high)
{

    int i;
    int j;
    quicksort_part(arr, low, high, &i, &j);

    if (low < j)
        quicksort_ord(arr, low, j);
    if (high > i)
        quicksort_ord(arr, i, high);
}


void quicksort(ApontadorIndice arr[], int n)
{
    quicksort_ord(arr, 0, n - 1);
}


void shellSort(ApontadorIndice arr[], int n)
{
    int gap;
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            ApontadorIndice temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].chave > temp.chave; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}


void insertionSort(ApontadorIndice arr[], int n)
{
    // TODO: Implementar Insertion Sort
}

void bucketSort(ApontadorIndice arr[], int n)
{
    // TODO: Implementar Bucket Sort
}
