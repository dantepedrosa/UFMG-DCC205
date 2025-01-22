#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "Escalonador.hpp"
#include "Paciente.hpp"


TEST_CASE("Testando a classe Escalonador") {
    Escalonador escalonador(10);
    escalonador.inicializa(0.0);

    DataHora ref(1, 1, 2025, 0.0);
    DataHora dh1(2, 1, 2025, 12.0);     // 36 horas depois
    DataHora dh2(3, 1, 2025, 14.0);     // 62 horas depois

    Paciente p1, p2;
    Evento e1(Tempo(dh1, ref), &p1, 1);
    Evento e2(Tempo(dh2, ref), &p2, 2);

    escalonador.insereEvento(e1);
    escalonador.insereEvento(e2);

    CHECK(escalonador.temEventos() == true);
    CHECK(escalonador.getRelogio() == 0.0);

    escalonador.avancaRelogio();
    CHECK(escalonador.getRelogio() == 36.0);

    Evento proximo = escalonador.retiraProximoEvento();
    CHECK(proximo.dataHora.getHorasDesdeReferencia() == 36.0);

    escalonador.avancaRelogio();
    CHECK(escalonador.getRelogio() == 62.0);

    proximo = escalonador.retiraProximoEvento();
    CHECK(proximo.dataHora.getHorasDesdeReferencia() == 62.0);

    CHECK(escalonador.temEventos() == false);
    escalonador.finaliza();
}

TEST_CASE("Testando exceção ao inserir evento com escalonador cheio") {
    Escalonador escalonador(2); // Capacidade máxima de 2 eventos
    escalonador.inicializa(0.0);

    DataHora ref(1, 1, 2025, 0.0);
    DataHora dh1(2, 1, 2025, 12.0);     // 36 horas depois
    DataHora dh2(3, 1, 2025, 14.0);     // 62 horas depois
    DataHora dh3(4, 1, 2025, 16.0);     // 86 horas depois

    Paciente p1, p2, p3;
    Evento e1(Tempo(dh1, ref), &p1, 1);
    Evento e2(Tempo(dh2, ref), &p2, 2);
    Evento e3(Tempo(dh3, ref), &p3, 3);

    escalonador.insereEvento(e1);
    escalonador.insereEvento(e2);

    CHECK_THROWS_AS(escalonador.insereEvento(e3), std::overflow_error);
}
