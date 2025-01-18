#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "../include/DataHoraTm.hpp"

TEST_CASE("Testando o construtor da classe Data") {
    Data data(15, 8, 2023);
    CHECK(data.getDia() == 15);
    CHECK(data.getmes() == 8);
    CHECK(data.getAno() == 2023);
}

TEST_CASE("Testando o construtor da classe DataHoraTm") {
    Data dataAtual(15, 8, 2023);
    float horaAtual = 14.5; // 14:30
    DataHoraTm dataHora(dataAtual, horaAtual);
    CHECK(dataHora.getData().getDia() == 15);
    CHECK(dataHora.getData().getmes() == 8);
    CHECK(dataHora.getData().getAno() == 2023);
    CHECK(dataHora.getHora() == 14);
    CHECK(dataHora.getMinutos() == 30);
}

TEST_CASE("Testando o método getStringDataHora") {
    Data dataAtual(15, 8, 2023);
    float horaAtual = 14.5; // 14:30
    DataHoraTm dataHora(dataAtual, horaAtual);
    CHECK(dataHora.getStringDataHora("%d/%m/%Y %H:%M") == "15/08/2023 14:30");
}

TEST_CASE("Testando o método somaHoras com overflow de dia") {
    Data dataAtual(15, 8, 2023);
    float horaAtual = 23.5; // 23:30
    DataHoraTm dataHora(dataAtual, horaAtual);
    dataHora.somaHoras(1.0); // Adiciona 1 hora
    CHECK(dataHora.getData().getDia() == 16);
    CHECK(dataHora.getData().getmes() == 8);
    CHECK(dataHora.getData().getAno() == 2023);
    CHECK(dataHora.getHora() == 0);
    CHECK(dataHora.getMinutos() == 30);
}

TEST_CASE("Testando o método somaHoras com overflow de mês") {
    Data dataAtual(31, 8, 2023);
    float horaAtual = 23.5; // 23:30
    DataHoraTm dataHora(dataAtual, horaAtual);
    dataHora.somaHoras(1.0); // Adiciona 1 hora
    CHECK(dataHora.getData().getDia() == 1);
    CHECK(dataHora.getData().getmes() == 9);
    CHECK(dataHora.getData().getAno() == 2023);
    CHECK(dataHora.getHora() == 0);
    CHECK(dataHora.getMinutos() == 30);
}

TEST_CASE("Testando o método somaHoras com overflow de ano") {
    Data dataAtual(31, 12, 2023);
    float horaAtual = 23.5; // 23:30
    DataHoraTm dataHora(dataAtual, horaAtual);
    dataHora.somaHoras(1.0); // Adiciona 1 hora
    CHECK(dataHora.getData().getDia() == 1);
    CHECK(dataHora.getData().getmes() == 1);
    CHECK(dataHora.getData().getAno() == 2024);
    CHECK(dataHora.getHora() == 0);
    CHECK(dataHora.getMinutos() == 30);
}

TEST_CASE("Testando o método getDiaSemana") {
    Data data(15, 8, 2023);
    DataHoraTm dataHora(data, 14.5);
    CHECK(dataHora.getStringDataHora("%A") == "Tuesday");
}

TEST_CASE("Testando o método getMes") {
    Data data(15, 8, 2023);
    DataHoraTm dataHora(data, 14.5);
    CHECK(dataHora.getStringDataHora("%B") == "August");
}
