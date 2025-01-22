#pragma once

#include <string>
#include <sstream>
#include "Tempo.hpp"

class Paciente {
private:
    int id; // Identificador do paciente
    bool altaImediata; // Indica se o paciente tem alta imediata
    Tempo admissaoHZ; // Tempo de admissão no hospital
    int grauUrgencia; // Grau de urgência do paciente
    int numMH; // Número de medidas hospitalares
    int numTL; // Número de testes de laboratório
    int numEI; // Número de exames de imagem
    int numIM; // Número de instrumentos/medicamentos
    int estado; // Estado atual do paciente
    Tempo tempoUltimoEvento; // Tempo do último evento
    float tempoTotalAtendimento; // Tempo total de atendimento
    float tempoTotalEspera; // Tempo total de espera
    int procedimentosPendentes[4]; // Procedimentos pendentes
    float temposEspera[14]; // Tempos de espera
    float temposAtendimento[14]; // Tempos de atendimento

public:
    /**
     * @brief Construtor padrão da classe Paciente.
     */
    Paciente()
        : id(0), altaImediata(false), admissaoHZ(), grauUrgencia(0),
          numMH(0), numTL(0), numEI(0), numIM(0), estado(1), tempoUltimoEvento(),
          tempoTotalAtendimento(0.0), tempoTotalEspera(0.0),
          procedimentosPendentes{0, 0, 0, 0}, temposEspera{0.0}, temposAtendimento{0.0} {}

    /**
     * @brief Construtor parametrizado da classe Paciente.
     * 
     * @param id Identificador do paciente.
     * @param alta Indica se o paciente tem alta imediata.
     * @param admissao Tempo de admissão no hospital.
     * @param urgencia Grau de urgência do paciente.
     * @param mh Número de medidas hospitalares.
     * @param tl Número de testes de laboratório.
     * @param ei Número de exames de imagem.
     * @param im Número de instrumentos/medicamentos.
     */
    Paciente(int id, bool alta, const Tempo& admissao, int urgencia, int mh, int tl, int ei, int im)
        : id(id), altaImediata(alta), admissaoHZ(admissao), grauUrgencia(urgencia),
          numMH(mh), numTL(tl), numEI(ei), numIM(im), estado(2), tempoUltimoEvento(admissao),
          tempoTotalAtendimento(0.0), tempoTotalEspera(0.0),
          procedimentosPendentes{mh, tl, ei, im}, temposEspera{0.0}, temposAtendimento{0.0} {}

    /**
     * @brief Construtor simplificado da classe Paciente.
     * 
     * @param linha String contendo os dados do paciente.
     * @param referencia Data de referência.
     */
    Paciente(const std::string& linha, const DataHora& referencia) {
        std::istringstream iss(linha);
        int alta, ano, mes, dia, hora, urgencia, mh, tl, ei, im;
        
        iss >> id >> alta >> ano >> mes >> dia >> hora >> urgencia >> mh >> tl >> ei >> im;

        DataHora admissao(dia, mes, ano, hora);
        admissaoHZ = Tempo(admissao, referencia);
        altaImediata = (alta == 1);
        grauUrgencia = urgencia;
        numMH = mh;
        numTL = tl;
        numEI = ei;
        numIM = im;
        estado = 2;
        tempoUltimoEvento = admissaoHZ;
        tempoTotalAtendimento = 0.0;
        tempoTotalEspera = 0.0;
        procedimentosPendentes[0] = mh;
        procedimentosPendentes[1] = tl;
        procedimentosPendentes[2] = ei;
        procedimentosPendentes[3] = im;
        std::fill(std::begin(temposEspera), std::end(temposEspera), 0.0);
        std::fill(std::begin(temposAtendimento), std::end(temposAtendimento), 0.0);
    }

    /**
     * @brief Destrutor da classe Paciente.
     */
    ~Paciente() = default;

    /**
     * @brief Atualiza o estado do paciente.
     * 
     * @param novoEstado Novo estado do paciente.
     * @param dataHoraAtual Tempo atual.
     */
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

    /**
     * @brief Registra o tempo de espera.
     * 
     * @param tempo Tempo de espera.
     */
    void registrarEspera(float tempo) {
        temposEspera[estado - 1] += tempo; // Corrigir índice do estado
        tempoTotalEspera += tempo;
    }

    /**
     * @brief Registra o tempo de atendimento.
     * 
     * @param tempo Tempo de atendimento.
     */
    void registrarAtendimento(float tempo) {
        temposAtendimento[estado - 1] += tempo; // Corrigir índice do estado
        tempoTotalAtendimento += tempo;
    }

    /**
     * @brief Converte o estado do paciente para string.
     * 
     * @return std::string Estado do paciente em formato string.
     */
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

    /**
     * @brief Obtém o tempo de admissão no hospital.
     * 
     * @return const Tempo& Tempo de admissão no hospital.
     */
    const Tempo& getAdmissaoHZ() const {
        return admissaoHZ;
    }

    /**
     * @brief Obtém o número de medidas hospitalares.
     * 
     * @return int Número de medidas hospitalares.
     */
    int getNumMH() const {
        return procedimentosPendentes[0];
    }

    /**
     * @brief Obtém o número de testes de laboratório.
     * 
     * @return int Número de testes de laboratório.
     */
    int getNumTL() const {
        return procedimentosPendentes[1];
    }

    /**
     * @brief Obtém o número de exames de imagem.
     * 
     * @return int Número de exames de imagem.
     */
    int getNumEI() const {
        return procedimentosPendentes[2];
    }

    /**
     * @brief Obtém o número de instrumentos/medicamentos.
     * 
     * @return int Número de instrumentos/medicamentos.
     */
    int getNumIM() const {
        return procedimentosPendentes[3];
    }

    /**
     * @brief Obtém o tempo total de atendimento.
     * 
     * @return float Tempo total de atendimento.
     */
    float getTempoTotalAtendimento() const {
        return tempoTotalAtendimento;
    }

    /**
     * @brief Obtém o tempo total de espera.
     * 
     * @return float Tempo total de espera.
     */
    float getTempoTotalEspera() const {
        return tempoTotalEspera;
    }

    /**
     * @brief Obtém o estado atual do paciente.
     * 
     * @return int Estado atual do paciente.
     */
    int getEstado() const {
        return estado;
    }

    /**
     * @brief Obtém o identificador do paciente.
     * 
     * @return int Identificador do paciente.
     */
    int getId() const {
        return id;
    }

    /**
     * @brief Obtém o grau de urgência do paciente.
     * 
     * @return int Grau de urgência do paciente.
     */
    int getUrgencia() const {
        return grauUrgencia;
    }

    /**
     * @brief Verifica se o paciente ainda precisa de serviços.
     * 
     * @return true Se o paciente ainda precisa de serviços.
     * @return false Caso contrário.
     */
    bool precisaDeServicos() const {
        return numMH > 0 || numTL > 0 || numEI > 0 || numIM > 0;
    }
};
