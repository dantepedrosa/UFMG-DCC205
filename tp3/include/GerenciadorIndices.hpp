/**
 * @file GerenciadorIndices.hpp
 * @brief Gerenciamento de índices para busca rápida de voos
 * @author Dante Junqueira Pedrosa
 * @date 2025
 */

#pragma once

#include "IndiceVoos.hpp"
#include "../include/Voo.hpp"
#include <stdexcept>
#include <iostream>

/**
 * @brief Classe para gerenciar múltiplos índices de voos
 */
class GerenciadorIndices {
private:
    IndiceVoos indiceOrigem;      ///< Índice para origem dos voos (org)
    IndiceVoos indiceDestino;     ///< Índice para destino dos voos (dst)
    IndiceVoos indicePreco;       ///< Índice para preço dos voos (prc)
    IndiceVoos indiceAssentos;    ///< Índice para assentos disponíveis (sea)
    IndiceVoos indiceParadas;     ///< Índice para número de paradas (sto)
    IndiceVoos indiceDuracao;     ///< Índice para duração dos voos (dur)
    IndiceVoos indicePartida;     ///< Índice para data de partida (dat)
    IndiceVoos indiceChegada;     ///< Índice para data de chegada (arr)

public:
    /**
     * @brief Insere um voo nos índices
     * @param voo Ponteiro para o voo
     * @param indice Índice do voo no vetor de voos
     */
    void inserirVoo(Voo* voo, int indice) {
        if (!voo) {
            throw std::invalid_argument("Ponteiro de voo inválido");
        }
        if (indice < 0) {
            throw std::invalid_argument("Índice não pode ser negativo");
        }

        try {
            indiceOrigem.inserir(voo->origem, indice);
            indiceDestino.inserir(voo->destino, indice);
            indicePreco.inserir(std::to_string(voo->preco), indice);
            indiceAssentos.inserir(std::to_string(voo->assentos), indice);
            indiceParadas.inserir(std::to_string(voo->paradas), indice);
            indiceDuracao.inserir(std::to_string(voo->duracao), indice);
            indicePartida.inserir(std::to_string(voo->partida), indice);
            indiceChegada.inserir(std::to_string(voo->chegada), indice);
        } catch (const std::exception& e) {
            std::cerr << "Erro ao indexar voo: " << e.what() << std::endl;
            throw;
        }
    }

    /**
     * @brief Busca voos por critério e valor
     * @param criterio Critério de busca (ex: "org", "dst")
     * @param valor Valor do critério
     * @return Ponteiro para a lista de índices dos voos
     */
    ListaEncadeada<int>* buscarPorCriterio(const std::string& criterio, const std::string& valor) {
        if (criterio.empty() || valor.empty()) {
            throw std::invalid_argument("Critério e valor não podem estar vazios");
        }

        if (criterio == "org") return indiceOrigem.buscar(valor);
        if (criterio == "dst") return indiceDestino.buscar(valor);
        if (criterio == "prc") return indicePreco.buscar(valor);
        if (criterio == "sea") return indiceAssentos.buscar(valor);
        if (criterio == "sto") return indiceParadas.buscar(valor);
        if (criterio == "dur") return indiceDuracao.buscar(valor);
        if (criterio == "dat") return indicePartida.buscar(valor);
        if (criterio == "arr") return indiceChegada.buscar(valor);
        return nullptr;
    }
};
