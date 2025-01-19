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


#include "../include/Escalonador.hpp"
#include "../include/DataHoraTm.hpp"
#include <stdexcept>
#include <iostream>



Evento::Evento(const DataHoraTm& dataHora, Paciente* paciente, int tipoEvento)
    : dataHora(dataHora), paciente(paciente), tipoEvento(tipoEvento) {}

// Operador de comparação
bool Evento::operator<(const Evento& outro) const {
    return dataHora < outro.dataHora; // Ordem crescente de tempo
}


#include "Escalonador.hpp"
#include <iostream>

// Construtor
Escalonador::Escalonador(int capacidadeMax) : capacidade(capacidadeMax), tamanho(0), relogio(0.0) {
    heap = new Evento[capacidade]; // Aloca o array estático
}

// Destrutor
Escalonador::~Escalonador() {
    delete[] heap;
}

// Inicializa o escalonador
void Escalonador::inicializa(float tempoInicial) {
    relogio = tempoInicial;
    tamanho = 0; // Heap vazio no início
}

// Insere um evento no heap
void Escalonador::insereEvento(const Evento& evento) {
    if (tamanho >= capacidade) {
        throw std::overflow_error("Escalonador cheio: não é possível adicionar mais eventos.");
    }
    heap[tamanho] = evento; // Adiciona o evento no final
    heapifyUp(tamanho);     // Ajusta o heap para manter a propriedade
    tamanho++;
}

// Retira o próximo evento do heap
Evento Escalonador::retiraProximoEvento() {
    if (tamanho == 0) {
        throw std::underflow_error("Escalonador vazio: não há eventos para retirar.");
    }
    Evento proximo = heap[0];   // O menor elemento está na raiz
    heap[0] = heap[tamanho - 1]; // Substitui pela última posição
    tamanho--;                  // Reduz o tamanho do heap
    heapifyDown(0);             // Ajusta o heap para restaurar a propriedade
    return proximo;
}

// Verifica se ainda há eventos
bool Escalonador::temEventos() const {
    return tamanho > 0;
}

// Avança o relógio para o próximo evento
float Escalonador::avancaRelogio() {
    if (tamanho == 0) {
        throw std::runtime_error("Não há eventos para avançar o relógio.");
    }
    //relogio = heap[0].dataHora.toFloat(); // Atualiza o relógio para o tempo do próximo evento
    return relogio;
}

// Finaliza o escalonador
void Escalonador::finaliza() {
    delete[] heap;
    heap = nullptr;
    tamanho = 0;
    capacidade = 0;
    relogio = 0.0;
}

// Ajusta o heap de baixo para cima
void Escalonador::heapifyUp(int indice) {
    while (indice > 0) {
        int pai = (indice - 1) / 2;
        if (heap[indice] < heap[pai]) {
            std::swap(heap[indice], heap[pai]);
            indice = pai;
        } else {
            break;
        }
    }
}

// Ajusta o heap de cima para baixo
void Escalonador::heapifyDown(int indice) {
    int menor = indice;
    int esq = 2 * indice + 1;
    int dir = 2 * indice + 2;

    if (esq < tamanho && heap[esq] < heap[menor]) {
        menor = esq;
    }
    if (dir < tamanho && heap[dir] < heap[menor]) {
        menor = dir;
    }

    if (menor != indice) {
        std::swap(heap[indice], heap[menor]);
        heapifyDown(menor); // Continua ajustando recursivamente
    }
}

// Obtém o tempo atual
float Escalonador::getRelogio() const {
    return relogio;
}
 */