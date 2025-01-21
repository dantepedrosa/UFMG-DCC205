#pragma once

#include <string>
#include "../include/Tempo.hpp"
#include "../include/Fila.hpp"
#include "../include/Paciente.hpp" // Include the Paciente header

struct Unidade
{
    bool ocupada;
    float tempoOcioso;
    Tempo ocupadoAte; // Quando a unidade estará disponível novamente

    Unidade() : ocupada(false), tempoOcioso(0.0), ocupadoAte() {}
};

class Procedimento
{
private:
    std::string nome;
    int numUnidades;
    float tempoAtendimentoMedio;
    Unidade *unidades;
    bool comUrgencia;

    FilaEncadeada<Paciente> filaVerde;
    FilaEncadeada<Paciente> filaAmarela;
    FilaEncadeada<Paciente> filaVermelha;
    FilaEncadeada<Paciente> filaGeral;

public:
    Procedimento(const std::string &nome, int numUnidades, float tempoAtendimentoMedio, bool comUrgencia)
        : nome(nome), numUnidades(numUnidades), tempoAtendimentoMedio(tempoAtendimentoMedio), comUrgencia(comUrgencia)
    {
        unidades = new Unidade[numUnidades];
        filaVerde.inicializa();
        filaAmarela.inicializa();
        filaVermelha.inicializa();
        filaGeral.inicializa();
    }

    ~Procedimento() {
        delete[] unidades;
    }

    bool unidadeDisponivel(const Tempo &dataHora) const
    {
        for (int i = 0; i < numUnidades; ++i)
        {
            if (!unidades[i].ocupada || unidades[i].ocupadoAte.getHorasDesdeReferencia() <= dataHora.getHorasDesdeReferencia())
            {
                return true;
            }
        }
        return false;
    }

    int alocarUnidade(const Tempo &dataHoraInicio, float duracao)
    {
        for (int i = 0; i < numUnidades; ++i)
        {
            if (!unidades[i].ocupada || unidades[i].ocupadoAte.getHorasDesdeReferencia() <= dataHoraInicio.getHorasDesdeReferencia())
            {
                unidades[i].ocupada = true;
                DataHora dhFim = dataHoraInicio.getReferencia();
                dhFim.hora += duracao;
                unidades[i].ocupadoAte = Tempo(dhFim, dataHoraInicio.getReferencia());
                return i;
            }
        }
        throw std::runtime_error("Nenhuma unidade disponível");
    }

    void liberarUnidade(int indice, const Tempo &dataHoraFim)
    {
        if (indice < 0 || indice >= numUnidades)
        {
            throw std::out_of_range("Índice de unidade inválido");
        }
        unidades[indice].ocupada = false;
        unidades[indice].tempoOcioso += dataHoraFim.getHorasDesdeReferencia() - unidades[indice].ocupadoAte.getHorasDesdeReferencia();
    }

    float calcularTempoOciosoTotal() const
    {
        float tempoOciosoTotal = 0.0;
        for (int i = 0; i < numUnidades; ++i)
        {
            tempoOciosoTotal += unidades[i].tempoOcioso;
        }
        return tempoOciosoTotal;
    }

    std::string getNome() const
    {
        return nome;
    }

    int getNumUnidades() const
    {
        return numUnidades;
    }

    float getTempoAtendimentoMedio() const
    {
        return tempoAtendimentoMedio;
    }

    void enfileira(Paciente paciente, int urgencia = -1)
    {
        if (comUrgencia)
        {
            switch (urgencia)
            {
            case 0:
                filaVerde.enfileira(paciente);
                break;
            case 1:
                filaAmarela.enfileira(paciente);
                break;
            case 2:
                filaVermelha.enfileira(paciente);
                break;
            /* default:
                throw std::invalid_argument("Urgência inválida para procedimento com urgência"); */
            }
        }
        else
        {
            filaGeral.enfileira(paciente);
        }
    }

    Paciente desenfileira()
    {
        if (comUrgencia)
        {
            if (!filaVermelha.filaVazia())
            {
                return filaVermelha.desenfileira();
            }
            else if (!filaAmarela.filaVazia())
            {
                return filaAmarela.desenfileira();
            }
            else if (!filaVerde.filaVazia())
            {
                return filaVerde.desenfileira();
            }
            /* else
            {
                throw std::runtime_error("Todas as filas de urgência estão vazias.");
            } */
        }
        else
        {
            if (!filaGeral.filaVazia())
            {
                return filaGeral.desenfileira();
            }
            /* else
            {
                throw std::runtime_error("A fila geral está vazia.");
            } */
        }
    }
};
