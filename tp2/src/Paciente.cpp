#include "Paciente.hpp"

Paciente::Paciente() 
    : id(0), altaImediata(false), admissaoHZ(), grauUrgencia(0),
      numMH(0), numTL(0), numEI(0), numIM(0), estado(1), tempoUltimoEvento(),
      tempoTotalAtendimento(0.0), tempoTotalEspera(0.0) {
    procedimentosPendentes = new int[4]{0, 0, 0, 0};
    temposEspera = new float[14]{0.0};
    temposAtendimento = new float[14]{0.0};
}

Paciente::Paciente(int id, bool alta, const Tempo& admissao, int urgencia, int mh, int tl, int ei, int im)
    : id(id), altaImediata(alta), admissaoHZ(admissao), grauUrgencia(urgencia),
      numMH(mh), numTL(tl), numEI(ei), numIM(im), estado(2), tempoUltimoEvento(admissao),
      tempoTotalAtendimento(0.0), tempoTotalEspera(0.0) {
    procedimentosPendentes = new int[4]{mh, tl, ei, im};
    temposEspera = new float[14]{0.0};
    temposAtendimento = new float[14]{0.0};
}

Paciente::~Paciente() {
    delete[] procedimentosPendentes;
    delete[] temposEspera;
    delete[] temposAtendimento;
}

void Paciente::atualizarEstado(int novoEstado, const Tempo& dataHoraAtual) {
    float tempoDecorrido = dataHoraAtual.getHorasDesdeReferencia() - tempoUltimoEvento.getHorasDesdeReferencia();
    if (estado % 2 == 0) { // Se o estado é par, é tempo de espera
        registrarEspera(tempoDecorrido);
    } else { // Se o estado é ímpar, é tempo de atendimento
        registrarAtendimento(tempoDecorrido);
    }
    estado = novoEstado;
    tempoUltimoEvento = dataHoraAtual;
}

void Paciente::registrarEspera(float tempo) {
    temposEspera[estado - 1] += tempo; // Corrigir índice do estado
    tempoTotalEspera += tempo;
}

void Paciente::registrarAtendimento(float tempo) {
    temposAtendimento[estado - 1] += tempo; // Corrigir índice do estado
    tempoTotalAtendimento += tempo;
}

int Paciente::getEstado() const {
    return estado;
}

std::string Paciente::estadoParaString() const {
    static const char* estados[] = {
        "Não chegou ainda ao hospital", "Na fila de triagem", "Sendo triado",
        "Na fila de atendimento", "Sendo atendido", "Na fila de medidas hospitalares",
        "Realizando medidas hospitalares", "Na fila de testes de laboratório",
        "Realizando testes de laboratório", "Na fila de exames de imagem",
        "Realizando exames de imagem", "Na fila para instrumentos/medicamentos",
        "Sendo aplicados instrumentos/medicamentos", "Alta hospitalar"
    };
    return estados[estado - 1];
}

const Tempo& Paciente::getAdmissaoHZ() const {
    return admissaoHZ;
}

int Paciente::getNumMH() const {
    return procedimentosPendentes[0];
}

int Paciente::getNumTL() const {
    return procedimentosPendentes[1];
}

int Paciente::getNumEI() const {
    return procedimentosPendentes[2];
}

int Paciente::getNumIM() const {
    return procedimentosPendentes[3];
}

float Paciente::getTempoTotalAtendimento() const {
    return tempoTotalAtendimento;
}

float Paciente::getTempoTotalEspera() const {
    return tempoTotalEspera;
}
