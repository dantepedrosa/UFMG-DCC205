#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/doctest.hpp"
#include "../include/Escalonador.hpp"
#include "../include/Fila.hpp"
#include "../include/Paciente.hpp"
#include "../include/Procedimento.hpp"
#include "../include/Tempo.hpp"

#define TRIAGEM 0
#define ATENDIMENTO 1
#define MH 2
#define TL 3
#define EI 4
#define IM 5

TEST_CASE("[sistema]Teste completo do programa") {
    std::string filePath = "../test/load/entrada.csv";
    std::ifstream inputFile(filePath);

    REQUIRE_MESSAGE(inputFile.is_open(), "Erro ao abrir o arquivo: " << filePath);

    DataHora ref(1, 1, 2000, 0.0);
    Procedimento* procedimentos[6];

    std::string line;
    std::istringstream iss;
    int durMin;
    float unidades;

    for (int i = 0; i < 6; i++) {
        std::getline(inputFile, line);
        iss.str(line);
        iss >> durMin >> unidades;
        procedimentos[i] = new Procedimento(unidades, durMin, i != TRIAGEM);
        iss.clear();
    }

    FilaEncadeada<Paciente*> cadastroPacientes;
    int numPacientes;
    std::getline(inputFile, line);
    iss.str(line);
    iss >> numPacientes;
    iss.clear();

    Escalonador escalonador(numPacientes, ref);

    for (int i = 0; i < numPacientes; i++) {
        std::getline(inputFile, line);
        Paciente* paciente = new Paciente(line, ref);
        double tempoChegada = paciente->getAdmissaoHZ().getHorasDesdeReferencia();
        Evento chegadaHospital(tempoChegada, paciente, 1);
        cadastroPacientes.enfileira(paciente);
        escalonador.insereEvento(chegadaHospital);
    }

    do {
        Evento evento = escalonador.retiraProximoEvento();
        double tempoEvento = escalonador.getRelogio();
        Paciente* paciente = evento.getPaciente();
        int tipoEvento = evento.getTipoEvento();

        if (tipoEvento == 1) {
            procedimentos[TRIAGEM]->enfileira(*paciente, paciente->getUrgencia());
            paciente->atualizarEstado(2, tempoEvento);
        }

        if (tipoEvento % 2 == 1 && tipoEvento > 1) {
            int procIndex = (tipoEvento - 3) / 2;
            procedimentos[procIndex]->liberarUnidade(tempoEvento);
            int proxProcedimento = paciente->proximaFilaProcedimento();
            if (proxProcedimento >= 0) {
                procedimentos[(proxProcedimento - 2) / 2]->enfileira(*paciente, paciente->getUrgencia());
                paciente->atualizarEstado(proxProcedimento, tempoEvento);
            }
        }

        for (int i = 0; i < 6; i++) {
            if (procedimentos[i]->unidadeDisponivel() && !procedimentos[i]->filasVazias()) {
                Paciente* pacienteFila = procedimentos[i]->desenfileira();
                procedimentos[i]->alocarUnidade(tempoEvento);
                Evento eventoProcedimento(
                    tempoEvento + procedimentos[i]->getTempoAtendimentoMedio(),
                    pacienteFila,
                    2 * i + 3
                );
                pacienteFila->atualizarEstado(3, tempoEvento);
                escalonador.insereEvento(eventoProcedimento);
            }
        }

    } while (escalonador.temEventos());

    inputFile.close();

    SUBCASE("Verificar tempos de atendimento") {
        while (!cadastroPacientes.filaVazia()) {
            Paciente* paciente = cadastroPacientes.desenfileira();
            CHECK(paciente->getTempoTotalAtendimento() > 0);
            CHECK(paciente->getTempoTotalEspera() >= 0);
            CHECK(paciente->getTempoTotalAtendimento() >= 0);
            delete paciente;
        }
    }

    /*
    SUBCASE("Verificar procedimentos realizados") {
        for (Procedimento* proc : procedimentos) {
            CHECK(proc->calcularTempoOcioso() >= 0);
            CHECK(proc->unidadesDisponiveis() > 0);
            delete proc;
        }
    }
    */

    SUBCASE("Verificar saída formatada") {
        std::ostringstream output;
        while (!cadastroPacientes.filaVazia()) {
            Paciente* paciente = cadastroPacientes.desenfileira();
            output << paciente->imprimeEstatisticas() << std::endl;
            delete paciente;
        }
        CHECK(!output.str().empty());
    }
}
