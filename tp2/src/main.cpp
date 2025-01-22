#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Tempo.hpp"
#include "../include/Paciente.hpp"
#include "../include/Fila.hpp"
#include "../include/Procedimento.hpp"
#include "../include/Escalonador.hpp"

#define DIA_REF 1
#define MES_REF 1
#define ANO_REF 2000
#define HORA_REF 0.0

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


int main(int argc, char const *argv[])
{

    // Erro entrada
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <caminho_para_arquivo>" << std::endl;
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

    int durMin; float unidades;

    // Cria Triagem
    std::getline(inputFile, line);
    std::istringstream iss(line);
    iss >> durMin >> unidades;
    Procedimento triagem("Triagem", unidades, durMin, false);
    
    // Cria Atendimento
    std::getline(inputFile, line);
    iss.clear();
    iss.str(line);
    iss >> durMin >> unidades;
    Procedimento atendimento("Atendimento", unidades, durMin, true);

    // Cria Medidas
    std::getline(inputFile, line);
    iss.clear();
    iss.str(line);
    iss >> durMin >> unidades;
    Procedimento mh("Medidas", unidades, durMin, true);

    // Cria Testes Laboratoriais
    std::getline(inputFile, line);
    iss.clear();
    iss.str(line);
    iss >> durMin >> unidades;
    Procedimento tl("Testes", unidades, durMin, true);

    // Cria Exame de Imagem
    std::getline(inputFile, line);
    iss.clear();
    iss.str(line);
    iss >> durMin >> unidades;
    Procedimento ei("Imagem", unidades, durMin, true);

    // Cria Instrumentos/Medicamentos
    std::getline(inputFile, line);
    iss.clear();
    iss.str(line);
    iss >> durMin >> unidades;
    Procedimento im("Instrumentos/Medicamentos", unidades, durMin, true);

    iss.clear();

    // Criar Pacientes e Escalonar ---------------------------------------------
    // Complexidade: O(n)

    FilaEncadeada<Paciente*> cadastroPacientes;

    int numPacientes;
    std::getline(inputFile, line);
    iss.str(line);
    iss >> numPacientes;
    iss.clear();

    Escalonador escalonador(numPacientes);

    for(int i = 0; i < numPacientes; i++) {
        std::getline(inputFile, line);
        Paciente* paciente = new Paciente(line, ref);
        cadastroPacientes.enfileira(paciente);
        triagem.enfileira(*paciente, paciente->getUrgencia());
    }

    // Processar Eventos -------------------------------------------------------
    // Complexidade: O(?)

    while(escalonador.temEventos()) {
        Evento evento = escalonador.retiraProximoEvento();
        float tempoEvento = escalonador.avancaRelogio();

        
    }


    // Processar Eventos -------------------------------------------------------
    while (escalonador.temEventos()) {
        // Retira o próximo evento a ser processado
        Evento evento = escalonador.retiraProximoEvento();

        // Avança o relógio para o instante do próximo evento
        float tempoEvento = escalonador.avancaRelogio();

        // TODO - Analisar lógica relógio

        // Verifica o estado atual do paciente com base no evento
        Paciente* paciente = evento.getPaciente();

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
                // conferir tempoUltimoEvento (entradaFila) de Paciente e somar tempo gasto em fila em tempoTotalEspera
                // atualizar tempoUltimoEvento de paciente
                // escalonar evento de finalização de triagem para paciente, com horário de termino

        // se evento retirado é 
        
        // Dependendo do tipo de evento, altere o estado do paciente e enfileire-o
        switch (evento.getTipo()) {
            case 1: // Chegada do paciente
                // Todos os pacientes entram na fila de triagem ao chegar
                triagem.enfileira(*paciente, paciente->getUrgencia());

                // Verifica se há unidade disponível para a triagem
                if (triagem.unidadeDisponivel(tempoEvento)) {
                    // Aloca a unidade para triagem e escalona evento de execução
                    int unidade = triagem.alocarUnidade(tempoEvento, triagem.getDuracaoMedia());
                    Evento eventoTriagem(tempoEvento + triagem.getDuracaoMedia(), paciente, 2, unidade);
                    escalonador.insereEvento(eventoTriagem);
                }
                break;

            case 2: // Execução de um procedimento (incluindo triagem)
                // Verifica se o paciente pode continuar com os próximos procedimentos
                if (paciente->temProcedimentoPendentes()) {
                    Procedimento* procedimento = paciente->getProximoProcedimento();
                    
                    // Enfileirar o paciente no próximo procedimento
                    procedimento->enfileira(*paciente, paciente->getUrgencia());
                } else {
                    // Alta hospitalar
                    paciente->finalizaAtendimento();
                }
                break;

            case 3: // Finalização de um procedimento
                // Similar ao código original, libera unidade e escalona próximos eventos
                Procedimento* procedimentoFinalizado = paciente->getProcedimentoEmExecucao();
                procedimentoFinalizado->liberarUnidade(evento.getUnidade(), tempoEvento);
                paciente->finalizaProcedimento();

                // Se o paciente ainda precisar de mais procedimentos, enfileira
                if (paciente->temProcedimentoPendentes()) {
                    Procedimento* proximoProcedimento = paciente->getProximoProcedimento();
                    proximoProcedimento->enfileira(*paciente, paciente->getUrgencia());
                } else {
                    // Alta hospitalar
                    paciente->finalizaAtendimento();
                }
                break;
        }


        // Para cada fila de espera que tenha pacientes, verifica unidades disponíveis
        for (Procedimento* proc : {&triagem, &atendimento, &mh, &tl, &ei, &im}) {
            if (!proc->filaVazia()) {
                if (proc->unidadeDisponivel(tempoEvento)) {
                    Paciente* pacienteFila = proc->desenfileira();
                    int unidade = proc->alocarUnidade(tempoEvento, pacienteFila->getDuracaoProcedimento());
                    Evento eventoExecucao(tempoEvento + pacienteFila->getDuracaoProcedimento(), pacienteFila, 3, unidade);
                    escalonador.insereEvento(eventoExecucao);
                }
            }
        }

        // Atualizar as estatísticas do sistema
        // (Pode ser acumulando tempo ocioso das unidades, tempo de espera dos pacientes, etc)
    }



    inputFile.close();



    // Imprimir Resultados -----------------------------------------------------
    // Complexidade: O(n)

    while (!cadastroPacientes.filaVazia()) {
        Paciente* paciente = cadastroPacientes.desenfileira();
        // Imprimir resultados
        delete paciente;
    }

    return 0;
}


/*
// main

// abrir arquivo - ok

// inicializa variaveis - ok
// para cada linha, chamar função de criar procedimento a partir de string x 6 vezes - ok
// ler numero de linhas - ok


// definir data de referência - ok
// loop de pacientes (linhas) - ok
    // para cada paciente (linhas), chamar função de criar paciente a partir de string.]
    // para cada paciente, enfileirar em cadastroPacientes (os pacientes devem ser impressos na mesma ordem no arquivo de saída)
    // para cada paciente, criado, criar evento de chegada e adicionar ao escalonador
ok

// apos escalonar todos os pacientes - ok
// loop while com temEventos() - ok
    // retirar proximo evento
    // avançar relógio para o instante do próximo evento
    // conferir qual deve ser o proximo estado do paciente (a partir de vários ifs)
    // a depender do próximo estado do paciente
        // se houver mais serviços para paciente
            // enfileirar paciente na fila adequada
        // senão
            // finalizar atendimento (alta hospitalar)
    // para cada fila de espera que tenha pacientes
        // conferir se ha unidade disponivel para procedimento
            // escalonar evento de execução do serviço

    // atualizar estatisticas

// desinfileirar todos os pacientes de cadastroPacientes na ordem, imprimindo também as estatisticas coletadas



*/