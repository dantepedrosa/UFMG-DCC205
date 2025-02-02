/**
 * @file Voo.hpp
 * @brief Definição e implementação da classe Voo
 * @author Dante Junqueira Pedrosa
 * @date 2025
 */

#pragma once

#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>

/**
 * @brief Classe que representa um voo e seus atributos
 */
class Voo {
public:
    std::string str;        // String original do voo
    std::string origem;     // Aeroporto de origem
    std::string destino;    // Aeroporto de destino
    float preco;            // Preço do voo
    int assentos;           // Número de assentos disponíveis
    std::time_t partida;    // Horário de partida
    std::time_t chegada;    // Horário de chegada
    int paradas;            // Número de paradas
    std::time_t duracao;    // Duração total do voo

    /**
     * @brief Construtor que inicializa um voo a partir de uma string
     * @param linha String contendo os dados do voo
     */
    Voo(const std::string& linha) {
        std::istringstream ss(linha);
        std::string partidaStr, chegadaStr;

        str = linha;

        if (!(ss >> origem >> destino >> preco >> assentos >> partidaStr >> chegadaStr >> paradas)) {
            throw std::invalid_argument("Formato inválido de entrada para voo");
        }

        if (origem.empty() || destino.empty()) {
            throw std::invalid_argument("Origem ou destino não podem estar vazios");
        }

        if (preco < 0) {
            throw std::invalid_argument("Preço não pode ser negativo");
        }

        if (assentos < 0) {
            throw std::invalid_argument("Número de assentos não pode ser negativo");
        }

        if (paradas < 0) {
            throw std::invalid_argument("Número de paradas não pode ser negativo");
        }

        try {
            partida = parseTempo(partidaStr);
            chegada = parseTempo(chegadaStr);
        } catch (const std::exception& e) {
            throw std::invalid_argument(std::string("Erro no formato de data/hora: ") + e.what());
        }

        duracao = chegada - partida;
        if (duracao < 0) {
            throw std::invalid_argument("Data de chegada deve ser posterior à data de partida");
        }
    }

private:
    /**
     * @brief Converte uma string de data/hora para time_t
     * @param datetime String no formato "YYYY-MM-DDThh:mm:ss"
     * @return Valor em time_t correspondente
     */
    std::time_t parseTempo(const std::string& datetime) {
        if (datetime.length() != 19) { // YYYY-MM-DDThh:mm:ss
            throw std::invalid_argument("Formato de data/hora inválido");
        }

        std::tm tm = {};
        std::istringstream ss(datetime);
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");

        if (ss.fail()) {
            throw std::runtime_error("Erro ao interpretar data/hora: " + datetime);
        }

        std::time_t tt = std::mktime(&tm);
        if (tt == -1) {
            throw std::runtime_error("Data/hora inválida");
        }

        return tt;
    }
};
