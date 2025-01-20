#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "Procedimento.hpp"

TEST_CASE("Testando a classe Procedimento") {
    Procedimento triagem("Triagem", 5, 0.2);

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
