#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "Tempo.hpp"

TEST_CASE("Testando a classe Tempo") {
    DataHora ref(1, 1, 2025, 0.0);
    DataHora dh(2, 1, 2025, 12.0);
    Tempo t1(dh, ref);

    CHECK(t1.getHorasDesdeReferencia() == 36.0);

    t1.somaHoras(1.0);
    CHECK(t1.getHorasDesdeReferencia() == 37.0);
    CHECK(!t1.paraString().empty());
    CHECK(t1.paraString() == "Thu Jan  2 13:00:00 2025");
}

TEST_CASE("Testando overflow de dia, mês e ano") {
    DataHora ref(1, 1, 2020, 0.0);
    DataHora dh(31, 12, 2024, 23.5);
    Tempo t1(dh, ref);

    t1.somaHoras(2.0);

    CHECK(t1.paraString() == "Wed Jan  1 01:30:00 2025");
}
