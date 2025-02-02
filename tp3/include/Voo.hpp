/**
 * @file Voo.hpp
 * @brief Definição da classe Voo e suas propriedades
 * @author Dante Junqueira Pedrosa
 * @date 2025
 */

#pragma once

#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>

/**
 * @brief Classe que representa um voo
 */
class Voo {
public:
    std::string str;      // String original do voo
    std::string origem;   // Aeroporto de origem
    std::string destino;  // Aeroporto de destino
    float preco;         // Preço do voo
    int assentos;        // Número de assentos disponíveis
    std::time_t partida; // Horário de partida
    std::time_t chegada; // Horário de chegada
    int paradas;         // Número de paradas
    std::time_t duracao; // Duração total do voo

    /**
     * @brief Construtor que inicializa um voo a partir de uma string
     * @param linha String contendo os dados do voo
     */
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
    /**
     * @brief Converte uma string de data/hora para time_t
     * @param datetime String no formato "YYYY-MM-DDThh:mm:ss"
     * @return Valor em time_t correspondente
     */
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
