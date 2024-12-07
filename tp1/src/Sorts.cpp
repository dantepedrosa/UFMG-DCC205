#include <algorithm>
#include "Sorts.hpp"
//#include "ListaEncadeada.hpp"


void quicksort_part(ApontadorIndice* arr[], int low, int high, int *i, int *j)
{
    *i = low;
    *j = high;

    ApontadorIndice* pivot = arr[(high + low) / 2]; // Pivot utilizado como metade do tamanho do vetor

    do
    {
        while (arr[*i] < pivot)
            (*i)++;
        while (arr[*j] > pivot)
            (*j)--;
        if (*i <= *j)
        {
            std::swap(arr[*i], arr[*j]);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void quicksort_ord(ApontadorIndice* arr[], int low, int high)
{

    int i;
    int j;
    quicksort_part(arr, low, high, &i, &j);

    if (low < j)
        quicksort_ord(arr, low, j);
    if (high > i)
        quicksort_ord(arr, i, high);
}

void quicksort(ApontadorIndice* arr[], int n)
{
    quicksort_ord(arr, 0, n - 1);
}

void shellSort(ApontadorIndice* arr[], int n)
{
    int gap;
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            ApontadorIndice* temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void insertionSort(ApontadorIndice* arr[], int n)
{
    
    int i, j;
    ApontadorIndice* aux;

    for (i = 2; i <= n; i++)
    {
        aux = arr[i];
        j = i - 1;
        arr[0] = aux;   // Sentinela: Evita a verificação de j > 0

        while (aux < arr[j])
        {
            arr[j + 1] = arr[j];    // move o elemento para frente
            j--;
        }
        arr[j + 1] = aux;
    }
    
}

/* TODO - Corrigir bucketsort

void bucketSort(ApontadorIndice arr[], int n)
{
    if (n <= 0)
        return;

    // Create 36 buckets
    ListaEncadeada<ApontadorIndice> buckets[36];

    // Determine the range of the initial digit
    for (int i = 0; i < n; i++) {
        int bucketIndex = arr[i].chave % 36;
        buckets[bucketIndex].insereFinal(arr[i]);
    }

    // Para cada bucket, ordenar
    for (int i = 0; i < 36; i++) {
        int bucketSize = buckets[i].tamanho();
        if (bucketSize > 0) {
            ApontadorIndice* bucketArray = new ApontadorIndice[bucketSize];
            Node* current = buckets[i].inicio();
            for (int j = 0; j < bucketSize; j++) {
                bucketArray[j] = current->data;
                current = current->next;
            }
            insertionSort(bucketArray, bucketSize);
            current = buckets[i].inicio();
            for (int j = 0; j < bucketSize; j++) {
                current->data = bucketArray[j];
                current = current->next;
            }
            delete[] bucketArray;
        }
    }

    // Concatenar
    int index = 0;
    for (int i = 0; i < 36; i++) {
        Node* current = buckets[i].inicio();
        while (current != nullptr) {
            arr[index++] = current->data;
            current = current->next;
        }
    }
}

*/
