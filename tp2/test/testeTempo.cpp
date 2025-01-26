#include "../include/doctest.hpp"
#include "../include/Tempo.hpp"

TEST_CASE("Testando o construtor da classe Tempo") {
    DataHora referencia(1, 1, 1970, 0.0);
    DataHora dataHora(1, 1, 1987, 0.0);
    Tempo tempo(dataHora, referencia);

    CHECK(tempo.getHorasDesdeReferencia() == 149016.0);
}

TEST_CASE("Testando a função somaHoras") {
    DataHora referencia(1, 1, 1970, 0.0);
    DataHora dataHora(1, 1, 1987, 0.0);
    Tempo tempo(dataHora, referencia);

    tempo.somaHoras(2.0);
    CHECK(tempo.getHorasDesdeReferencia() == 149018.0);
}

TEST_CASE("Testando a função paraString") {
    DataHora referencia(1, 1, 2000, 0.0);
    DataHora dataHora(21, 3, 2017, 2.0);
    Tempo tempo(dataHora, referencia);

    CHECK(tempo.paraString() == "Tue Mar 21 02:00:00 2017");
}

TEST_CASE("Testando a função getDataHora") {
    DataHora referencia(1, 1, 2000, 0.0);
    DataHora dataHora(21, 3, 2017, 2.0);
    Tempo tempo(dataHora, referencia);

    DataHora dh = tempo.getDataHora();
    CHECK(dh.dia == 21);
    CHECK(dh.mes == 3);
    CHECK(dh.ano == 2017);
    CHECK(dh.hora == 2.0);
}
