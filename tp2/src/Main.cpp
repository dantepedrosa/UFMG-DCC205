#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../include/DataHora.hpp"
#include "../include/Paciente.hpp"
#include "../include/Fila.hpp"
#include "../include/Procedimento.hpp"
#include "../include/Escalonador.hpp"

void inicializaSistema(Escalonador& escalonador, std::vector<Paciente>& pacientes, const std::string& arquivoEntrada) {
    std::ifstream file(arquivoEntrada);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Leitura das especificações do hospital
    float tempoTriagem, tempoAtendimento, tempoMedidas, tempoTestes, tempoImagem, tempoInstrumentos;
    int unidadesTriagem, unidadesAtendimento, unidadesMedidas, unidadesTestes, unidadesImagem, unidadesInstrumentos;
    file >> tempoTriagem >> unidadesTriagem;
    file >> tempoAtendimento >> unidadesAtendimento;
    file >> tempoMedidas >> unidadesMedidas;
    file >> tempoTestes >> unidadesTestes;
    file >> tempoImagem >> unidadesImagem;
    file >> tempoInstrumentos >> unidadesInstrumentos;

    // Inicializa procedimentos
    Procedimento triagem("Triagem", unidadesTriagem, tempoTriagem);
    Procedimento atendimento("Atendimento", unidadesAtendimento, tempoAtendimento);
    Procedimento medidas("Medidas Hospitalares", unidadesMedidas, tempoMedidas);
    Procedimento testes("Testes de Laboratório", unidadesTestes, tempoTestes);
    Procedimento imagem("Exames de Imagem", unidadesImagem, tempoImagem);
    Procedimento instrumentos("Instrumentos/Medicamentos", unidadesInstrumentos, tempoInstrumentos);

    // Leitura dos pacientes
    int numPacientes;
    file >> numPacientes;
    for (int i = 0; i < numPacientes; ++i) {
        int id, urgencia, ano, mes, dia, hora, minuto, segundo, mh, tl, ei, im;
        file >> id >> urgencia >> ano >> mes >> dia >> hora >> minuto >> segundo >> mh >> tl >> ei >> im;
        DataHora admissao(dia, mes, ano, hora + minuto / 60.0);
        Paciente paciente(id, urgencia == 1, Tempo(admissao, admissao), urgencia, mh, tl, ei, im);
        pacientes.push_back(paciente);
        escalonador.insereEvento(Evento(Tempo(admissao, admissao), &paciente, 1)); // Evento de chegada
    }

    file.close();
}

