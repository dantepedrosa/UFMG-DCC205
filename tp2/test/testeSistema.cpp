#include <fstream>
#include <iostream>
#include <sstream>

#include "../include/doctest.hpp"

#include "../include/Escalonador.hpp"
#include "../include/Fila.hpp"
#include "../include/Paciente.hpp"
#include "../include/Procedimento.hpp"
#include "../include/Tempo.hpp"

#define DIA_REF 1
#define MES_REF 1
#define ANO_REF 2000
#define HORA_REF 0.0

#define TRIAGEM 0
#define ATENDIMENTO 1
#define MH 2
#define TL 3
#define EI 4
#define IM 5

/*
TEST_CASE("[sistema] Testando todas o programa") {

    /*
    // Erro entrada
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <caminho_para_arquivo>"
                  << std::endl;
        return 1;
    }
    
    // abertura de arquivo
    std::string filePath = argv[1];
    *//*
    std::string filePath = "../test/load/entrada.csv";

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
    }

    DataHora ref(DIA_REF, MES_REF, ANO_REF, HORA_REF);

    // Inicializa Procedimentos ------------------------------------------------
    // Complexidade: O(1)

    std::string line;
    std::istringstream iss;

    int durMin;
    float unidades;
    
    Procedimento* procedimentos[6];
    // 0: Triagem, 1: Atendimento, 2: MH, 3: TL, 4: EI, 5: IM

    // Inicializa procedimentos
    for (int i = 0; i < 6; i++) {
        std::getline(inputFile, line);
        iss.str(line);
        iss >> durMin >> unidades;
        if (i == TRIAGEM) // Triagem não tem prioridade
            procedimentos[i] = new Procedimento(unidades, durMin, false);   
        else
            procedimentos[i] = new Procedimento(unidades, durMin, true);
        iss.clear();
    }

    // Criar Pacientes e Escalonar ---------------------------------------------
    // Complexidade: O(n)

    FilaEncadeada<Paciente*> cadastroPacientes;

    // Numero de pacientes
    int numPacientes;
    std::getline(inputFile, line);
    iss.str(line);
    iss >> numPacientes;
    iss.clear();

    Escalonador escalonador(numPacientes, ref);

    // Coloca todos os paciente na no hospital
    for (int i = 0; i < numPacientes; i++) {
        std::getline(inputFile, line);

        Paciente* paciente = new Paciente(line, ref);
        double tempoChegada = paciente->getAdmissaoHZ().getHorasDesdeReferencia();
        Evento chegadaHospital(tempoChegada, paciente, 1);

        cadastroPacientes.enfileira(paciente);  // Para manter a ordem do documento de entrada
        escalonador.insereEvento(chegadaHospital);
    }

    // Processar Eventos -------------------------------------------------------
    // Complexidade: O(?)

    do
    {
        // Inicialização de variaveis uteis
        Evento evento = escalonador.retiraProximoEvento();      // Retira o próximo evento a ser processado    
        double tempoEvento = escalonador.avancaRelogio();       // Avança o relógio para o instante do evento
        Paciente* paciente = evento.getPaciente();
        int tipoEvento = evento.getTipoEvento();

        // Caso seja chegada no CHEGADA NO HZ, enfilera na TRIAGEM
        if(tipoEvento == 1){
            procedimentos[TRIAGEM]->enfileira(*paciente, paciente->getUrgencia());
            paciente->atualizarEstado(2, tempoEvento);     // Evento de entrada na fila
        }

        // Caso evento é finalização de procedimento
        if(tipoEvento % 2 == 1 && tipoEvento > 1){
            int i = (tipoEvento - 3) / 2;
            procedimentos[i]->liberarUnidade(tempoEvento);

            // Identificar próxima fila de procedimento
            int proxProcedimento = paciente->proximaFilaProcedimento();
            int proxFila = (proxProcedimento - 2) / 2;
            // Alocar paciente na proxima fila
            if(proxProcedimento >= 0){
                procedimentos[proxFila]->enfileira(*paciente, paciente->getUrgencia());
                paciente->atualizarEstado(proxProcedimento, tempoEvento);
            }
            else{
                // TODO - Paciente receberá alta
            }
        }
        
        // Cria eventos de finalização procedimento
        // Apenas caso haja pacientes esperando e unidades disponiveis
        for(int i = 0; i < 6; i++){
            if(procedimentos[i]->unidadeDisponivel() && !procedimentos[i]->filasVazias()){
                Paciente* pacienteFila = procedimentos[i]->desenfileira();
                procedimentos[i]->alocarUnidade(tempoEvento);
                Evento eventoProcedimento(tempoEvento + procedimentos[i]->getTempoAtendimentoMedio(), pacienteFila, tipoEvento+1);
                pacienteFila->atualizarEstado(3, tempoEvento);   // Registra entrada no atendimento
                escalonador.insereEvento(eventoProcedimento);   // Evento de início de atendimento
            }
        }
        // TODO - Inserir final do loop

    } while (escalonador.temEventos());


    inputFile.close();

    // Imprimir Resultados -----------------------------------------------------
    // Complexidade: O(n)

    while (!cadastroPacientes.filaVazia()) {
        Paciente* paciente = cadastroPacientes.desenfileira();
        paciente->imprimeEstatisticas();
        delete paciente;
    }
}

*/