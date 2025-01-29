#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>

#include "../include/Escalonador.hpp"
#include "../include/Fila.hpp"
#include "../include/Paciente.hpp"
#include "../include/Procedimento.hpp"
#include "../include/Tempo.hpp"
#include "../include/doctest.hpp"

#define TRIAGEM 0
#define ATENDIMENTO 1
#define MH 2
#define TL 3
#define EI 4
#define IM 5
#define DIA_REF 1
#define MES_REF 1
#define ANO_REF 2000
#define HORA_REF 0.0

TEST_CASE("Sistema: Teste completo do programa") {

    unsigned int contEventos = 0;
    unsigned int contPacientes = 0;

    

    


    // Define variaveis para captura de tempo
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> tInit, tCadastro, tInitEvento, tEndProcedimento, tFilasEvento, tStat;

    int numDados = 100;
    while (numDados < 143133) {

        // Capture o tempo de início de cadastro
        start = std::chrono::high_resolution_clock::now();

        std::string filePath = "./test/load/20242TP2.csv";

        std::ifstream inputFile(filePath);

        DataHora ref(1, 1, 2000, 0.0);
        Procedimento* procedimentos[6];

        std::string line;
        std::istringstream iss;

        // Inicializa procedimentos
        float duracao[6];
        int unidades[6];
        for (int i = 0; i < 6; i++) {
            std::getline(inputFile, line);
            iss.str(line);
            iss >> duracao[i] >> unidades[i];
            iss.clear();
        }

        int numPacientes;
        std::getline(inputFile, line);
        iss.str(line);
        iss >> numPacientes;
        iss.clear();

        // Inicializa procedimentos
        for (int i = 0; i < 6; i++) {
            procedimentos[i] = new Procedimento(unidades[i], duracao[i], i != TRIAGEM);
        }

        FilaEncadeada<Paciente*> cadastroPacientes;
        Escalonador escalonador(numPacientes, ref);

        // Captura tempo de cadastro
        end = std::chrono::high_resolution_clock::now();
        tInit = end - start;

        // Capture o tempo de início de cadastro
        start = std::chrono::high_resolution_clock::now();

        // Coloca todos os pacientes no hospital
        for (int i = 0; i < numDados; i++) {
            std::getline(inputFile, line);
            Paciente* paciente = new Paciente(line, ref);
            double tempoChegada =
                paciente->getAdmissaoHZ().getHorasDesdeReferencia();
            Evento chegadaHospital(tempoChegada, paciente, 1);
            cadastroPacientes.enfileira(paciente);
            escalonador.insereEvento(chegadaHospital);

            // Captura quantidade de eventos/pacientes
            contEventos++;
            contPacientes++;
        }

        // Captura tempo de cadastro
        end = std::chrono::high_resolution_clock::now();
        tCadastro = end - start;


        // Processar eventos
        do {

            // Capture o tempo de início de processamento de evento
            start = std::chrono::high_resolution_clock::now();

            Evento evento = escalonador.retiraProximoEvento();
            double tempoEvento = escalonador.getRelogio();
            Paciente* paciente = evento.getPaciente();
            int tipoEvento = evento.getTipoEvento();

            // Captura tempo de cadastro
            end = std::chrono::high_resolution_clock::now();
            tInitEvento = end - start;

            // Capture o tempo de início de finalização de procedimento
            start = std::chrono::high_resolution_clock::now();

            // Caso evento é finalização de procedimento
            if (tipoEvento % 2 == 1) {
                if (tipoEvento != 1) {
                    int procIndex = (tipoEvento - 3) / 2;
                    procedimentos[procIndex]->liberarUnidade(tempoEvento);
                }

                int proxProcedimento = paciente->proximaFilaProcedimento();

                if (proxProcedimento >= 0) {
                    procedimentos[(proxProcedimento - 2) / 2]->enfileira(
                        *paciente, paciente->getUrgencia());

                    paciente->atualizarEstado(proxProcedimento, tempoEvento);

                } else {
                    paciente->atualizarEstado(14, tempoEvento);
                }
            }

            // Captura tempo de finalização de procedimento
            end = std::chrono::high_resolution_clock::now();
            tEndProcedimento = end - start;


            // Captura tempo de criação retirada filas e criação evento
            start = std::chrono::high_resolution_clock::now();

            // Cria eventos de finalização de procedimento
            // Apenas caso haja pacientes esperando e unidades disponíveis
            for (int i = 0; i < 6; i++) {
                while (procedimentos[i]->unidadeDisponivel() &&
                       !procedimentos[i]->filasVazias()) {
                    Paciente* pacienteFila = procedimentos[i]->desenfileira();

                    double horaSaida =
                        tempoEvento +
                        procedimentos[i]->getTempoAtendimentoMedio();

                    // Coloca para ser atendido
                    pacienteFila->atualizarEstado((2 * i) + 3, tempoEvento);
                    procedimentos[i]->alocarUnidade(tempoEvento);

                    Evento eventoProcedimento(horaSaida, pacienteFila,
                                              (2 * i) + 3);
                    escalonador.insereEvento(eventoProcedimento);

                    contEventos++;
                }
            }

            // Captura tempo de criação retirada filas e criação evento
            end = std::chrono::high_resolution_clock::now();
            tFilasEvento = end - start;

        } while (escalonador.temEventos());


        // Captura tempo de impressão de estatísticas
        start = std::chrono::high_resolution_clock::now();

        // Imprime estatísticas
        std::ostringstream output;
        while (!cadastroPacientes.filaVazia()) {
            Paciente* paciente = cadastroPacientes.desenfileira();
            //output << paciente->imprimeEstatisticas() << std::endl;
            delete paciente;
        }

        // Captura tempo de impressão de estatísticas
        end = std::chrono::high_resolution_clock::now();
        tStat = end - start;

        
        // Imprimir dados de tempo
        std::cout 
            << numDados << " "
            << contPacientes << " "
            << contEventos << " "
            << tInit.count() << " "
            << tCadastro.count() << " "
            << tInitEvento.count() << " "
            << tEndProcedimento.count() << " "
            << tFilasEvento.count() << " "
            << tStat.count() << std::endl;


        numDados += 1400;
        contPacientes = 0;
        contEventos = 0;

        // Apaga todos os dados utilizados no loop para outra iteração
        for (int i = 0; i < 6; i++) {
            delete procedimentos[i];
        }

        inputFile.close();

    }

    ;




}
