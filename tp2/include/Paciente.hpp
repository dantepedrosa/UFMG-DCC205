#pragma once

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#define TRIAGEM 0
#define ATENDIMENTO 1
#define MH 2
#define TL 3
#define EI 4
#define IM 5

#include "Tempo.hpp"

/**
 * @file Paciente.hpp
 * @brief Declaração da classe Paciente.
 */

/**
 * @brief Classe que representa um paciente na simulação de atendimento
 * hospitalar.
 */
class Paciente {
   private:
    std::string id;               // Identificador do paciente
    bool altaImediata;            // Indica se o paciente tem alta imediata
    Tempo admissaoHZ;             // Tempo de admissão no hospital
    Tempo saidaHZ;                // Tempo de saída do hospital
    int grauUrgencia;             // Grau de urgência do paciente
    int estado;                   // Estado atual do paciente
    double tempoUltimoEvento;     // Tempo do último evento
    float tempoTotalAtendimento;  // Tempo total de atendimento
    float tempoTotalEspera;       // Tempo total de espera

    int procedimentosTotais[6];     // Procedimentos totais
    int procedimentosPendentes[6];  // Procedimentos pendentes

    float temposEspera[6];       // Tempos de espera
    float temposAtendimento[6];  // Tempos de atendimento
    float permanenciaHZ;

    void registraSaida(double horaSaida) {
        permanenciaHZ = horaSaida - admissaoHZ.getHorasDesdeReferencia();

        /*
        if (permanenciaHZ != (tempoTotalEspera + tempoTotalAtendimento))
            throw std::invalid_argument(
                "Erro: permanência do paciente não corresponde ao tempo total "
                "de espera e atendimento");
        */
        saidaHZ = admissaoHZ;
        saidaHZ.somaHoras(permanenciaHZ);
        estado = 14;
    }

    std::string formatarNumero(float valor) {
        std::ostringstream oss;

        // Verifica se o número tem parte fracionária significativa
        if (std::abs(std::fmod(valor, 1.0)) < 0.01) {
            // Sem parte fracionária relevante (ex.: 5.0 ou 10.0)
            oss << std::fixed << std::setprecision(1);
        } else {
            // Exibe com mais casas decimais (ex.: 0.05)
            oss << std::fixed << std::setprecision(2);
        }

        oss << valor;
        return oss.str();
    }

