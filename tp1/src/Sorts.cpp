/**
 * @file Sorts.cpp
 * @brief Implementação dos algoritmos de ordenação utilizados pela classe OrdInd.
 *
 * Este arquivo contém as implementações dos algoritmos de ordenação QuickSort, ShellSort e InsertionSort.
 * Para mais informações sobre as funções, consulte o arquivo include/Sorts.hpp.
 *
 * @author Dante Junqueira Pedrosa
 * @institution Universidade Federal de Minas Gerais (UFMG)
 * @course DCC205 - Estruturas de Dados
 */

#include <algorithm>
#include "Sorts.hpp"

void quicksort_part(ApontadorIndice *arr[], int low, int high, int *i, int *j)
{
    *i = low;
    *j = high;

    ApontadorIndice *pivot = arr[(high + low) / 2]; // Pivot utilizado como metade do tamanho do vetor

    do
    {
        while (*arr[*i] < *pivot)
            (*i)++;
        while (*arr[*j] > *pivot)
            (*j)--;
        if (*i <= *j)
        {
            std::swap(arr[*i], arr[*j]);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void quicksort_ord(ApontadorIndice *arr[], int low, int high)
{

    int i;
    int j;
    quicksort_part(arr, low, high, &i, &j);

    if (low < j)
        quicksort_ord(arr, low, j); // Chama a ordenação para a porção esquerda
    if (high > i)
        quicksort_ord(arr, i, high); // Chama a ordenação para a porção direita
}

void quicksort(ApontadorIndice *arr[], int n)
{
    quicksort_ord(arr, 0, n - 1);
}

void shellSort(ApontadorIndice *arr[], int n)
{
    int gap;
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            ApontadorIndice *temp = arr[i];
            int j;
            for (j = i; j >= gap && *arr[j - gap] > *temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void insertionSort(ApontadorIndice *arr[], int n)
{

    int i, j;
    ApontadorIndice *aux;

    for (i = 1; i < n; i++)
    {
        aux = arr[i]; // Separa o elemento atual
        j = i - 1;

        while (j >= 0 && *aux < *arr[j])
        {
            arr[j + 1] = arr[j]; // move o elemento para frente
            j--;
        }
        arr[j + 1] = aux; // Insere na posição liberada
    }
}