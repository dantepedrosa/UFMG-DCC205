#include "OrdInd.h"
#include <cstring> // Para strcmp
#include <utility> // Para std::swap

// QuickSort
void quickSort(Vetor &indices, int low, int high, int atribid, const Matriz &dados) {
    if (low < high) {
        int pi = partition(indices, low, high, atribid, dados);
        quickSort(indices, low, pi - 1, atribid, dados);
        quickSort(indices, pi + 1, high, atribid, dados);
    }
}

int partition(Vetor &indices, int low, int high, int atribid, const Matriz &dados) {
    const char *pivot = dados.get(indices[high], atribid);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(dados.get(indices[j], atribid), pivot) < 0) {
            i++;
            std::swap(indices[i], indices[j]);
        }
    }
    std::swap(indices[i + 1], indices[high]);
    return i + 1;
}

// BubbleSort
void bubbleSort(Vetor &indices, int atribid, const Matriz &dados) {
    for (int i = 0; i < indices.size() - 1; i++) {
        for (int j = 0; j < indices.size() - i - 1; j++) {
            if (strcmp(dados.get(indices[j], atribid), dados.get(indices[j + 1], atribid)) > 0) {
                std::swap(indices[j], indices[j + 1]);
            }
        }
    }
}

// SelectionSort
void selectionSort(Vetor &indices, int atribid, const Matriz &dados) {
    for (int i = 0; i < indices.size() - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < indices.size(); j++) {
            if (strcmp(dados.get(indices[j], atribid), dados.get(indices[minIdx], atribid)) < 0) {
                minIdx = j;
            }
        }
        std::swap(indices[i], indices[minIdx]);
    }
}
