#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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
#define DIA_REF 1
#define MES_REF 1
#define ANO_REF 2000
#define HORA_REF 0.0


int main(int argc, char const* argv[]) {
    // Erro entrada
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <caminho_para_arquivo>"
                  << std::endl;
        return 1;
    }

    // abertura de arquivo
    std::string filePath = argv[1];

    std::ifstream inputFile(filePath);

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

    }



    FilaEncadeada<Paciente*> cadastroPacientes;
    int numPacientes;
    std::getline(inputFile, line);
    iss.str(line);
    iss >> numPacientes;
    iss.clear();

    Escalonador escalonador(numPacientes, ref);

    // Coloca todos os pacientes no hospital
    for (int i = 0; i < numPacientes; i++) {
        std::getline(inputFile, line);
        Paciente* paciente = new Paciente(line, ref);
        double tempoChegada = paciente->getAdmissaoHZ().getHorasDesdeReferencia();
        Evento chegadaHospital(tempoChegada, paciente, 1);
        cadastroPacientes.enfileira(paciente);
        escalonador.insereEvento(chegadaHospital);
    }

    inputFile.close();

    // Processar eventos
    do {
        Evento evento = escalonador.retiraProximoEvento();
        double tempoEvento = escalonador.getRelogio();
        Paciente* paciente = evento.getPaciente();
        int tipoEvento = evento.getTipoEvento();

        // Caso evento é finalização de procedimento
        if (tipoEvento % 2 == 1) {
            
            if(tipoEvento != 1){
                int procIndex = (tipoEvento - 3) / 2;
                procedimentos[procIndex]->liberarUnidade(tempoEvento);
            }
            
            int proxProcedimento = paciente->proximaFilaProcedimento();

            if (proxProcedimento >= 0){
                procedimentos[(proxProcedimento - 2) / 2]->enfileira(*paciente, paciente->getUrgencia());
                
                paciente->atualizarEstado(proxProcedimento, tempoEvento);

            }
            else {
                paciente->atualizarEstado(14, tempoEvento);
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
            }
        }


    } while (escalonador.temEventos());

    // Imprime estatísticas
    std::ostringstream output;
        while (!cadastroPacientes.filaVazia()) {
            Paciente* paciente = cadastroPacientes.desenfileira();
            output << paciente->imprimeEstatisticas() << std::endl;
            delete paciente;
        }    
}
