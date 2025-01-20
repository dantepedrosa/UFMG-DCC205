#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "../include/Fila.hpp"

TEST_CASE("Testando a inicialização da fila") {
    FilaEncadeada<int> fila;
    fila.inicializa();
    CHECK(fila.filaVazia() == true);
}

TEST_CASE("Testando a enfileiração de elementos") {
    FilaEncadeada<int> fila;
    fila.inicializa();
    fila.enfileira(10);
    CHECK(fila.filaVazia() == false);
    fila.enfileira(20);
    fila.enfileira(30);
    CHECK(fila.filaVazia() == false);
}

TEST_CASE("Testando a desenfileiração de elementos") {
    FilaEncadeada<int> fila;
    fila.inicializa();
    fila.enfileira(10);
    fila.enfileira(20);
    fila.enfileira(30);
    CHECK(fila.desenfileira() == 10);
    CHECK(fila.desenfileira() == 20);
    CHECK(fila.desenfileira() == 30);
    CHECK(fila.filaVazia() == true);
}

TEST_CASE("Testando a fila vazia") {
    FilaEncadeada<int> fila;
    fila.inicializa();
    CHECK(fila.filaVazia() == true);
    fila.enfileira(10);
    CHECK(fila.filaVazia() == false);
    fila.desenfileira();
    CHECK(fila.filaVazia() == true);
}

TEST_CASE("Testando a finalização da fila") {
    FilaEncadeada<int> fila;
    fila.inicializa();
    fila.enfileira(10);
    fila.enfileira(20);
    fila.enfileira(30);
    fila.finaliza();
    CHECK(fila.filaVazia() == true);
}

/*
TEST_CASE("Testando exceção ao desenfileirar de uma fila vazia") {
    FilaEncadeada<int> fila;
    fila.inicializa();
    CHECK_THROWS_AS(fila.desenfileira(), std::runtime_error);
}
*/