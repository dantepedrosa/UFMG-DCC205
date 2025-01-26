/*
O escalonador é um elemento central da simulação de eventos discretos. Ele é
implemen- tado como uma fila de prioridade que recupera o próximo evento (ou
seja o evento de menor data-hora que está na fila). Sugere-se implementar a fila
de prioridade utilizando um minheap. As operações a serem implementadas incluem:
1. Inicializa
2. InsereEvento
3. RetiraProximoEvento
4. Finaliza
Para fins de escalonamento, você pode converter as várias data-hora para o
número de horas, incluindo frações, a partir de uma data de referência. As
estatísticas devem ser geradas quando finalizar.
 */

#pragma once

#include <iostream>
#include <stdexcept>

#include "../include/Paciente.hpp"
#include "../include/Tempo.hpp"

/**
 * @file Escalonador.hpp
 * @brief Declaração das classes Evento e Escalonador.
 */

/**
 * @brief Representa um evento na simulação de atendimento hospitalar.
 */
class Evento {
    double dataHora;     // Data e hora do evento
    Paciente* paciente;  // Ponteiro para o paciente associado ao evento
    int tipoEvento;      // Tipo do evento (1: chegada, 2: triagem, etc.)

    friend class Escalonador;  // Declara Escalonador como friend class

   public:
    Evento() : dataHora(), paciente(nullptr), tipoEvento(0) {}

    Evento(double dataHora, Paciente* paciente, int tipoEvento)
        : dataHora(dataHora), paciente(paciente), tipoEvento(tipoEvento) {}

    Paciente* getPaciente() const { return paciente; }

    int getTipoEvento() const { return tipoEvento; }

    double getTempo() const { return dataHora; }

    bool operator<(const Evento& outro) const {
        return dataHora < outro.dataHora;
    }

    bool operator==(const Evento& outro) const {
        return dataHora == outro.dataHora;
    }

    bool operator!=(const Evento& outro) const { return !(*this == outro); }

    bool operator>(const Evento& outro) const {
        return dataHora > outro.dataHora;
    }

    bool operator<=(const Evento& outro) const { return !(*this > outro); }

    bool operator>=(const Evento& outro) const { return !(*this < outro); }

    ~Evento() {}
};

/**
 * @brief Classe que representa o escalonador de eventos.
 */
class Escalonador {
   private:
    Evento* heap;    // Array dinâmico para armazenar os eventos
    int capacidade;  // Capacidade máxima do heap
    int tamanho;     // Tamanho atual do heap
    double relogio;  // Tempo atual da simulação

    void heapifyDown(int indice) {
        int menor = indice;
        int esquerda = 2 * indice + 1;
        int direita = 2 * indice + 2;

        if (esquerda < tamanho && heap[esquerda] < heap[menor]) {
            menor = esquerda;
        }

        if (direita < tamanho && heap[direita] < heap[menor]) {
            menor = direita;
        }

        if (menor != indice) {
            std::swap(heap[indice], heap[menor]);
            heapifyDown(menor);
        }
    }

    void heapifyUp(int indice) {
        int pai = (indice - 1) / 2;

        if (indice && heap[indice] < heap[pai]) {
            std::swap(heap[indice], heap[pai]);
            heapifyUp(pai);
        }
    }

    float avancaRelogio() {
        if (tamanho == 0) {
            throw std::underflow_error("Heap vazio");
        }

        relogio = heap[0].getTempo();
        return relogio;
    }

   public:
    Escalonador(int capacidadeMax, const DataHora& ref)
        : capacidade(capacidadeMax), tamanho(0) {
        heap = new Evento[capacidade];
        relogio = 0.0;
    }

    ~Escalonador() { delete[] heap; }

    void insereEvento(const Evento& evento) {
        if (tamanho == capacidade) {
            throw std::overflow_error("Heap cheio");
        }

        heap[tamanho] = evento;
        heapifyUp(tamanho);
        tamanho++;
    }

    Evento retiraProximoEvento() {
        if (tamanho == 0) {
            throw std::underflow_error("Heap vazio");
        }
        avancaRelogio();
        Evento evento = heap[0];
        heap[0] = heap[tamanho - 1];
        tamanho--;
        heapifyDown(0);

        return evento;
    }

    bool temEventos() const { return tamanho > 0; }

    void finaliza() {
        delete[] heap;
        heap = nullptr;
        tamanho = 0;
        capacidade = 0;
    }

    float getRelogio() const { return relogio; }
};
