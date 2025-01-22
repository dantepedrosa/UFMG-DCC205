#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "../include/Paciente.hpp"
#include "../include/Tempo.hpp"

TEST_CASE("Testando a classe Paciente") {
    DataHora ref(21, 3, 2017, 0.0);
    DataHora admissao(21, 3, 2017, 2.0); // 2 horas depois
    Tempo tAdmissao(admissao, ref);

    Paciente p1(9600008, false, tAdmissao, 2, 5, 43, 2, 110);

    CHECK(p1.getEstado() == 2); // Estado inicial é 2 (Na fila de triagem)
    CHECK(p1.getAdmissaoHZ().getHorasDesdeReferencia() == 2.0);

    DataHora dh1(21, 3, 2017, 3.0); // 3 horas depois
    Tempo t1(dh1, ref);
    p1.atualizarEstado(3, t1);

    CHECK(p1.getEstado() == 3);
    CHECK(p1.getTempoTotalEspera() == 1.0);

    DataHora dh2(21, 3, 2017, 4.0); // 4 horas depois
    Tempo t2(dh2, ref);
    p1.atualizarEstado(4, t2);

    CHECK(p1.getEstado() == 4);
    CHECK(p1.getTempoTotalAtendimento() == 1.0);

    DataHora dh3(21, 3, 2017, 5.0); // 5 horas depois
    Tempo t3(dh3, ref);
    p1.atualizarEstado(5, t3);

    CHECK(p1.getEstado() == 5);
    CHECK(p1.getTempoTotalEspera() == 2.0);

    DataHora dh4(21, 3, 2017, 6.0); // 6 horas depois
    Tempo t4(dh4, ref);
    p1.atualizarEstado(6, t4);

    CHECK(p1.getEstado() == 6);
    CHECK(p1.getTempoTotalAtendimento() == 2.0);

    // Testando getters de procedimentos pendentes
    CHECK(p1.getNumMH() == 5);
    CHECK(p1.getNumTL() == 43);
    CHECK(p1.getNumEI() == 2);
    CHECK(p1.getNumIM() == 110);

    // Testando estatísticas
    CHECK(p1.getTempoTotalAtendimento() == 2.0);
    CHECK(p1.getTempoTotalEspera() == 2.0);
}

TEST_CASE("Testando o construtor simplificado da classe Paciente") {
    DataHora referencia(1, 1, 2025, 0.0);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";

    Paciente paciente(linha, referencia);

    CHECK(paciente.getId() == 9600008);
    CHECK(paciente.getAdmissaoHZ().getReferencia() == referencia);
    CHECK(paciente.getAdmissaoHZ().getDataHora().ano == 2017);
    CHECK(paciente.getAdmissaoHZ().getDataHora().mes == 3);
    CHECK(paciente.getAdmissaoHZ().getDataHora().dia == 21);
    CHECK(paciente.getAdmissaoHZ().getDataHora().hora == 2.0);
    CHECK(paciente.getNumMH() == 5);
    CHECK(paciente.getNumTL() == 43);
    CHECK(paciente.getNumEI() == 2);
    CHECK(paciente.getNumIM() == 110);
    CHECK(paciente.getEstado() == 2);
    CHECK(paciente.getTempoTotalAtendimento() == 0.0);
    CHECK(paciente.getTempoTotalEspera() == 0.0);
}

TEST_CASE("Testando a atualização de estado do paciente") {
    DataHora referencia(1, 1, 1970, 0.0);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";

    Paciente paciente(linha, referencia);

    DataHora dh1(21, 3, 2017, 3.0); // 1 hora depois
    Tempo t1(dh1, referencia);
    paciente.atualizarEstado(3, t1);

    CHECK(paciente.getEstado() == 3);
    CHECK(paciente.getTempoTotalEspera() == 1.0);
    CHECK(paciente.getTempoTotalAtendimento() == 0.0);

    DataHora dh2(21, 3, 2017, 4.0); // 2 horas depois
    Tempo t2(dh2, referencia);
    paciente.atualizarEstado(4, t2);

    CHECK(paciente.getEstado() == 4);
    CHECK(paciente.getTempoTotalEspera() == 1.0);
    CHECK(paciente.getTempoTotalAtendimento() == 1.0);
}

TEST_CASE("Testando a conversão de estado para string") {
    DataHora referencia(1, 1, 1970, 0.0);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";

    Paciente paciente(linha, referencia);

    CHECK(paciente.estadoParaString() == "Na fila de triagem");

    DataHora dh1(21, 3, 2017, 3.0); // 1 hora depois
    Tempo t1(dh1, referencia);
    paciente.atualizarEstado(3, t1);

    CHECK(paciente.estadoParaString() == "Sendo triado");
}
