#include "heap.hpp"
#include <iostream>

/**
 * @brief Programa principal que lê uma quantidade de elementos, insere-os em um heap e os remove em ordem.
 * 
 * O programa realiza as seguintes etapas:
 * 1. Lê um número inteiro n que representa a quantidade de elementos.
 * 2. Cria um objeto Heap com capacidade para n elementos.
 * 3. Lê n elementos e os insere no heap.
 * 4. Remove e imprime os elementos do heap até que ele esteja vazio.
 * 
 * @return int Código de saída do programa.
 */
int main() {
    int n;
    std::cin >> n;

    Heap heap(n);

    for (int i = 0; i < n; ++i) {
        int element;
        std::cin >> element;
        heap.Inserir(element);
    }

    while (!heap.Vazio()) {
        std::cout << heap.Remover() << " ";
    }
    std::cout << std::endl;

    return 0;
}

