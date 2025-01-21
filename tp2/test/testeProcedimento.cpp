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

TEST_CASE("Testando enfileiramento e desenfileiramento na fila geral") {
    Procedimento procedimento("Procedimento Geral", 3, 0.5, false);

    DataHora ref(1, 1, 2025, 0.0);
    Tempo admissao1(DataHora(1, 1, 2025, 1.0), ref);
    Tempo admissao2(DataHora(1, 1, 2025, 2.0), ref);

    Paciente paciente1(1, false, admissao1, 0, 0, 0, 0, 0);
    Paciente paciente2(2, false, admissao2, 0, 0, 0, 0, 0);

    procedimento.enfileira(paciente1);
    procedimento.enfileira(paciente2);

    Paciente desenfileirado1 = procedimento.desenfileira();
    CHECK(desenfileirado1.getId() == 1);

    Paciente desenfileirado2 = procedimento.desenfileira();
    CHECK(desenfileirado2.getId() == 2);
}

