#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "../include/DataHora.hpp"

TEST_CASE("Testando o construtor da classe Data") {
    Data data(15, 8, 2023);
    CHECK(data.getDia() == 15);
    CHECK(data.getmes() == 8);
    CHECK(data.getAno() == 2023);
}

TEST_CASE("Testando o construtor da classe DataHora") {
    Data dataReferencia(1, 1, 2020);
    Data dataAtual(15, 8, 2023);
    float horaAtual = 14.5; // 14:30
    DataHora dataHora(dataReferencia, dataAtual, horaAtual);
    CHECK(dataHora.getCodDataHora() == 202308151450);
}

TEST_CASE("Testando o método getStringDataHora") {
    Data dataReferencia(1, 1, 2020);
    Data dataAtual(15, 8, 2023);
    float horaAtual = 14.5; // 14:30
    DataHora dataHora(dataReferencia, dataAtual, horaAtual);
    std::string formato = "DD/MM/YYYY HH:MM";
    CHECK(dataHora.getStringDataHora(formato) == "15/08/2023 14:30");
}

TEST_CASE("Testando o método somaHoras") {
    Data dataReferencia(1, 1, 2020);
    Data dataAtual(15, 8, 2023);
    float horaAtual = 14.5; // 14:30
    DataHora dataHora(dataReferencia, dataAtual, horaAtual);
    dataHora.somaHoras(1.5); // Adiciona 1 hora e 30 minutos
    CHECK(dataHora.getStringDataHora("DD/MM/YYYY HH:MM") == "15/08/2023 16:00");
}

TEST_CASE("Testando os operadores de comparação") {
    Data dataReferencia(1, 1, 2020);
    Data data1(15, 8, 2023);
    Data data2(16, 8, 2023);
    float hora1 = 14.5; // 14:30
    float hora2 = 15.0; // 15:00
    DataHora dataHora1(dataReferencia, data1, hora1);
    DataHora dataHora2(dataReferencia, data2, hora2);

    CHECK(dataHora1 < dataHora2);
    CHECK(dataHora2 > dataHora1);
    CHECK(dataHora1 <= dataHora2);
    CHECK(dataHora2 >= dataHora1);
    CHECK(dataHora1 != dataHora2);
    CHECK(!(dataHora1 == dataHora2));
}
