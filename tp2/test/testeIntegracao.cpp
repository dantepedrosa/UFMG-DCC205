/*
Inicializa Condição de Término para FALSO
Inicializa as variáveis de estado do sistema
Inicializa o Relógio (usualmente zero)
Escalona a chegada de pacientes
Enquanto houver eventos ou filas não vazias
    Remove o próximo evento do escalonador
    Avança o relógio para o instante do próximo evento
    Verifica o próximo estado do paciente
    Se houver mais serviços para paciente
        Enfileira o paciente na fila adequada
    Senão
        Finaliza o atendimento (Alta Hospitalar)
    Para cada fila de espera que tenha pacientes
        Se há unidade disponível para execução
            Escalonar o evento de execução do serviço
    Atualizar as estatísticas
Fim
Gerar relatórios de estatísticas
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "Paciente.hpp"
#include "Tempo.hpp"
#include "Escalonador.hpp"
#include "Procedimento.hpp"
#include <fstream>
#include <sstream>

TEST_CASE("Teste de integração com arquivo CSV") {
    // Carregar arquivo de entrada
    std::ifstream entrada("test/load/entrada.csv");
    REQUIRE(entrada.is_open());

    std::string linha;
    std::vector<std::string> linhasEntrada;
    while (std::getline(entrada, linha)) {
        linhasEntrada.push_back(linha);
    }
    entrada.close();

    // Carregar arquivo de saída esperado
    std::ifstream saida("test/load/saida.csv");
    REQUIRE(saida.is_open());

    std::vector<std::string> saidaEsperada;
    while (std::getline(saida, linha)) {
        saidaEsperada.push_back(linha);
    }
    saida.close();

    // Inicializar variáveis de estado do sistema
    Escalonador escalonador(100);
    escalonador.inicializa(0.0);

    // Inicializar procedimentos a partir do arquivo CSV
    std::vector<Procedimento> procedimentos;
    for (size_t i = 1; i < 7; ++i) { // As primeiras 6 linhas são de especificações de procedimentos
        std::istringstream iss(linhasEntrada[i]);
        std::string nome;
        int unidades;
        double duracao;
        iss >> nome >> unidades >> duracao;
        procedimentos.emplace_back(nome, unidades, duracao);
    }

    // Escalonar a chegada de pacientes
    DataHora ref(21, 3, 2017, 0.0);
    for (size_t i = 7; i < linhasEntrada.size(); ++i) {
        std::istringstream iss(linhasEntrada[i]);
        std::string id_str, dummy;
        int id, urgencia, mh, tl, ei, im;
        iss >> id_str >> dummy >> dummy >> dummy >> dummy >> dummy >> urgencia >> mh >> tl >> ei >> im;
        id = std::stoi(id_str.substr(3)); // Remover os três primeiros zeros do ID
        DataHora admissao(21, 3, 2017, 2.0); // Exemplo de admissão
        Tempo tAdmissao(admissao, ref);
        Paciente* p = new Paciente(id, false, tAdmissao, urgencia, mh, tl, ei, im);
        Evento e(tAdmissao, p, 1);
        escalonador.insereEvento(e);
    }

    // Processar eventos
    while (escalonador.temEventos()) {
        Evento e = escalonador.retiraProximoEvento();
        escalonador.avancaRelogio();

        Paciente* p = e.paciente;
        if (p->getEstado() < 14) {
            p->atualizarEstado(p->getEstado() + 1, e.dataHora);
            Evento novoEvento(e.dataHora, p, p->getEstado());
            escalonador.insereEvento(novoEvento);
        }
    }

    // Verificar saída
    for (size_t i = 0; i < saidaEsperada.size(); ++i) {
        std::ostringstream oss;
        oss << saidaEsperada[i];
        CHECK(oss.str() == saidaEsperada[i]);
    }
}