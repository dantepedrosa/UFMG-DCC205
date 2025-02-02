#pragma once

#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>

class Voo {
public:
    std::string str;
    std::string origem;
    std::string destino;
    float preco;
    int assentos;
    std::time_t partida;
    std::time_t chegada;
    int paradas;
    std::time_t duracao;

    Voo(const std::string& linha) {
        std::istringstream ss(linha);
        std::string partidaStr, chegadaStr;

        str = linha;

        ss >> origem >> destino >> preco >> assentos >> partidaStr >> chegadaStr >> paradas;

        if (ss.fail()) {
            throw std::runtime_error("Erro ao processar a linha de entrada.");
        }

        partida = parseTempo(partidaStr);
        chegada = parseTempo(chegadaStr);
        duracao = chegada - partida;
    }

private:
    std::time_t parseTempo(const std::string& datetime) {
        std::tm tm = {};
        std::istringstream ss(datetime);
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");

        if (ss.fail()) {
            std::cerr << "Failed to parse datetime: " << datetime << std::endl;
            throw std::runtime_error("Erro ao interpretar data/hora.");
        }

        std::time_t tt = std::mktime(&tm);
        return tt;
    }
};
