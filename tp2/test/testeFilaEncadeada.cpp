#include "../include/doctest.hpp"
#include "../include/Fila.hpp"

TEST_CASE("Testando o construtor da classe FilaEncadeada") {
    FilaEncadeada<int> fila;
    CHECK(fila.filaVazia() == true);
}

TEST_CASE("Testando a função enfileira e desenfileira") {
    FilaEncadeada<int> fila;
    fila.enfileira(1);
    fila.enfileira(2);
    fila.enfileira(3);

    CHECK(fila.filaVazia() == false);
    CHECK(fila.desenfileira() == 1);
    CHECK(fila.desenfileira() == 2);
    CHECK(fila.desenfileira() == 3);
    CHECK(fila.filaVazia() == true);
}

TEST_CASE("Testando a função desenfileiraPonteiro") {
    FilaEncadeada<int> fila;
    fila.enfileira(1);
    fila.enfileira(2);

    int* item = fila.desenfileiraPonteiro();
    CHECK(*item == 1);
    delete item;

    item = fila.desenfileiraPonteiro();
    CHECK(*item == 2);
    delete item;
}

TEST_CASE("Testando a função peek") {
    FilaEncadeada<int> fila;
    fila.enfileira(1);
    fila.enfileira(2);

    CHECK(fila.peek() == 1);
    fila.desenfileira();
    CHECK(fila.peek() == 2);
}