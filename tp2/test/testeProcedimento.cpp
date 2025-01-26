#include "../include/doctest.hpp"
#include "../include/Procedimento.hpp"
#include "../include/Paciente.hpp"
#include "../include/Tempo.hpp"

TEST_CASE("Testando o construtor da classe Procedimento") {
    Procedimento procedimento(10, 30.0, true);

    CHECK(procedimento.getNumUnidades() == 10);
    CHECK(procedimento.getTempoAtendimentoMedio() == 30.0);
    CHECK(procedimento.unidadeDisponivel() == true);
}

TEST_CASE("Testando a alocação e liberação de unidades") {
    Procedimento procedimento(2, 30.0, true);

    CHECK(procedimento.unidadeDisponivel() == true);
    procedimento.alocarUnidade(0.0);
    CHECK(procedimento.unidadeDisponivel() == true);
    procedimento.alocarUnidade(0.0);
    CHECK(procedimento.unidadeDisponivel() == false);

    procedimento.liberarUnidade(30.0);
    CHECK(procedimento.unidadeDisponivel() == true);
}

TEST_CASE("Testando a enfileiramento e desenfileiramento de pacientes") {
    Procedimento procedimento(2, 30.0, true);
    DataHora referencia(1, 1, 2000, 0.0);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";
    Paciente paciente(linha, referencia);

    procedimento.enfileira(paciente, 1);
    CHECK(procedimento.filasVazias() == false);

    Paciente* desenfileirado = procedimento.desenfileira();
    CHECK(desenfileirado->getId() == "0009600008");
    CHECK(procedimento.filasVazias() == true);
}

TEST_CASE("Testando a função calcularTempoOciosoTotal") {
    Procedimento procedimento(2, 30.0, true);

    procedimento.alocarUnidade(0.0);
    procedimento.alocarUnidade(0.0);
    CHECK(procedimento.calcularTempoOciosoTotal() == 60.0);

    procedimento.liberarUnidade(30.0);
    CHECK(procedimento.calcularTempoOciosoTotal() == 30.0);
}

TEST_CASE("Testando erros de alocação") {
    Procedimento procedimento(1, 30.0, true);

    procedimento.alocarUnidade(0.0);
    CHECK_THROWS_AS(procedimento.alocarUnidade(0.0), std::runtime_error);
}

TEST_CASE("Testando erros de liberação"){
    Procedimento procedimento(2, 30.0, true);

    CHECK_THROWS_AS(procedimento.liberarUnidade(30.0), std::runtime_error);
}

TEST_CASE("Testando erros de enfileiramento e desenfileiramento de pacientes") {
    Procedimento procedimento(2, 30.0, true);
    DataHora referencia(1, 1, 2000, 0.0);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";
    Paciente paciente(linha, referencia);

    CHECK_THROWS_AS(procedimento.enfileira(paciente, 3), std::invalid_argument);

    CHECK_THROWS_AS(procedimento.desenfileira(), std::runtime_error);
}