   public:
    /**
     * @brief Construtor simplificado da classe Paciente.
     *
     * @param linha String contendo os dados do paciente.
     * @param referencia Data de referência.
     */
    Paciente(const std::string& linha, const DataHora& referencia) {
        std::istringstream iss(linha);
        int alta, ano, mes, dia, hora, urgencia, mh, tl, ei, im;

        iss >> id >> alta >> ano >> mes >> dia >> hora >> urgencia >> mh >>
            tl >> ei >> im;

        DataHora admissao(dia, mes, ano, hora);
        admissaoHZ = Tempo(admissao, referencia);
        altaImediata = (alta == 1);
        grauUrgencia = urgencia;
        estado = 1;

        procedimentosTotais[0] = 1;
        procedimentosTotais[1] = 1;
        procedimentosTotais[2] = mh;
        procedimentosTotais[3] = tl;
        procedimentosTotais[4] = ei;
        procedimentosTotais[5] = im;

        tempoUltimoEvento = admissaoHZ.getHorasDesdeReferencia();
        tempoTotalAtendimento = 0.0;
        tempoTotalEspera = 0.0;

        // Inicializa os arrays
        for (int i = 0; i < 6; i++) {
            temposEspera[i] = 0.0;
            temposAtendimento[i] = 0.0;
            if (i > 1 && altaImediata) {
                procedimentosPendentes[i] = 0;  // Receberá alta imediata
            } else {
                procedimentosPendentes[i] = procedimentosTotais[i];
            }
        }

        std::fill(std::begin(temposEspera), std::end(temposEspera), 0.0);
        std::fill(std::begin(temposAtendimento), std::end(temposAtendimento),
                  0.0);
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
    void atualizarEstado(int novoEstado, double dataHoraAtual) {
        if (novoEstado == 1) {
            throw std::invalid_argument(
                "Erro: paciente não pode voltar para o estado 1");
        }

        double tempoDecorrido = dataHoraAtual - tempoUltimoEvento; // Arredonda para 2 casas decimais


        int i;
        // Evento é impar: Paciente será atendido
        if (novoEstado % 2 == 1) {
            i = (estado - 1) / 2;
            procedimentosPendentes[i]--;
            // Registrar tempo de espera da última fila
            registrarEspera(tempoDecorrido);
        }
        // Evento é par: Paciente entrará em fila
        else if (novoEstado % 2 == 0) {
            i = (estado - 2) / 2;
            // Registrar tempo de atendimento do último atendimento
            registrarAtendimento(tempoDecorrido);
        }

        if (novoEstado == 14) {
            if (procedimentosPendentes[0] > 0 || procedimentosPendentes[1] > 0)
                throw std::invalid_argument(
                    "Erro: paciente não pode ter alta sem ter passado por "
                    "triagem e atendimento");

            if (this->precisaDeServicos()){
                if(!altaImediata)
                    throw std::invalid_argument(
                    "Erro: paciente não pode ter alta sem ter passado por "
                    "todos os procedimentos");
            }
            registraSaida(dataHoraAtual);
        }

        estado = novoEstado;
        tempoUltimoEvento = dataHoraAtual;
    }

    int proximaFilaProcedimento() {
        for (int i = 0; i < 6; i++) {
            if (procedimentosPendentes[i] > 0) {
                return (i + 1) * 2;  // Retorna qual a próxima fila
            }
        }
        return -1;
    }

    int proximoProcedimentoEficiente() {
        // Confere o tamanho da fila * tempo medio atendimento de cada próximo
        // atendimento proximo procedimento = min(fila * tempo medio
        // atendimento)
        return -1;
    }

    /**
     * @brief Registra o tempo de espera.
     *
     * @param tempo Tempo de espera.
     */
    void registrarEspera(float tempo) {
        temposEspera[(estado - 2)/2] += tempo;  // Corrigir índice do estado
        tempoTotalEspera += tempo;
    }

    /**
     * @brief Registra o tempo de atendimento.
     *
     * @param tempo Tempo de atendimento.
     */
    void registrarAtendimento(float tempo) {
        temposAtendimento[(estado - 3)/2] += tempo;
        tempoTotalAtendimento += tempo;
    }

    /**
     * @brief Imprime os dados e estatísticas do paciente.
     *
     * @details Imprime o paciente no formato, em uma linha apenas:
     *
     * <id>
     * <ddddChegada> <mChegada> <dChegada> <hChegada>:<mChegada>:00 <yChegada>
     * <ddddSaida> <mSaida> <dSaida> <hSaida>:<mSaida>:00 <ySaida>
     * <permanenciaHZ> <tempoTotalAtendimento> <tempoTotalEspera>
     *
     */
    std::string imprimeEstatisticas() {
        std::ostringstream outputStream;

        outputStream << std::fixed << std::setprecision(2);

        outputStream << id << " " << admissaoHZ.paraString() << " "
                     << saidaHZ.paraString() << " "
                     << this->formatarNumero(permanenciaHZ) << " "
                     << this->formatarNumero(tempoTotalAtendimento) << " "
                     << this->formatarNumero(tempoTotalEspera);

        std::string output = outputStream.str();

        std::cout << output << std::endl;

        return output;
    }

    /**
     * @brief Converte o estado do paciente para string.
     *
     * @return std::string Estado do paciente em formato string.
     */
    std::string estadoParaString() const {
        static const char* estados[] = {
            "Não chegou ainda ao hospital",
            "Na fila de triagem",
            "Sendo triado",
            "Na fila de atendimento",
            "Sendo atendido",
            "Na fila de medidas hospitalares",
            "Realizando medidas hospitalares",
            "Na fila de testes de laboratório",
            "Realizando testes de laboratório",
            "Na fila de exames de imagem",
            "Realizando exames de imagem",
            "Na fila para instrumentos/medicamentos",
            "Sendo aplicados instrumentos/medicamentos",
            "Alta hospitalar"};
        return estados[estado - 1];
    }

    /**
     * @brief Verifica se o paciente ainda precisa de serviços.
     *
     * @return true Se o paciente ainda precisa de serviços.
     * @return false Caso contrário.
     */
    bool precisaDeServicos() const {
        for (int i = 0; i < 6; i++) {
            if (procedimentosPendentes[i] > 0) {
                return true;  // Retorna qual a próxima fila
            }
        }
        return false;
    }

    // Getters

    /** @brief Retorna o tempo de admissão no hospital */
    const Tempo& getAdmissaoHZ() const { return admissaoHZ; }

    /** @brief Retorna o tempo total de atendimento */
    float getTempoTotalAtendimento() const { return tempoTotalAtendimento; }

    /** @brief Retorna o tempo total de espera */
    float getTempoTotalEspera() const { return tempoTotalEspera; }

    /** @brief Retorna o estado atual do paciente */
    int getEstado() const { return estado; }

    /** @brief Retorna o identificador do paciente */
    std::string getId() const { return id; }

    /** @brief Retorna se o paciente tem alta imediata */
    bool getAltaImediata() const { return altaImediata; }

    /** @brief Retorna o grau de urgência do paciente */
    int getUrgencia() const { return grauUrgencia; }

    /** @brief Retorna o número total de triagens */
    int getTriagemTotal() const { return procedimentosTotais[TRIAGEM]; }

    /** @brief Retorna o número total de atendimentos */
    int getAtendimentoTotal() const { return procedimentosTotais[ATENDIMENTO]; }

    /** @brief Retorna o número total de medidas hospitalares */
    int getMhTotal() const { return procedimentosTotais[MH]; }

    /** @brief Retorna o número total de testes de laboratório */
    int getTlTotal() const { return procedimentosTotais[TL]; }

    /** @brief Retorna o número total de exames de imagem */
    int getEiTotal() const { return procedimentosTotais[EI]; }

    /** @brief Retorna o número total de instrumentos/medicamentos */
    int getImTotal() const { return procedimentosTotais[IM]; }

    /** @brief Retorna o número de triagens pendentes */
    int getTriagemPendente() const { return procedimentosPendentes[TRIAGEM]; }

    /** @brief Retorna o número de atendimentos pendentes */
    int getAtendimentoPendente() const { return procedimentosPendentes[ATENDIMENTO]; }

    /** @brief Retorna o número de medidas hospitalares pendentes */
    int getMhPendente() const { return procedimentosPendentes[MH]; }

    /** @brief Retorna o número de testes de laboratório pendentes */
    int getTlPendente() const { return procedimentosPendentes[TL]; }

    /** @brief Retorna o número de exames de imagem pendentes */
    int getEiPendente() const { return procedimentosPendentes[EI]; }

    /** @brief Retorna o número de instrumentos/medicamentos pendentes */
    int getImPendente() const { return procedimentosPendentes[IM]; }
};
