#pragma once

#include <string>
#include <sstream>
#include "Tempo.hpp"

/**
 * @brief Classe que representa um paciente na simulação de atendimento hospitalar.
 */
class Paciente {
private:
    int id; // Identificador do paciente
    bool altaImediata; // Indica se o paciente tem alta imediata
    Tempo admissaoHZ; // Tempo de admissão no hospital
    int grauUrgencia; // Grau de urgência do paciente
    int estado; // Estado atual do paciente
    double tempoUltimoEvento; // Tempo do último evento
    float tempoTotalAtendimento; // Tempo total de atendimento
    float tempoTotalEspera; // Tempo total de espera

    int procedimentosTotais[6]; // Procedimentos totais
    int procedimentosPendentes[6]; // Procedimentos pendentes

    float temposEspera[6]; // Tempos de espera
    float temposAtendimento[6]; // Tempos de atendimento

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
        
        iss >> id >> alta >> ano >> mes >> dia >> hora >> urgencia >> mh >> tl >> ei >> im;

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
        for (int i = 0; i < 6; i++){
            temposEspera[i] = 0.0;
            temposAtendimento[i] = 0.0;
            if (i > 1 && altaImediata){
                procedimentosPendentes[i] = 0;  // Receberá alta imediata
            }
            else{
                procedimentosPendentes[i] = procedimentosTotais[i];
            }
        }


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
    void atualizarEstado(int novoEstado, double dataHoraAtual) {
        if (novoEstado ==  1){
            throw std::invalid_argument("Erro: paciente não pode voltar para o estado 1");
        }
    
        float tempoDecorrido = dataHoraAtual - tempoUltimoEvento;

        int i;
        // Evento é impar: Paciente será atendido
        if( novoEstado % 2 == 1){
            i = (novoEstado - 3)/2;
            procedimentosPendentes[i]--;
            // Registrar tempo de espera da última fila
            temposEspera[i] += tempoDecorrido; 
        }
        // Evento é par: Paciente entrará em fila
        else if(novoEstado % 2 == 1){
            i = (novoEstado - 4)/2;
            procedimentosPendentes[i]--;
            // Registrar tempo de atendimento do último atendimento
            temposAtendimento[i] += tempoDecorrido;    
        }     
        
        estado = novoEstado;
        tempoUltimoEvento = dataHoraAtual;
    }

    /**
     * @brief Obtém a próxima fila de procedimento que o paciente deve entrar.
     * 
     * @return int O índice da próxima fila de procedimento.
     */
    int proximaFilaProcedimento() {
        for(int i = 0; i < 6; i++){
            if(procedimentosPendentes[i] > 0){
                return (i+1)*2; // Retorna qual a próxima fila
            }
        }
    }

    /**
     * @brief Obtém o próximo procedimento eficiente para o paciente.
     * 
     * @return int O índice do próximo procedimento eficiente.
     */
    int proximoProcedimentoEficiente(){
        // Confere o tamanho da fila * tempo medio atendimento de cada próximo atendimento
        // proximo procedimento = min(fila * tempo medio atendimento)
        return -1;
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
        for(int i = 0; i < 6; i++){
            if(procedimentosPendentes[i] > 0){
                return true; // Retorna qual a próxima fila
            }
        }
        return false;
    }

};
