#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "../include/Procedimento.hpp"
#include "../include/Paciente.hpp"
#include "../include/Tempo.hpp"

TEST_CASE("Testando a classe Procedimento") {
    Procedimento triagem("Triagem", 5, 0.2, false);

    DataHora ref(1, 1, 2025, 0.0);
    DataHora dh1(1, 1, 2025, 1.0); // 1 hora depois
    Tempo t1(dh1, ref);

    CHECK(triagem.unidadeDisponivel(t1) == true);

    int unidade = triagem.alocarUnidade(t1, 0.2);
    CHECK(unidade >= 0);
    CHECK(triagem.unidadeDisponivel(t1) == true);

    DataHora dh2(1, 1, 2025, 1.5); // 1.5 horas depois
    Tempo t2(dh2, ref);
    triagem.liberarUnidade(unidade, t2);

    CHECK(triagem.unidadeDisponivel(t2) == true);
    CHECK(triagem.calcularTempoOciosoTotal() > 0.0);
}

TEST_CASE("Testando enfileiramento e desenfileiramento na fila geral") {
    Procedimento procedimento("Procedimento Geral", 3, 0.5, false);

    DataHora ref(1, 1, 2025, 0.0);
    Tempo admissao1(DataHora(1, 1, 2025, 1.0), ref);
    Tempo admissao2(DataHora(1, 1, 2025, 2.0), ref);

    Paciente paciente1(1, false, admissao1, 0, 0, 0, 0, 0);
    Paciente paciente2(2, false, admissao2, 0, 0, 0, 0, 0);

    procedimento.enfileira(paciente1);
    procedimento.enfileira(paciente2);

    Paciente desenfileirado1 = procedimento.desenfileira();
    CHECK(desenfileirado1.getId() == 1);

    Paciente desenfileirado2 = procedimento.desenfileira();
    CHECK(desenfileirado2.getId() == 2);
}

TEST_CASE("Testando enfileiramento de pacientes com diferentes níveis de urgência e DataHora iguais") {
    Procedimento procedimento("Procedimento com Urgência", 3, 0.5, true);

    DataHora ref(1, 1, 2025, 0.0);
    Tempo admissao(DataHora(1, 1, 2025, 1.0), ref);

    Paciente paciente1(1, false, admissao, 0, 0, 0, 0, 0);
    Paciente paciente2(2, false, admissao, 0, 0, 0, 0, 0);
    Paciente paciente3(3, false, admissao, 0, 0, 0, 0, 0);

    procedimento.enfileira(paciente1, 0); // Verde
    procedimento.enfileira(paciente2, 1); // Amarelo
    procedimento.enfileira(paciente3, 2); // Vermelho

    Paciente desenfileirado1 = procedimento.desenfileira();
    CHECK(desenfileirado1.getId() == 3); // Vermelho tem prioridade

    Paciente desenfileirado2 = procedimento.desenfileira();
    CHECK(desenfileirado2.getId() == 2); // Amarelo tem prioridade

    Paciente desenfileirado3 = procedimento.desenfileira();
    CHECK(desenfileirado3.getId() == 1); // Verde tem prioridade
}

TEST_CASE("Testando enfileiramento de pacientes com diferentes níveis de urgência e DataHora diferentes") {
    Procedimento procedimento("Procedimento com Urgência", 3, 0.5, true);

    DataHora ref(1, 1, 2025, 0.0);
    Tempo admissao1(DataHora(1, 1, 2025, 1.0), ref);
    Tempo admissao2(DataHora(1, 1, 2025, 2.0), ref);
    Tempo admissao3(DataHora(1, 1, 2025, 3.0), ref);

    Paciente paciente1(1, false, admissao1, 0, 0, 0, 0, 0);
    Paciente paciente2(2, false, admissao2, 0, 0, 0, 0, 0);
    Paciente paciente3(3, false, admissao3, 0, 0, 0, 0, 0);

    procedimento.enfileira(paciente1, 0); // Verde
    procedimento.enfileira(paciente2, 1); // Amarelo
    procedimento.enfileira(paciente3, 2); // Vermelho

    Paciente desenfileirado1 = procedimento.desenfileira();
    CHECK(desenfileirado1.getId() == 3); // Vermelho tem prioridade

    Paciente desenfileirado2 = procedimento.desenfileira();
    CHECK(desenfileirado2.getId() == 2); // Amarelo tem prioridade

    Paciente desenfileirado3 = procedimento.desenfileira();
    CHECK(desenfileirado3.getId() == 1); // Verde tem prioridade
}

TEST_CASE("Testando exceção ao desenfileirar de uma fila vazia") {
    Procedimento procedimento("Procedimento Geral", 3, 0.5, false);

    CHECK_THROWS_AS(procedimento.desenfileira(), std::runtime_error);
}

TEST_CASE("Testando exceção ao alocar unidade inválida") {
    Procedimento procedimento("Procedimento Geral", 3, 0.5, false);

    DataHora ref(1, 1, 2025, 0.0);
    Tempo t1(DataHora(1, 1, 2025, 1.0), ref);

    CHECK_THROWS_AS(procedimento.alocarUnidade(t1, 0.2), std::runtime_error);
}

TEST_CASE("Testando exceção ao liberar unidade inválida") {
    Procedimento procedimento("Procedimento Geral", 3, 0.5, false);

    DataHora ref(1, 1, 2025, 0.0);
    Tempo t1(DataHora(1, 1, 2025, 1.0), ref);

    CHECK_THROWS_AS(procedimento.liberarUnidade(-1, t1), std::out_of_range);
    CHECK_THROWS_AS(procedimento.liberarUnidade(3, t1), std::out_of_range);
}

