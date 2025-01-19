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
    DataHora ref(31, 12, 2020, 23.0);
    DataHora dh(1, 1, 2021, 1.0);
    Tempo t1(dh, ref);

    CHECK(t1.getHorasDesdeReferencia() == 2.0);

    DataHora ref2(28, 2, 2020, 23.0); // Leap year
    DataHora dh2(1, 3, 2020, 1.0);
    Tempo t2(dh2, ref2);

    CHECK(t2.getHorasDesdeReferencia() == 2.0);
}
