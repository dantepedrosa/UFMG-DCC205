#include "../include/doctest.hpp"
#include "../include/Escalonador.hpp"
#include "../include/Paciente.hpp"
#include "../include/Tempo.hpp"

TEST_CASE("Testando o construtor da classe Escalonador") {
    DataHora referencia(1, 1, 2000, 0.0);
    Escalonador escalonador(10, referencia);

    CHECK(escalonador.temEventos() == false);
}

TEST_CASE("Testando a inserção e retirada de eventos") {
    DataHora referencia(1, 1, 2000, 0.0);
    Escalonador escalonador(10, referencia);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";
    DataHora dataHora(21, 3, 2017, 2.0);
    Tempo tempoEvento(dataHora, referencia);
    Paciente paciente(linha, referencia);
    Evento evento(tempoEvento.getHorasDesdeReferencia(), &paciente, 1);

    escalonador.insereEvento(evento);
    CHECK(escalonador.temEventos() == true);

    Evento proximoEvento = escalonador.retiraProximoEvento();
    CHECK(proximoEvento.getPaciente()->getId() == "0009600008");
    CHECK(escalonador.temEventos() == false);
}

TEST_CASE("Testando a função avancaRelogio") {
    DataHora referencia(1, 1, 2017, 0.0);
    Escalonador escalonador(10, referencia);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";
    DataHora dataHora(21, 3, 2017, 2.0);
    Tempo tempoEvento(dataHora, referencia);
    Paciente paciente(linha, referencia);
    Evento evento(tempoEvento.getHorasDesdeReferencia(), &paciente, 1);

    escalonador.insereEvento(evento);
    escalonador.retiraProximoEvento();
    float relogio = escalonador.getRelogio();

    CHECK(relogio == tempoEvento.getHorasDesdeReferencia());
}

TEST_CASE("Testando a função finaliza") {
    DataHora referencia(1, 1, 2000, 0.0);
    Escalonador escalonador(10, referencia);
    std::string linha = "0009600008 0 2017 3 21 2 1 5 43 2 110";
    DataHora dataHora(21, 3, 2017, 2.0);
    Tempo tempoEvento(dataHora, referencia);
    Paciente paciente(linha, referencia);
    Evento evento(tempoEvento.getHorasDesdeReferencia(), &paciente, 1);

    escalonador.insereEvento(evento);
    escalonador.finaliza();

    CHECK(escalonador.temEventos() == false);
}
