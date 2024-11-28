#include "OrdInd.h"
#include "Test.h"
#include <iostream>
#include <cassert> // Para validação com assert

Test::Test() {
    printf("Iniciando Testes de Unidade da Classe OrdInd\n");
}

Test::~Test() {
    printf("Finalizando Testes de Unidade\n");
}

void Test::Print() {
    printf("Executando Testes de Unidade\n");

    // Teste 1: Inicialização da Classe
    OrdInd organizador(3, 2); // 3 registros, 2 colunas
    printf("Teste 1: Inicialização da Classe - OK\n");

    // Teste 2: Inserção e Recuperação de Dados
    organizador.setDado(0, 0, "nome1");
    organizador.setDado(0, 1, "cpf1");
    assert(strcmp(organizador.getDado(0, 0), "nome1") == 0);
    assert(strcmp(organizador.getDado(0, 1), "cpf1") == 0);
    printf("Teste 2: Inserção e Recuperação de Dados - OK\n");

    // Teste 3: Criação de Índices
    organizador.criaIndice(0); // Índice para a coluna 0 (nome)
    assert(organizador.getDado(organizador.getIndicesNome()[0], 0) != nullptr);
    printf("Teste 3: Criação de Índices - OK\n");

    // Teste 4: Ordenação de Índices
    organizador.setDado(1, 0, "nome3");
    organizador.setDado(2, 0, "nome2");
    organizador.ordenaIndice(0);
    assert(strcmp(organizador.getDado(organizador.getIndicesNome()[0], 0), "nome1") == 0);
    assert(strcmp(organizador.getDado(organizador.getIndicesNome()[1], 0), "nome2") == 0);
    assert(strcmp(organizador.getDado(organizador.getIndicesNome()[2], 0), "nome3") == 0);
    printf("Teste 4: Ordenação de Índices - OK\n");

    // Teste 5: Acesso Fora de Limite
    try {
        organizador.getDado(10, 10); // Índices inválidos
        assert(false); // Deve lançar uma exceção
    } catch (const std::out_of_range &) {
        printf("Teste 5: Acesso Fora de Limite - OK\n");
    }

    printf("Todos os Testes de Unidade Foram Bem-Sucedidos\n");
}
