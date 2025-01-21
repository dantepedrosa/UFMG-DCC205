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
#include "../include/Paciente.hpp"
#include "../include/Tempo.hpp"
#include "../include/Escalonador.hpp"
#include "../include/Procedimento.hpp"
#include <fstream>
#include <sstream>


TEST_CASE("Teste de integração com enfileiramento e desenfileiramento de pacientes") {
    Procedimento procedimento("Procedimento Geral", 3, 0.5, false);

    DataHora ref(1, 1, 2025, 0.0);
    Tempo admissao1(DataHora(1, 1, 2025, 1.0), ref);
    Tempo admissao2(DataHora(1, 1, 2025, 2.0), ref);
    Tempo admissao3(DataHora(1, 1, 2025, 3.0), ref);

    Paciente paciente1(1, false, admissao1, 0, 0, 0, 0, 0);
    Paciente paciente2(2, false, admissao2, 0, 0, 0, 0, 0);
    Paciente paciente3(3, false, admissao3, 0, 0, 0, 0, 0);

    procedimento.enfileira(paciente1);
    procedimento.enfileira(paciente2);
    procedimento.enfileira(paciente3);

    Paciente desenfileirado1 = procedimento.desenfileira();
    CHECK(desenfileirado1.getId() == 1);

    Paciente desenfileirado2 = procedimento.desenfileira();
    CHECK(desenfileirado2.getId() == 2);

    Paciente desenfileirado3 = procedimento.desenfileira();
    CHECK(desenfileirado3.getId() == 3);
}

TEST_CASE("Teste de integração com escalonador simples") {
    Escalonador escalonador(10);

    DataHora ref(1, 1, 2025, 0.0);
    Tempo admissao1(DataHora(1, 1, 2025, 1.0), ref);
    Tempo admissao2(DataHora(1, 1, 2025, 2.0), ref);
    Tempo admissao3(DataHora(1, 1, 2025, 3.0), ref);

    Paciente paciente1(1, false, admissao1, 0, 0, 0, 0, 0);
    Paciente paciente2(2, false, admissao2, 0, 0, 0, 0, 0);
    Paciente paciente3(3, false, admissao3, 0, 0, 0, 0, 0);

    Evento evento1(admissao1, &paciente1, 1);
    Evento evento2(admissao2, &paciente2, 1);
    Evento evento3(admissao3, &paciente3, 1);

    escalonador.insereEvento(evento1);
    escalonador.insereEvento(evento2);
    escalonador.insereEvento(evento3);

    Evento proximoEvento1 = escalonador.retiraProximoEvento();
    CHECK(proximoEvento1.paciente->getId() == 1);

    Evento proximoEvento2 = escalonador.retiraProximoEvento();
    CHECK(proximoEvento2.paciente->getId() == 2);

    Evento proximoEvento3 = escalonador.retiraProximoEvento();
    CHECK(proximoEvento3.paciente->getId() == 3);
}

TEST_CASE("Teste de integração com diferentes níveis de urgência") {
    Procedimento procedimento("Procedimento com Urgência", 3, 0.5, true);

    DataHora ref(1, 1, 2025, 0.0);
    Tempo admissao1(DataHora(1, 1, 2025, 1.0), ref);
    Tempo admissao2(DataHora(1, 1, 2025, 2.0), ref);
    Tempo admissao3(DataHora(1, 1, 2025, 3.0), ref);

    Paciente paciente1(1, false, admissao1, 0, 0, 0, 0, 0);
    Paciente paciente2(2, false, admissao2, 0, 0, 0, 0, 0);
    Paciente paciente3(3, false, admissao3, 0, 0, 0, 0, 0);

    procedimento.enfileira(paciente1, 0); // Verde
    procedimento.enfileira(paciente2, 1); // Amarelo
    procedimento.enfileira(paciente3, 2); // Vermelho

    Paciente desenfileirado1 = procedimento.desenfileira();
    CHECK(desenfileirado1.getId() == 3); // Vermelho tem prioridade

    Paciente desenfileirado2 = procedimento.desenfileira();
    CHECK(desenfileirado2.getId() == 2); // Amarelo tem prioridade

    Paciente desenfileirado3 = procedimento.desenfileira();
    CHECK(desenfileirado3.getId() == 1); // Verde tem prioridade
}

TEST_CASE("Teste de integração com exceções") {
    Procedimento procedimento("Procedimento Geral", 3, 0.5, false);

    CHECK_THROWS_AS(procedimento.desenfileira(), std::runtime_error);

    DataHora ref(1, 1, 2025, 0.0);
    Tempo t1(DataHora(1, 1, 2025, 1.0), ref);

    CHECK_THROWS_AS(procedimento.alocarUnidade(t1, 0.2), std::runtime_error);
    CHECK_THROWS_AS(procedimento.liberarUnidade(-1, t1), std::out_of_range);
    CHECK_THROWS_AS(procedimento.liberarUnidade(3, t1), std::out_of_range);
}