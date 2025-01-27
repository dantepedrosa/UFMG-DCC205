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


TEST_CASE("Sistema: Teste completo do programa") {
    
    std::string filePath = "./test/load/entrada.csv";
    std::ifstream inputFile(filePath);

    REQUIRE(inputFile.is_open());

    DataHora ref(1, 1, 2000, 0.0);
    Procedimento* procedimentos[6];

    std::string line;
    std::istringstream iss;

    // Inicializa procedimentos
    float duracao;
    int unidades;
    for (int i = 0; i < 6; i++) {
        std::getline(inputFile, line);
        iss.str(line);
        iss >> duracao >> unidades;
        procedimentos[i] = new Procedimento(unidades, duracao, i != TRIAGEM);
        iss.clear();

        CHECK(procedimentos[i]->getNumUnidades() == unidades);
    }

    CHECK(procedimentos[TRIAGEM]->getNumDisponiveis() == 2);
    CHECK(procedimentos[ATENDIMENTO]->getTempoAtendimentoMedio() == 0.5);

    FilaEncadeada<Paciente*> cadastroPacientes;
    int numPacientes;
    std::getline(inputFile, line);
    iss.str(line);
    iss >> numPacientes;
    iss.clear();

    Escalonador escalonador(numPacientes, ref);

    CHECK(escalonador.temEventos() == false);

    // Coloca todos os pacientes no hospital
    for (int i = 0; i < numPacientes; i++) {
        std::getline(inputFile, line);
        Paciente* paciente = new Paciente(line, ref);
        double tempoChegada = paciente->getAdmissaoHZ().getHorasDesdeReferencia();
        Evento chegadaHospital(tempoChegada, paciente, 1);
        cadastroPacientes.enfileira(paciente);
        escalonador.insereEvento(chegadaHospital);

        REQUIRE(tempoChegada >= 0);
        CHECK(escalonador.getTamanho() == i + 1);
        CHECK(cadastroPacientes.getTamanho() == i + 1);
    }

    REQUIRE(escalonador.temEventos() == true);
    CHECK(escalonador.getTamanho() == numPacientes);
    CHECK(cadastroPacientes.getTamanho() == numPacientes);
    int numAltas = 0;
    DataHora dhtest;

    // Processar eventos
    int count = 0;
    do {
        Evento evento = escalonador.retiraProximoEvento();
        double tempoEvento = escalonador.getRelogio();
        Paciente* paciente = evento.getPaciente();
        int tipoEvento = evento.getTipoEvento();

        dhtest = Tempo(tempoEvento, ref).getDataHora();
        std::cout << dhtest.paraString() << ": Evento " << tipoEvento << " com paciente " << paciente->getId() << std::endl;
        REQUIRE(tempoEvento >= 0);

        // Caso evento é finalização de procedimento
        if (tipoEvento % 2 == 1) {
            
            if(tipoEvento != 1){
                int procIndex = (tipoEvento - 3) / 2;
                procedimentos[procIndex]->liberarUnidade(tempoEvento);
            }
            
            int proxProcedimento = paciente->proximaFilaProcedimento();

            // std::cout << "ProxProcedimento: " << proxProcedimento << std::endl;

            if (proxProcedimento >= 0){
                procedimentos[(proxProcedimento - 2) / 2]->enfileira(*paciente, paciente->getUrgencia());
                
                paciente->atualizarEstado(proxProcedimento, tempoEvento);

                dhtest = Tempo(tempoEvento, ref).getDataHora();
                std::cout << dhtest.paraString() << ": Paciente* " << paciente->getId() << " | Estado: " << paciente->estadoParaString() << std::endl;
            }
            else {
                
                REQUIRE(paciente->precisaDeServicos() == false);
                paciente->atualizarEstado(14, tempoEvento);

                dhtest = Tempo(tempoEvento, ref).getDataHora();
                std::cout << dhtest.paraString() << ": Paciente " << paciente->getId() << " | Estado: " << paciente->estadoParaString() << std::endl;
                
                numAltas++;
            }
        }


        // Cria eventos de finalização de procedimento
        // Apenas caso haja pacientes esperando e unidades disponíveis
        for (int i = 0; i < 6; i++) {
            while (procedimentos[i]->unidadeDisponivel() && !procedimentos[i]->filasVazias()) {
                
                Paciente* pacienteFila = procedimentos[i]->desenfileira();

                double horaSaida = tempoEvento + procedimentos[i]->getTempoAtendimentoMedio();
                
                // Coloca para ser atendido
                pacienteFila->atualizarEstado((2 * i) + 3, tempoEvento);
                procedimentos[i]->alocarUnidade(tempoEvento);

                Evento eventoProcedimento(horaSaida, pacienteFila, (2 * i) + 3);
                escalonador.insereEvento(eventoProcedimento);

                dhtest = Tempo(horaSaida, ref).getDataHora();
                std::cout << dhtest.paraString() << "*: Paciente " << pacienteFila->getId() << " | Estado: " << paciente->estadoParaString() << std::endl;
            }
        }

        count++;
        //if(count > 100) {break;}
    } while (escalonador.temEventos());

    REQUIRE(cadastroPacientes.getTamanho() == numAltas);

    inputFile.close();

    // Verificar tempos de atendimento
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
    // Verificar procedimentos realizados
    SUBCASE("Verificar procedimentos realizados") {
        for (Procedimento* proc : procedimentos) {
            CHECK(proc->calcularTempoOcioso() >= 0);
            CHECK(proc->unidadesDisponiveis() > 0);
            delete proc;
        }
    }
    */

    // Verificar saída formatada
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