void processaEvento(Escalonador& escalonador, Paciente& paciente, std::vector<Fila<Paciente>>& filas, std::vector<Procedimento>& procedimentos) {
    // Processa o próximo evento do paciente
    int estado = paciente.getEstado();
    Tempo dataHoraAtual = escalonador.getRelogio();

    switch (estado) {
        case 1: // Chegada
            paciente.atualizarEstado(2, dataHoraAtual);
            filas[0].enfileira(paciente);
            break;
        case 2: // Na fila de triagem
            if (procedimentos[0].unidadeDisponivel(dataHoraAtual)) {
                int unidade = procedimentos[0].alocarUnidade(dataHoraAtual, procedimentos[0].getTempoAtendimentoMedio());
                paciente.atualizarEstado(3, dataHoraAtual);
                escalonador.insereEvento(Evento(dataHoraAtual + procedimentos[0].getTempoAtendimentoMedio(), &paciente, 3));
            }
            break;
        case 3: // Sendo triado
            paciente.atualizarEstado(4, dataHoraAtual);
            filas[1].enfileira(paciente);
            procedimentos[0].liberarUnidade(0, dataHoraAtual);
            break;
        case 4: // Na fila de atendimento
            if (procedimentos[1].unidadeDisponivel(dataHoraAtual)) {
                int unidade = procedimentos[1].alocarUnidade(dataHoraAtual, procedimentos[1].getTempoAtendimentoMedio());
                paciente.atualizarEstado(5, dataHoraAtual);
                escalonador.insereEvento(Evento(dataHoraAtual + procedimentos[1].getTempoAtendimentoMedio(), &paciente, 5));
            }
            break;
        case 5: // Sendo atendido
            if (paciente.getNumMH() == 0 && paciente.getNumTL() == 0 && paciente.getNumEI() == 0 && paciente.getNumIM() == 0) {
                paciente.atualizarEstado(14, dataHoraAtual);
                paciente.saidaHZ = dataHoraAtual;
            } else {
                paciente.atualizarEstado(6, dataHoraAtual);
                filas[2].enfileira(paciente);
            }
            procedimentos[1].liberarUnidade(0, dataHoraAtual);
            break;
        case 6: // Na fila de medidas hospitalares
            if (procedimentos[2].unidadeDisponivel(dataHoraAtual)) {
                int unidade = procedimentos[2].alocarUnidade(dataHoraAtual, procedimentos[2].getTempoAtendimentoMedio());
                paciente.atualizarEstado(7, dataHoraAtual);
                escalonador.insereEvento(Evento(dataHoraAtual + procedimentos[2].getTempoAtendimentoMedio(), &paciente, 7));
            }
            break;
        case 7: // Realizando medidas hospitalares
            paciente.atualizarEstado(8, dataHoraAtual);
            filas[3].enfileira(paciente);
            procedimentos[2].liberarUnidade(0, dataHoraAtual);
            break;
        case 8: // Na fila de testes de laboratório
            if (procedimentos[3].unidadeDisponivel(dataHoraAtual)) {
                int unidade = procedimentos[3].alocarUnidade(dataHoraAtual, procedimentos[3].getTempoAtendimentoMedio());
                paciente.atualizarEstado(9, dataHoraAtual);
                escalonador.insereEvento(Evento(dataHoraAtual + procedimentos[3].getTempoAtendimentoMedio(), &paciente, 9));
            }
            break;
        case 9: // Realizando testes de laboratório
            paciente.atualizarEstado(10, dataHoraAtual);
            filas[4].enfileira(paciente);
            procedimentos[3].liberarUnidade(0, dataHoraAtual);
            break;
        case 10: // Na fila de exames de imagem
            if (procedimentos[4].unidadeDisponivel(dataHoraAtual)) {
                int unidade = procedimentos[4].alocarUnidade(dataHoraAtual, procedimentos[4].getTempoAtendimentoMedio());
                paciente.atualizarEstado(11, dataHoraAtual);
                escalonador.insereEvento(Evento(dataHoraAtual + procedimentos[4].getTempoAtendimentoMedio(), &paciente, 11));
            }
            break;
        case 11: // Realizando exames de imagem
            paciente.atualizarEstado(12, dataHoraAtual);
            filas[5].enfileira(paciente);
            procedimentos[4].liberarUnidade(0, dataHoraAtual);
            break;
        case 12: // Na fila para instrumentos/medicamentos
            if (procedimentos[5].unidadeDisponivel(dataHoraAtual)) {
                int unidade = procedimentos[5].alocarUnidade(dataHoraAtual, procedimentos[5].getTempoAtendimentoMedio());
                paciente.atualizarEstado(13, dataHoraAtual);
                escalonador.insereEvento(Evento(dataHoraAtual + procedimentos[5].getTempoAtendimentoMedio(), &paciente, 13));
            }
            break;
        case 13: // Sendo aplicados instrumentos/medicamentos
            paciente.atualizarEstado(14, dataHoraAtual);
            paciente.saidaHZ = dataHoraAtual;
            procedimentos[5].liberarUnidade(0, dataHoraAtual);
            break;
        default:
            break;
    }
}

void gerarRelatorios(const std::vector<Paciente>& pacientes) {
    for (const auto& paciente : pacientes) {
        std::cout << paciente.getId() << " "
                  << paciente.getAdmissaoHZ().paraString() << " "
                  << paciente.getSaidaHZ().paraString() << " "
                  << paciente.getTempoTotalAtendimento() << " "
                  << paciente.getTempoTotalEspera() << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.csv>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string arquivoEntrada = argv[1];
    Escalonador escalonador(100); // Capacidade máxima do heap
    std::vector<Paciente> pacientes;
    std::vector<Fila<Paciente>> filas(6); // 6 filas de atendimento
    std::vector<Procedimento> procedimentos;

    inicializaSistema(escalonador, pacientes, arquivoEntrada);

    while (escalonador.temEventos() || !filas.empty()) {
        Evento evento = escalonador.retiraProximoEvento();
        escalonador.avancaRelogio();
        processaEvento(escalonador, *evento.paciente, filas, procedimentos);
    }

    gerarRelatorios(pacientes);

    return 0;
}