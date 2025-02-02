/**
 * @file mainPontoExtra.cpp
 * @brief Sistema interativo de processamento e filtragem de voos com recomendações
 * @author Dante Junqueira Pedrosa
 * @date 2025
 */

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "../include/ArvoreDeExpressao.hpp"
#include "../include/ListaEncadeada.hpp"
#include "../include/Pilha.hpp"
#include "../include/Sort.hpp"
#include "../include/Voo.hpp"
#include "../include/IndiceVoos.hpp"
#include "../include/GerenciadorIndices.hpp"

// Estrutura para armazenar estatísticas de uma consulta
struct EstatisticasConsulta {
    int numResultados;
    float minPreco, maxPreco;
    float minDuracao, maxDuracao;
    int minParadas, maxParadas;
    int numOrigens;
    int numDestinos;
    ListaEncadeada<std::string> origens;
    ListaEncadeada<std::string> destinos;
};

/**
 * @brief Estrutura para armazenar dados de uma consulta de voos
 */
struct Consulta {
    std::string str;          // String original da consulta
    int numResultados;        // Número de resultados desejados
    std::string trigrama;     // Critério de ordenação
    std::string expression;   // Expressão de filtragem
};

// Protótipos de funções
EstatisticasConsulta analisarResultados(const ListaEncadeada<Voo*>& voos);
ListaEncadeada<std::string> gerarRecomendacoes(const EstatisticasConsulta& stats);
void leConsultasdeEntrada(Consulta** consultas, int numConsultas);
void leConsultasdeArquivo(std::ifstream& inputFile, Consulta** consultas, int numConsultas);
void separarMenoresVoos(ListaEncadeada<Voo*>& lista, Voo** arrayDestino, int n, const std::string& trigrama);
void imprimirVoos(Voo** voos, int numVoos);
void leVoosdeArquivo(std::ifstream& inputFile, Voo** voos, int numLinhas);
void leVoosdeEntrada(Voo** voos, int numLinhas);

/**
 * @brief Analisa os resultados de uma consulta e gera estatísticas
 * @param voos Lista de voos resultantes
 * @return Estrutura com estatísticas da consulta
 */
EstatisticasConsulta analisarResultados(const ListaEncadeada<Voo*>& voos) {
    EstatisticasConsulta stats;
    stats.numResultados = voos.GetTamanho();
    
    if (voos.Vazia()) {
        return stats;
    }

    // Inicializa com valores do primeiro voo
    Voo* primeiro = voos.GetItem(0);
    stats.minPreco = stats.maxPreco = primeiro->preco;
    stats.minDuracao = stats.maxDuracao = primeiro->duracao;
    stats.minParadas = stats.maxParadas = primeiro->paradas;
    stats.origens.InsereFinal(primeiro->origem);
    stats.destinos.InsereFinal(primeiro->destino);
    stats.numOrigens = stats.numDestinos = 1;

    // Analisa demais voos
    for (int i = 1; i < voos.GetTamanho(); i++) {
        Voo* v = voos.GetItem(i);
        
        // Atualiza ranges
        if (v->preco < stats.minPreco) stats.minPreco = v->preco;
        if (v->preco > stats.maxPreco) stats.maxPreco = v->preco;
        if (v->duracao < stats.minDuracao) stats.minDuracao = v->duracao;
        if (v->duracao > stats.maxDuracao) stats.maxDuracao = v->duracao;
        if (v->paradas < stats.minParadas) stats.minParadas = v->paradas;
        if (v->paradas > stats.maxParadas) stats.maxParadas = v->paradas;

        // Verifica se origem/destino já existem
        bool origemExiste = false;
        bool destinoExiste = false;
        for (int j = 0; j < stats.origens.GetTamanho(); j++) {
            if (stats.origens.GetItem(j) == v->origem) {
                origemExiste = true;
                break;
            }
        }
        for (int j = 0; j < stats.destinos.GetTamanho(); j++) {
            if (stats.destinos.GetItem(j) == v->destino) {
                destinoExiste = true;
                break;
            }
        }

        if (!origemExiste) {
            stats.origens.InsereFinal(v->origem);
            stats.numOrigens++;
        }
        if (!destinoExiste) {
            stats.destinos.InsereFinal(v->destino);
            stats.numDestinos++;
        }
    }

    return stats;
}

/**
 * @brief Gera recomendações para refinar a consulta
 * @param stats Estatísticas da consulta atual
 * @param consulta Consulta original
 * @return Lista de sugestões de refinamento
 */
