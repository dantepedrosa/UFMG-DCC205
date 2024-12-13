#include <iostream>
#include "ListaEncadeada.hpp"

int main() {
    ListaEncadeada<int> lista;

    // Teste: Inserir no início
    lista.InsereInicio(10);
    lista.InsereInicio(20);
    lista.InsereInicio(30);
    std::cout << "Lista após inserir no início: ";
    lista.Imprime(); // Esperado: 30 20 10

    // Teste: Inserir no final
    lista.InsereFinal(40);
    lista.InsereFinal(50);
    std::cout << "Lista após inserir no final: ";
    lista.Imprime(); // Esperado: 30 20 10 40 50

    // Teste: Remover do início
    int removidoInicio = lista.RemoveInicio();
    std::cout << "Elemento removido do início: " << removidoInicio << std::endl; // Esperado: 30
    std::cout << "Lista após remover do início: ";
    lista.Imprime(); // Esperado: 20 10 40 50

    // Teste: Remover do final
    int removidoFinal = lista.RemoveFinal();
    std::cout << "Elemento removido do final: " << removidoFinal << std::endl; // Esperado: 50
    std::cout << "Lista após remover do final: ";
    lista.Imprime(); // Esperado: 20 10 40

    // Teste: Verificar se a lista está vazia
    std::cout << "A lista está vazia? " << (lista.Vazia() ? "Sim" : "Não") << std::endl; // Esperado: Não

    // Teste: Obter o tamanho da lista
    std::cout << "Tamanho da lista: " << lista.Tamanho() << std::endl; // Esperado: 3

    // Teste: Limpar a lista
    lista.Limpa();
    std::cout << "Lista após limpar: ";
    lista.Imprime(); // Esperado: (vazia)
    std::cout << "A lista está vazia? " << (lista.Vazia() ? "Sim" : "Não") << std::endl; // Esperado: Sim

    return 0;
}
