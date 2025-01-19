/*
O escalonador é um elemento central da simulação de eventos discretos. Ele é implemen-
tado como uma fila de prioridade que recupera o próximo evento (ou seja o evento de
menor data-hora que está na fila). Sugere-se implementar a fila de prioridade utilizando
um minheap.
As operações a serem implementadas incluem:
1. Inicializa
2. InsereEvento
3. RetiraProximoEvento
4. Finaliza
Para fins de escalonamento, você pode converter as várias data-hora para o número de
horas, incluindo frações, a partir de uma data de referência. As estatísticas devem ser
geradas quando finalizar.
 */


#pragma once


#include "DataHoraTm.hpp"
#include "Paciente.hpp"
#include <iostream>

/**
 * @brief Representa um evento na simulação de atendimento hospitalar.
 */
class Evento {
public:
    DataHoraTm dataHora;  // Data e hora do evento
    Paciente* paciente;   // Ponteiro para o paciente associado ao evento
    int tipoEvento;       // Tipo do evento (1: chegada, 2: triagem, etc.)

    /**
     * @brief Construtor padrão.
     */
    Evento();

    /**
     * @brief Construtor parametrizado.
     *
     * @param dataHora Data e hora do evento.
     * @param paciente Paciente associado ao evento.
     * @param tipoEvento Tipo do evento.
     */
    Evento(const DataHoraTm& dataHora, Paciente* paciente, int tipoEvento);

    /**
     * @brief Operador de comparação para o escalonador.
     * 
     * Eventos são ordenados pelo tempo, do menor para o maior.
     * 
     * @param outro O outro evento a ser comparado.
     * @return true Se este evento ocorre antes do outro.
     * @return false Caso contrário.
     */
    bool operator<(const Evento& outro) const;

    /**
     * @brief Destrutor padrão.
     */
    ~Evento();
};


class Escalonador {
private:
    Evento* heap;       // Array estático para armazenar os eventos
    int capacidade;     // Número máximo de eventos permitidos
    int tamanho;        // Número atual de eventos no heap
    float relogio;      // Tempo atual da simulação

    /**
     * @brief Restaura a propriedade do heap movendo um nó para baixo.
     *
     * @param indice O índice inicial a ser ajustado.
     */
    void heapifyDown(int indice);

    /**
     * @brief Restaura a propriedade do heap movendo um nó para cima.
     *
     * @param indice O índice inicial a ser ajustado.
     */
    void heapifyUp(int indice);

public:
    /**
     * @brief Construtor do escalonador.
     *
     * @param capacidadeMax O número máximo de eventos no heap.
     */
    Escalonador(int capacidadeMax);

    /**
     * @brief Destrutor do escalonador.
     */
    ~Escalonador();

    /**
     * @brief Inicializa o escalonador com um tempo inicial.
     *
     * @param tempoInicial Tempo inicial da simulação (em horas).
     */
    void inicializa(float tempoInicial);

    /**
     * @brief Insere um evento no heap.
     *
     * @param evento O evento a ser inserido.
     * @throws std::overflow_error Se o heap estiver cheio.
     */
    void insereEvento(const Evento& evento);

    /**
     * @brief Remove e retorna o próximo evento (com menor tempo) do heap.
     *
     * @return Evento O próximo evento no heap.
     * @throws std::underflow_error Se o heap estiver vazio.
     */
    Evento retiraProximoEvento();

    /**
     * @brief Verifica se ainda há eventos no escalonador.
     *
     * @return true Se há eventos no heap.
     * @return false Se o heap está vazio.
     */
    bool temEventos() const;

    /**
     * @brief Avança o relógio da simulação para o próximo evento.
     *
     * @return float O tempo do próximo evento.
     */
    float avancaRelogio();

    /**
     * @brief Finaliza o escalonador e limpa recursos.
     */
    void finaliza();

    /**
     * @brief Obtém o tempo atual da simulação.
     *
     * @return float O tempo atual em horas.
     */
    float getRelogio() const;
};