ListaEncadeada<std::string> gerarRecomendacoes(const EstatisticasConsulta& stats) {
    ListaEncadeada<std::string> recomendacoes;

    // Se muitos resultados, sugere refinamentos
    if (stats.numResultados > 10) {
        // Recomendações baseadas em preço
        if (stats.maxPreco - stats.minPreco > 100) {
            std::stringstream ss;
            ss << "Adicione filtro de preço: prc < " << (stats.minPreco + stats.maxPreco) / 2;
            recomendacoes.InsereFinal(ss.str());
        }

        // Recomendações baseadas em origem/destino
        if (stats.numOrigens > 1) {
            std::string sugestao = "Especifique a origem. Origens disponíveis:";
            for (int i = 0; i < stats.origens.GetTamanho(); i++) {
                sugestao += " " + stats.origens.GetItem(i);
            }
            recomendacoes.InsereFinal(sugestao);
        }

        // Recomendações baseadas em paradas
        if (stats.maxParadas - stats.minParadas > 1) {
            recomendacoes.InsereFinal("Adicione filtro de paradas: sto <= " + 
                                    std::to_string(stats.minParadas + 1));
        }
    }

    return recomendacoes;
}


int main(int argc, char const* argv[]) {
    try {
        // Inicialização igual ao main.cpp
        bool fileEnabled = false;
        std::string filePath;
        std::string line;
        std::istringstream iss;
        int numLinhas;
        
        Voo** voos;
        GerenciadorIndices indices;

        // Processamento dos argumentos de linha de comando
        switch (argc) {
            case 1:
                fileEnabled = false;
                break;
            case 2:
                fileEnabled = true;
                filePath = argv[1];
                break;
            default:
                std::cerr << "Uso: " << argv[0] << " [arquivo_entrada]" << std::endl;
                return 1;
        }

        // Leitura inicial dos voos
        if (fileEnabled) {
            std::ifstream inputFile(filePath);
            if (!inputFile.is_open()) {
                throw std::runtime_error("Não foi possível abrir o arquivo: " + filePath);
            }
            std::getline(inputFile, line);
            numLinhas = std::stoi(line);
            voos = new Voo*[numLinhas];
            leVoosdeArquivo(inputFile, voos, numLinhas);
            inputFile.close();
        } else {
            std::getline(std::cin, line);
            numLinhas = std::stoi(line);
            voos = new Voo*[numLinhas];
            leVoosdeEntrada(voos, numLinhas);
        }

        // Indexação inicial
        for (int i = 0; i < numLinhas; i++) {
            indices.inserirVoo(voos[i], i);
        }

        // Loop principal interativo
        std::string comando;
        while (true) {
            std::getline(std::cin, line);
            if (line == "FIM") break;

            if (line[0] == '+') {
                // Adicionar novo voo
                try {
                    std::string dadosVoo = line.substr(2);
                    Voo** novosVoos = new Voo*[numLinhas + 1];
                    for (int i = 0; i < numLinhas; i++) {
                        novosVoos[i] = voos[i];
                    }
                    novosVoos[numLinhas] = new Voo(dadosVoo);
                    indices.inserirVoo(novosVoos[numLinhas], numLinhas);
                    delete[] voos;
                    voos = novosVoos;
                    numLinhas++;
                    std::cout << "Voo adicionado com sucesso." << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Erro ao adicionar voo: " << e.what() << std::endl;
                }
            }
            else if (line[0] == '-') {
                // Remover voo por índice
                try {
                    int idx = std::stoi(line.substr(2));
                    if (idx >= 0 && idx < numLinhas) {
                        delete voos[idx];
                        for (int i = idx; i < numLinhas - 1; i++) {
                            voos[i] = voos[i + 1];
                        }
                        numLinhas--;
                        // Recria índices
                        indices = GerenciadorIndices();
                        for (int i = 0; i < numLinhas; i++) {
                            indices.inserirVoo(voos[i], i);
                        }
                        std::cout << "Voo removido com sucesso." << std::endl;
                    } else {
                        std::cerr << "Índice inválido." << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Erro ao remover voo: " << e.what() << std::endl;
                }
            }
            else {
                // Processar consulta
                try {
                    Consulta consulta;
                    consulta.str = line;
                    std::istringstream iss(line);
                    iss >> consulta.numResultados >> consulta.trigrama >> consulta.expression;

                    ArvoreDeExpressao arvore(consulta.expression);
                    ListaEncadeada<Voo*> voosFiltrados = arvore.filtrarVoos(voos, numLinhas);

                    // Análise e recomendações
                    EstatisticasConsulta stats = analisarResultados(voosFiltrados);
                    ListaEncadeada<std::string> recomendacoes = gerarRecomendacoes(stats);

                    // Processamento e exibição dos resultados
                    int numResultados = std::min(consulta.numResultados, voosFiltrados.GetTamanho());
                    Voo* menoresVoos[numResultados];
                    separarMenoresVoos(voosFiltrados, menoresVoos, numResultados, consulta.trigrama);
                    
                    imprimirVoos(menoresVoos, numResultados);

                    // Exibe recomendações
                    if (!recomendacoes.Vazia()) {
                        std::cout << "\nRecomendações para refinar sua busca:" << std::endl;
                        for (int i = 0; i < recomendacoes.GetTamanho(); i++) {
                            std::cout << "- " << recomendacoes.GetItem(i) << std::endl;
                        }
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Erro ao processar consulta: " << e.what() << std::endl;
                }
            }
        }

        // Liberação de memória
        for (int i = 0; i < numLinhas; i++) {
            delete voos[i];
        }
        delete[] voos;

    } catch (const std::exception& e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
