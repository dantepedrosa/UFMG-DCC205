#pragma once

#include <string>
#include "Paciente.hpp"
#include "Tempo.hpp"
#include "Fila.hpp"


#define MAXTAM 15

class Procedimento
{
private:
    std::string nome;               // Nome do procedimento
    int numUnidades;                // Número de unidades total
    int numDisponiveis;             // Número de unidades disponíveis
    float tempoAtendimentoMedio;    // Tempo médio de atendimento
    bool comUrgencia;               // Indica se o procedimento tem urgência

    FilaEncadeada<Paciente>* filaVerde;     // Fila de pacientes com urgência verde
    FilaEncadeada<Paciente>* filaAmarela;   // Fila de pacientes com urgência amarela
    FilaEncadeada<Paciente>* filaVermelha;  // Fila de pacientes com urgência vermelha
    FilaEncadeada<Paciente>* filaGeral;     // Fila geral de pacientes

public:
    /**
     * @brief Construtor da classe Procedimento.
     * 
     * @param nome Nome do procedimento.
     * @param numUnidades Número de unidades disponíveis.
     * @param tempoAtendimentoMedio Tempo médio de atendimento.
     * @param comUrgencia Indica se o procedimento tem urgência.
     */
    Procedimento(const std::string &nome, int numUnidades, float tempoAtendimentoMedio, bool comUrgencia)
        : nome(nome), numUnidades(numUnidades), numDisponiveis(numUnidades), tempoAtendimentoMedio(tempoAtendimentoMedio), comUrgencia(comUrgencia)
    {
        filaVerde = new FilaEncadeada<Paciente>();
        filaAmarela = new FilaEncadeada<Paciente>();
        filaVermelha = new FilaEncadeada<Paciente>();
        filaGeral = new FilaEncadeada<Paciente>();
    }

    /**
     * @brief Destrutor da classe Procedimento.
     */
    ~Procedimento()
    {

        if (filaVerde)
        {
            filaVerde->finaliza(); // Limpa os elementos da fila
            delete filaVerde;      // Deleta a própria fila
            filaVerde = nullptr;   // Previne dangling pointers
        }

        if (filaAmarela)
        {
            filaAmarela->finaliza(); // Limpa os elementos da fila
            delete filaAmarela;      // Deleta a própria fila
            filaAmarela = nullptr;   // Previne dangling pointers
        }

        if (filaVermelha)
        {
            filaVermelha->finaliza(); // Limpa os elementos da fila
            delete filaVermelha;      // Deleta a própria fila
            filaVermelha = nullptr;   // Previne dangling pointers
        }

        if (filaGeral)
        {
            filaGeral->finaliza(); // Limpa os elementos da fila
            delete filaGeral;      // Deleta a própria fila
            filaGeral = nullptr;   // Previne dangling pointers
        }
    }

    /**
     * @brief Verifica se há unidades disponíveis no tempo especificado.
     * 
     * @param dataHora Tempo a ser verificado.
     * @return true Se há unidades disponíveis.
     * @return false Caso contrário.
     */
    bool unidadeDisponivel(const Tempo &dataHora) const
    {
        return numDisponiveis > 0;
    }

    /**
     * @brief Aloca uma unidade para atendimento.
     * 
     * @param dataHoraInicio Tempo de início do atendimento.
     * @param duracao Duração do atendimento.
     * @return int Índice da unidade alocada.
     * @throws std::runtime_error Se não houver unidades disponíveis.
     */
    int alocarUnidade(const Tempo &dataHoraInicio, float duracao)
    {
        if (numDisponiveis > 0)
        {
            numDisponiveis--;
            return numUnidades - numDisponiveis - 1;
        }
        throw std::runtime_error("Nenhuma unidade disponível");
    }

    /**
     * @brief Libera uma unidade após o atendimento.
     * 
     * @param indice Índice da unidade a ser liberada.
     * @param dataHoraFim Tempo de término do atendimento.
     * @throws std::out_of_range Se o índice da unidade for inválido.
     */
    void liberarUnidade(int indice, const Tempo &dataHoraFim)
    {
        if (indice < 0 || indice >= numUnidades)
        {
            throw std::out_of_range("Índice de unidade inválido");
        }
        numDisponiveis++;
    }

    /**
     * @brief Calcula o tempo ocioso total das unidades.
     * 
     * @return float Tempo ocioso total.
     */
    float calcularTempoOciosoTotal() const
    {
        return (numUnidades - numDisponiveis) * tempoAtendimentoMedio;
    }

    /**
     * @brief Obtém o nome do procedimento.
     * 
     * @return std::string Nome do procedimento.
     */
    std::string getNome() const
    {
        return nome;
    }

    /**
     * @brief Obtém o número de unidades disponíveis.
     * 
     * @return int Número de unidades disponíveis.
     */
    int getNumUnidades() const
    {
        return numUnidades;
    }

    /**
     * @brief Obtém o tempo médio de atendimento.
     * 
     * @return float Tempo médio de atendimento.
     */
    float getTempoAtendimentoMedio() const
    {
        return tempoAtendimentoMedio;
    }

    /**
     * @brief Enfileira um paciente na fila adequada.
     * 
     * @param paciente Paciente a ser enfileirado.
     * @param urgencia Grau de urgência do paciente.
     * @throws std::invalid_argument Se a urgência for inválida para procedimento com urgência.
     */
    void enfileira(Paciente paciente, int urgencia = -1)
    {
        if (comUrgencia)
        {
            switch (urgencia)
            {
            case 0:
                filaVerde->enfileira(paciente);
                break;
            case 1:
                filaAmarela->enfileira(paciente);
                break;
            case 2:
                filaVermelha->enfileira(paciente);
                break;
            default:
                throw std::invalid_argument("Urgência inválida para procedimento com urgência");
            }
        }
        else
        {
            filaGeral->enfileira(paciente);
        }
    }

    /**
     * @brief Desenfileira um paciente da fila adequada.
     * 
     * @return Paciente Paciente desenfileirado.
     * @throws std::runtime_error Se todas as filas de urgência estiverem vazias ou se a fila geral estiver vazia.
     */
    Paciente desenfileira()
    {
        if (comUrgencia)
        {
            if (!filaVermelha->filaVazia())
            {
                return filaVermelha->desenfileira();
            }
            else if (!filaAmarela->filaVazia())
            {
                return filaAmarela->desenfileira();
            }
            else if (!filaVerde->filaVazia())
            {
                return filaVerde->desenfileira();
            }
            else
            {
                throw std::runtime_error("Todas as filas de urgência estão vazias.");
            }
        }
        else
        {
            if (!filaGeral->filaVazia())
            {
                return filaGeral->desenfileira();
            }
            else
            {
                throw std::runtime_error("A fila geral está vazia.");
            }
        }
        throw std::runtime_error("Nenhum paciente para desenfileirar.");
    }
};
