#pragma once

#include <string>
#include "Tempo.hpp"

class Paciente {
private:
    int id;
    bool altaImediata;
    Tempo admissaoHZ;
    int grauUrgencia;
    int numMH;
    int numTL;
    int numEI;
    int numIM;
    int estado;
    Tempo tempoUltimoEvento;
    float tempoTotalAtendimento;
    float tempoTotalEspera;
    int procedimentosPendentes[4];
    float temposEspera[14];
    float temposAtendimento[14];

public:
    Paciente()
        : id(0), altaImediata(false), admissaoHZ(), grauUrgencia(0),
          numMH(0), numTL(0), numEI(0), numIM(0), estado(1), tempoUltimoEvento(),
          tempoTotalAtendimento(0.0), tempoTotalEspera(0.0),
          procedimentosPendentes{0, 0, 0, 0}, temposEspera{0.0}, temposAtendimento{0.0} {}

    Paciente(int id, bool alta, const Tempo& admissao, int urgencia, int mh, int tl, int ei, int im)
        : id(id), altaImediata(alta), admissaoHZ(admissao), grauUrgencia(urgencia),
          numMH(mh), numTL(tl), numEI(ei), numIM(im), estado(2), tempoUltimoEvento(admissao),
          tempoTotalAtendimento(0.0), tempoTotalEspera(0.0),
          procedimentosPendentes{mh, tl, ei, im}, temposEspera{0.0}, temposAtendimento{0.0} {}

    ~Paciente() = default;

    void atualizarEstado(int novoEstado, const Tempo& dataHoraAtual) {
        float tempoDecorrido = dataHoraAtual.getHorasDesdeReferencia() - tempoUltimoEvento.getHorasDesdeReferencia();
        if (estado % 2 == 0) { // Se o estado é par, é tempo de espera
            registrarEspera(tempoDecorrido);
        } else { // Se o estado é ímpar, é tempo de atendimento
            registrarAtendimento(tempoDecorrido);
        }
        estado = novoEstado;
        tempoUltimoEvento = dataHoraAtual;
    }

    void registrarEspera(float tempo) {
        temposEspera[estado - 1] += tempo; // Corrigir índice do estado
        tempoTotalEspera += tempo;
    }

    void registrarAtendimento(float tempo) {
        temposAtendimento[estado - 1] += tempo; // Corrigir índice do estado
        tempoTotalAtendimento += tempo;
    }

    int getEstado() const {
        return estado;
    }

    int getId() const {
        return id;
    }

    std::string estadoParaString() const {
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

    const Tempo& getAdmissaoHZ() const {
        return admissaoHZ;
    }

    int getNumMH() const {
        return procedimentosPendentes[0];
    }

    int getNumTL() const {
        return procedimentosPendentes[1];
    }

    int getNumEI() const {
        return procedimentosPendentes[2];
    }

    int getNumIM() const {
        return procedimentosPendentes[3];
    }

    float getTempoTotalAtendimento() const {
        return tempoTotalAtendimento;
    }

    float getTempoTotalEspera() const {
        return tempoTotalEspera;
    }
};
