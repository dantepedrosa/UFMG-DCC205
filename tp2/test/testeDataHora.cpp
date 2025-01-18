//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "../include/DataHora.hpp"

TEST_CASE("Testando o construtor da classe Data") {
    Data data(15, 8, 2023);
    CHECK(data.getDia() == 15);
    CHECK(data.getmes() == 8);
    CHECK(data.getAno() == 2023);
}

TEST_CASE("Testando o construtor da classe DataHora") {
    Data dataAtual(15, 8, 2023);
    float horaAtual = 14.5; // 14:30
    DataHora dataHora(dataAtual, horaAtual);
    CHECK(dataHora.getCodDataHora() == 2308151450);
}

TEST_CASE("Testando o método getStringDataHora") {
    Data dataAtual(15, 8, 2023);
    float horaAtual = 14.5; // 14:30
    DataHora dataHora(dataAtual, horaAtual);
    CHECK(dataHora.getStringDataHora() == "Tue Aug 15 14:30:00 2023");
}

TEST_CASE("Testando o método somaHoras") {
    Data dataAtual(15, 8, 2023);
    float horaAtual = 14.5; // 14:30
    DataHora dataHora(dataAtual, horaAtual);
    dataHora.somaHoras(1.5); // Adiciona 1 hora e 30 minutos
    CHECK(dataHora.getCodDataHora() == 2308151600);
}

TEST_CASE("Testando o método somaHoras com overflow") {
    Data dataAtual(15, 8, 2023);
    float horaAtual = 23.5; // 23:30
    DataHora dataHora(dataAtual, horaAtual);
    dataHora.somaHoras(27); // Adiciona 27 horas
    CHECK(dataHora.getCodDataHora() == 2308170250);
}

TEST_CASE("Testando o método getData") {
    Data dataAtual(15, 8, 2023);
    float horaAtual = 14.5; // 14:30
    DataHora dataHora(dataAtual, horaAtual);
    Data data = dataHora.getData();
    CHECK(data.getDia() == 15);
    CHECK(data.getmes() == 8);
    CHECK(data.getAno() == 2023);
}

TEST_CASE("Testando o método getHora") {
    Data dataAtual(15, 8, 2023);
    float horaAtual = 14.5; // 14:30
    DataHora dataHora(dataAtual, horaAtual);
    CHECK(dataHora.getHora() == 14);
}

TEST_CASE("Testando o método getMinutos") {
    Data dataAtual(15, 8, 2023);
    float horaAtual = 14.5; // 14:30
    DataHora dataHora(dataAtual, horaAtual);
    CHECK(dataHora.getMinutos() == 30);
}

TEST_CASE("Testando os operadores de comparação") {
    Data data1(15, 8, 2023);
    Data data2(16, 8, 2023);
    float hora1 = 14.5; // 14:30
    float hora2 = 15.0; // 15:00
    DataHora dataHora1(data1, hora1);
    DataHora dataHora2(data2, hora2);

    CHECK(dataHora1 < dataHora2);
    CHECK(dataHora2 > dataHora1);
    CHECK(dataHora1 <= dataHora2);
    CHECK(dataHora2 >= dataHora1);
    CHECK(dataHora1 != dataHora2);
    CHECK(!(dataHora1 == dataHora2));
}

TEST_CASE("Testando o método getDiaSemana") {
    Data data(15, 8, 2023);
    DataHora dataHora(data, 14.5);
    CHECK(dataHora.getDiaSemana(data) == "Tue");
}

TEST_CASE("Testando o método getMes") {
    Data data(15, 8, 2023);
    DataHora dataHora(data, 14.5);
    CHECK(dataHora.getMes(data) == "Aug");
}
