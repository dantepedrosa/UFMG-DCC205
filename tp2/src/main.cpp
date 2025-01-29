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

    // abertura de arquivo  - O(1)
    std::string filePath = argv[1];

    std::ifstream inputFile(filePath);

    DataHora ref(1, 1, 2000, 0.0);
    Procedimento* procedimentos[6];

    std::string line;
    std::istringstream iss;

    // Inicializa procedimentos - O(1)
    float duracao;
    int unidades;
    for (int i = 0; i < 6; i++) {
        std::getline(inputFile, line);
        iss.str(line);
        iss >> duracao >> unidades;
        procedimentos[i] = new Procedimento(unidades, duracao, i != TRIAGEM);
        iss.clear();

    }

    // Registra o número de pacientes - O(1)
    FilaEncadeada<Paciente*> cadastroPacientes;
    int numPacientes;
    std::getline(inputFile, line);
    iss.str(line);
    iss >> numPacientes;
    iss.clear();

    Escalonador escalonador(numPacientes, ref);

    // Coloca todos os pacientes no hospital - O(nlogn)
    for (int i = 0; i < numPacientes; i++) {    // O(n)
        std::getline(inputFile, line);
        Paciente* paciente = new Paciente(line, ref);
        double tempoChegada = paciente->getAdmissaoHZ().getHorasDesdeReferencia();
        Evento chegadaHospital(tempoChegada, paciente, 1);
        cadastroPacientes.enfileira(paciente);      // O(1)
        escalonador.insereEvento(chegadaHospital);  // O(logn)
    }

    inputFile.close();

    // Processar eventos - O(mlogm)
    do {
        Evento evento = escalonador.retiraProximoEvento();  // O(logm)
        double tempoEvento = escalonador.getRelogio();
        Paciente* paciente = evento.getPaciente();
        int tipoEvento = evento.getTipoEvento();

        // Caso evento é finalização de procedimento - O(1)
        if (tipoEvento % 2 == 1) {
            
            if(tipoEvento != 1){    // O(1)
                int procIndex = (tipoEvento - 3) / 2;
                procedimentos[procIndex]->liberarUnidade(tempoEvento);
            }
            
            int proxProcedimento = paciente->proximaFilaProcedimento();

            if (proxProcedimento >= 0){ // O(1)
                procedimentos[(proxProcedimento - 2) / 2]->enfileira(*paciente, paciente->getUrgencia());
                
                paciente->atualizarEstado(proxProcedimento, tempoEvento);

            }
            else {  // O(1)
                paciente->atualizarEstado(14, tempoEvento);
            }
        }


        // Cria eventos de finalização de procedimento, retirando pacientes da fila - O(1)
        for (int i = 0; i < 6; i++) {
            // Apenas caso haja pacientes esperando e unidades disponíveis
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


    } while (escalonador.temEventos()); // O(m) - m é o número de eventos = pacientes * procedimentos

    // Imprime estatísticas - O(n)
    std::ostringstream output;
        while (!cadastroPacientes.filaVazia()) {
            Paciente* paciente = cadastroPacientes.desenfileira();
            output << paciente->imprimeEstatisticas() << std::endl;
            delete paciente;
        }    
}
