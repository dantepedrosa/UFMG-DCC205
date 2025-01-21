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


TEST_CASE("Testando a classe Procedimento com urgência") {
    Procedimento procedimento("Teste", 3, 30.0, true);

    DataHora ref(1, 1, 2025, 0.0);
    DataHora dh1(1, 1, 2025, 1.0); // 1 hora depois
    Tempo tAdmissao(dh1, ref);
    Paciente p1(9600008, false, tAdmissao, 2, 5, 43, 2, 110);
    Paciente p2(9600009, false, tAdmissao, 2, 5, 43, 2, 110);
    Paciente p3(9600010, false, tAdmissao, 2, 5, 43, 2, 110);

    std::cout << "Enfileirando pacientes..." << std::endl;
    procedimento.enfileira(p1, 0);
    procedimento.enfileira(p2, 1);
    procedimento.enfileira(p3, 2);

    std::cout << "Desenfileirando pacientes..." << std::endl;
    CHECK(procedimento.desenfileira().getId() == 9600010);
    CHECK(procedimento.desenfileira().getId() == 9600009);
    CHECK(procedimento.desenfileira().getId() == 9600008);
}
/*
TEST_CASE("Testando a classe Procedimento sem urgência") {
    Procedimento procedimento("Teste", 3, 30.0, false);

    DataHora referencia(1, 1, 2023, 0.0);
    Tempo tempoInicial(referencia, referencia);
    Paciente paciente1(1, false, tempoInicial, 0, 1, 1, 1, 1);
    Paciente paciente2(2, false, tempoInicial, 1, 1, 1, 1, 1);

    std::cout << "Enfileirando pacientes..." << std::endl;
    procedimento.enfileira(paciente1);
    procedimento.enfileira(paciente2);

    std::cout << "Desenfileirando pacientes..." << std::endl;
    CHECK(procedimento.desenfileira().getId() == 1);
    CHECK(procedimento.desenfileira().getId() == 2);
}
*/