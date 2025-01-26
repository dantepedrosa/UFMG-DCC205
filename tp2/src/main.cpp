#include <fstream>
#include <iostream>
#include <sstream>

#include "../include/Escalonador.hpp"
#include "../include/Fila.hpp"
#include "../include/Paciente.hpp"
#include "../include/Procedimento.hpp"
#include "../include/Tempo.hpp"

#define DIA_REF 1
#define MES_REF 1
#define ANO_REF 2000
#define HORA_REF 0.0


/*
PSEUDOCÓDIGO
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
    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
        return 1;
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
        double tempoEvento = escalonador.getRelogio();
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

    return 0;
}



    // Processar Eventos -------------------------------------------------------
    // Complexidade: O(?)

    /*
        // se evento retirado é finalização de atendimento de paciente1:
            // registrar soma de horas em atendimento em paciente1
            // verificar se paciente1 possui mais procedimentos
            // se alguma unidade de procedimento está disponivel
                // ocupar unidade disponível
                // escalonar evento de termino de atendimento de paciente1
            // se nao
                // enfileirar paciente no próximo procedimento
        // senão
            // finalizar atendimento (alta hospitalar):
            // calcular tempo total de cada atendimento para paciente
            // calcular tempo total gasto em fila para paciente
            // liberar unidade

        // para cada procedimento, se houver unidade de atendimento disponivel
            // se tiver paciente na fila:
                // retirar paciente de fila de espera e conferir relogio
                // conferir tempoUltimoEvento (entradaFila) de Paciente e somar
       tempo gasto em fila em tempoTotalEspera atualizar tempoUltimoEvento de
       paciente
                // escalonar evento de finalização de triagem para paciente, com
       horário de termino

        // TODO - Completar se evento retirado é

        // Dependendo do tipo de evento, altere o estado do paciente e
       enfileire-o
    */
    /*
    switch (evento.getTipoEvento()) {
        case 1: // Chegada do paciente
            // Todos os pacientes entram na fila de triagem ao chegar
            triagem.enfileira(*paciente, paciente->getUrgencia());

            // Verifica se há unidade disponível para a triagem
            if (triagem.unidadeDisponivel(tempoEvento)) {
                // Aloca a unidade para triagem e escalona evento de execução
                int unidade = triagem.alocarUnidade(tempoEvento,
    triagem.getDuracaoMedia()); Evento eventoTriagem(tempoEvento +
    triagem.getDuracaoMedia(), paciente, 2, unidade);
                escalonador.insereEvento(eventoTriagem);
            }
            break;

        case 2: // Execução de um procedimento (incluindo triagem)
            // Verifica se o paciente pode continuar com os próximos
    procedimentos if (paciente->temProcedimentoPendentes()) { Procedimento*
    procedimento = paciente->getProximoProcedimento();

                // Enfileirar o paciente no próximo procedimento
                procedimento->enfileira(*paciente, paciente->getUrgencia());
            } else {
                // Alta hospitalar
                paciente->finalizaAtendimento();
            }
            break;

        case 3: // Finalização de um procedimento
            // Similar ao código original, libera unidade e escalona próximos
    eventos Procedimento* procedimentoFinalizado =
    paciente->getProcedimentoEmExecucao();
            procedimentoFinalizado->liberarUnidade(evento.getUnidade(),
    tempoEvento); paciente->finalizaProcedimento();

            // Se o paciente ainda precisar de mais procedimentos, enfileira
            if (paciente->temProcedimentoPendentes()) {
                Procedimento* proximoProcedimento =
    paciente->getProximoProcedimento();
                proximoProcedimento->enfileira(*paciente,
    paciente->getUrgencia()); } else {
                // Alta hospitalar
                paciente->finalizaAtendimento();
            }
            break;
    }


    // Para cada fila de espera que tenha pacientes, verifica unidades
    disponíveis for (Procedimento* proc : {&triagem, &atendimento, &mh, &tl,
    &ei, &im}) { if (!proc->filaVazia()) { if
    (proc->unidadeDisponivel(tempoEvento)) { Paciente* pacienteFila =
    proc->desenfileira(); int unidade = proc->alocarUnidade(tempoEvento,
    pacienteFila->getDuracaoProcedimento()); Evento eventoExecucao(tempoEvento +
    pacienteFila->getDuracaoProcedimento(), pacienteFila, 3, unidade);
                escalonador.insereEvento(eventoExecucao);
            }
        }
    }
    */
    // Atualizar as estatísticas do sistema
    // (Pode ser acumulando tempo ocioso das unidades, tempo de espera dos
    // pacientes, etc)



/*
// main

// abrir arquivo - ok

// inicializa variaveis - ok
// para cada linha, chamar função de criar procedimento a partir de string x 6
vezes - ok
// ler numero de linhas - ok


// definir data de referência - ok
// loop de pacientes (linhas) - ok
    // para cada paciente (linhas), chamar função de criar paciente a partir de
string.]
    // para cada paciente, enfileirar em cadastroPacientes (os pacientes devem
ser impressos na mesma ordem no arquivo de saída)
    // para cada paciente, criado, criar evento de chegada e adicionar ao
escalonador ok

// apos escalonar todos os pacientes - ok
// loop while com temEventos() - ok
    // retirar proximo evento
    // avançar relógio para o instante do próximo evento
    // conferir qual deve ser o proximo estado do paciente (a partir de vários
ifs)
    // a depender do próximo estado do paciente
        // se houver mais serviços para paciente
            // enfileirar paciente na fila adequada
        // senão
            // finalizar atendimento (alta hospitalar)
    // para cada fila de espera que tenha pacientes
        // conferir se ha unidade disponivel para procedimento
            // escalonar evento de execução do serviço

    // atualizar estatisticas

// desinfileirar todos os pacientes de cadastroPacientes na ordem, imprimindo
também as estatisticas coletadas



*/