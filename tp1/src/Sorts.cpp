#include "OrdInd.h"
#include <algorithm>

/**
 * @brief Função de ordenação usando QuickSort.
 * @param indices Vetor de índices a ser ordenado.
 * @param ordind Objeto OrdInd contendo os dados.
 * @param atributo Índice do atributo para ordenação.
 */
void quickSort(std::vector<int> &indices, OrdInd &ordind, int atributo) {
    std::sort(indices.begin(), indices.end(), [&](int i, int j) {
        return ordind.getDado(i, atributo) < ordind.getDado(j, atributo);
    });
}

/**
 * @brief Função de ordenação usando BubbleSort.
 * @param indices Vetor de índices a ser ordenado.
 * @param ordind Objeto OrdInd contendo os dados.
 * @param atributo Índice do atributo para ordenação.
 */
void bubbleSort(std::vector<int> &indices, OrdInd &ordind, int atributo) {
    for (size_t i = 0; i < indices.size() - 1; ++i) {
        for (size_t j = 0; j < indices.size() - i - 1; ++j) {
            if (ordind.getDado(indices[j], atributo) >
                ordind.getDado(indices[j + 1], atributo)) {
                std::swap(indices[j], indices[j + 1]);
            }
        }
    }
}

/**
 * @brief Função de ordenação usando SelectionSort.
 * @param indices Vetor de índices a ser ordenado.
 * @param ordind Objeto OrdInd contendo os dados.
 * @param atributo Índice do atributo para ordenação.
 */
void selectionSort(std::vector<int> &indices, OrdInd &ordind, int atributo) {
    for (size_t i = 0; i < indices.size() - 1; ++i) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < indices.size(); ++j) {
            if (ordind.getDado(indices[j], atributo) <
                ordind.getDado(indices[minIdx], atributo)) {
                minIdx = j;
            }
        }
        std::swap(indices[i], indices[minIdx]);
    }
}
