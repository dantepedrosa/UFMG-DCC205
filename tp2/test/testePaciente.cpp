#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "../include/Paciente.hpp"
#include "../include/Tempo.hpp"
#include "../include/Procedimento.hpp"

TEST_CASE("Testando o construtor da classe Paciente") {
    DataHora referencia(1, 1, 2000, 0.0);
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

TEST_CASE("Testando o construtor simplificado da classe Paciente") {
    DataHora referencia(1, 1, 2000, 0.0);
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
    paciente.atualizarEstado(3, t1.getHorasDesdeReferencia());

    CHECK(paciente.getEstado() == 3);
    CHECK(paciente.getTempoTotalEspera() == 1.0);
    CHECK(paciente.getTempoTotalAtendimento() == 0.0);

    DataHora dh2(21, 3, 2017, 4.0); // 2 horas depois
    Tempo t2(dh2, referencia);
    paciente.atualizarEstado(4, t2.getHorasDesdeReferencia());

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
    paciente.atualizarEstado(3, t1.getHorasDesdeReferencia());

    CHECK(paciente.estadoParaString() == "Sendo triado");
}

TEST_CASE("Testando a função proximaFilaProcedimento") {
    DataHora referencia(1, 1, 1970, 0.0);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";

    Paciente paciente(linha, referencia);

    CHECK(paciente.proximaFilaProcedimento() == 2);

    DataHora dh1(21, 3, 2017, 3.0); // 1 hora depois
    Tempo t1(dh1, referencia);
    paciente.atualizarEstado(3, t1.getHorasDesdeReferencia());

    CHECK(paciente.proximaFilaProcedimento() == 4);
}

TEST_CASE("Testando a função precisaDeServicos") {
    DataHora referencia(1, 1, 1970, 0.0);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";

    Paciente paciente(linha, referencia);

    CHECK(paciente.precisaDeServicos() == true);

    DataHora dh1(21, 3, 2017, 3.0); // 1 hora depois
    Tempo t1(dh1, referencia);
    paciente.atualizarEstado(3, t1.getHorasDesdeReferencia());

    CHECK(paciente.precisaDeServicos() == true);

    // Simular a conclusão de todos os procedimentos
    paciente.atualizarEstado(4, t1.getHorasDesdeReferencia() + 1);
    paciente.atualizarEstado(5, t1.getHorasDesdeReferencia() + 2);
    paciente.atualizarEstado(6, t1.getHorasDesdeReferencia() + 3);
    paciente.atualizarEstado(7, t1.getHorasDesdeReferencia() + 4);
    paciente.atualizarEstado(8, t1.getHorasDesdeReferencia() + 5);
    paciente.atualizarEstado(9, t1.getHorasDesdeReferencia() + 6);
    paciente.atualizarEstado(10, t1.getHorasDesdeReferencia() + 7);
    paciente.atualizarEstado(11, t1.getHorasDesdeReferencia() + 8);
    paciente.atualizarEstado(12, t1.getHorasDesdeReferencia() + 9);
    paciente.atualizarEstado(13, t1.getHorasDesdeReferencia() + 10);

    CHECK(paciente.precisaDeServicos() == false);
}
