#include "../include/doctest.hpp"
#include "../include/Paciente.hpp"
#include "../include/Tempo.hpp"

TEST_CASE("Testando o construtor da classe Paciente") {
    DataHora referencia(1, 1, 2000, 0.0);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";

    Paciente paciente(linha, referencia);

    CHECK(paciente.getId() == "0009600008");
    CHECK(paciente.getAltaImediata() == false);
    CHECK(paciente.getAdmissaoHZ().getReferencia() == referencia);
    CHECK(paciente.getAdmissaoHZ().getDataHora().ano == 2017);
    CHECK(paciente.getAdmissaoHZ().getDataHora().mes == 3);
    CHECK(paciente.getAdmissaoHZ().getDataHora().dia == 21);
    CHECK(paciente.getAdmissaoHZ().getDataHora().hora == 2.0);
    CHECK(paciente.getUrgencia() == 1);
    CHECK(paciente.getMhTotal() == 5);
    CHECK(paciente.getTlTotal() == 43);
    CHECK(paciente.getEiTotal() == 2);
    CHECK(paciente.getImTotal() == 110);
    CHECK(paciente.getEstado() == 1);
    CHECK(paciente.getTempoTotalAtendimento() == 0.0);
    CHECK(paciente.getTempoTotalEspera() == 0.0);
}

TEST_CASE("Testando a atualização de estado do paciente") {
    DataHora referencia(21, 3, 2017, 2.0);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";

    // Entrar na fila de triagem
    Paciente paciente(linha, referencia);
    DataHora dh0(21, 3, 2017, 2.0); // Entrada instantanea fila triagem
    Tempo t0(dh0, referencia);
    paciente.atualizarEstado(2, t0.getHorasDesdeReferencia());

    // Atendido em triagem
    DataHora dh1(21, 3, 2017, 3.0); 
    Tempo t1(dh1, referencia);
    paciente.atualizarEstado(3, t1.getHorasDesdeReferencia());

    CHECK(paciente.getEstado() == 3);
    CHECK(paciente.getTempoTotalEspera() == 1.0);
    CHECK(paciente.getTempoTotalAtendimento() == 0.0);

    DataHora dh2(21, 3, 2017, 4.0); // 2 horas depois, 1 de atendimento
    Tempo t2(dh2, referencia);
    paciente.atualizarEstado(4, t2.getHorasDesdeReferencia());

    CHECK(paciente.getEstado() == 4);
    CHECK(paciente.getTempoTotalEspera() == 1.0);
    CHECK(paciente.getTempoTotalAtendimento() == 1.0);
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
    std::string linha = "0009600008 0 2017 3 21 2 1 1 1 1 1";

    Paciente paciente(linha, referencia);
    DataHora dh0(21, 3, 2017, 2.0); // Entrada instantanea fila triagem
    Tempo t0(dh0, referencia);
    paciente.atualizarEstado(2, t0.getHorasDesdeReferencia());

    CHECK(paciente.precisaDeServicos() == true);

    DataHora dh1(21, 3, 2017, 3.0); // 1 hora depois
    Tempo t1(dh1, referencia);
    paciente.atualizarEstado(3, t1.getHorasDesdeReferencia());

    CHECK(paciente.precisaDeServicos() == true);

    // Simular a conclusão de todos os procedimentos 1 vez
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

TEST_CASE("Testando a função registraSaida e imprimeEstatisticas, com alta após atendimento") {
    DataHora referencia(1, 1, 1970, 0.0);
    std::string linha = "0009600008 1 2017 3 21 2 1 5 43 2 110";

    Paciente paciente(linha, referencia);
    
    DataHora dh0(21, 3, 2017, 2.0); // Entrada instantanea fila triagem
    Tempo t0(dh0, referencia);   // Entrada instantanea fila triagem
    paciente.atualizarEstado(2, t0.getHorasDesdeReferencia());

    DataHora dh1(21, 3, 2017, 3.0); // 1 hora depois, em fila
    Tempo t1(dh1, referencia);  // Entrada Triagem
    paciente.atualizarEstado(3, t1.getHorasDesdeReferencia());

    DataHora dh2(21, 3, 2017, 3.05); // Em atendimento 
    Tempo t2(dh2, referencia);  // Saida triagem, fila atendimento
    paciente.atualizarEstado(4, t2.getHorasDesdeReferencia());

    DataHora dh3(21, 3, 2017, 4.5); // 1 hora e 27 min depois, em fila
    Tempo t3(dh3, referencia);  // Entrada atendimento, saida fila
    paciente.atualizarEstado(5, t3.getHorasDesdeReferencia());    
    
    paciente.atualizarEstado(14, t3.getHorasDesdeReferencia()+1);  // 1 hora sendo atendido

    CHECK(paciente.getEstado() == 14);

    std::string output = paciente.imprimeEstatisticas();
    std::string expected_output = "0009600008 Tue Mar 21 02:00:00 2017 Tue Mar 21 05:30:00 2017 3.50 1.05 2.45";

    CHECK(output == expected_output);
}

TEST_CASE("Testando erros na atualização de estado do paciente") {
    DataHora referencia(1, 1, 1970, 0.0);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";

    Paciente paciente(linha, referencia);
    DataHora dh0(21, 3, 2017, 2.0); // Entrada instantanea fila triagem
    Tempo t0(dh0, referencia);

    CHECK_THROWS_AS(paciente.atualizarEstado(1, t0.getHorasDesdeReferencia()), std::invalid_argument);

    paciente.atualizarEstado(2, t0.getHorasDesdeReferencia());
    CHECK_THROWS_AS(paciente.atualizarEstado(14, t0.getHorasDesdeReferencia()), std::invalid_argument);
}
