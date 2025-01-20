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

#include "Escalonador.hpp"

Evento::Evento() : dataHora(), paciente(nullptr), tipoEvento(0) {}

Evento::Evento(const Tempo& dataHora, Paciente* paciente, int tipoEvento)
    : dataHora(dataHora), paciente(paciente), tipoEvento(tipoEvento) {}

bool Evento::operator<(const Evento& outro) const {
    return dataHora < outro.dataHora;
}

bool Evento::operator==(const Evento& outro) const {
    return dataHora == outro.dataHora;
}

bool Evento::operator!=(const Evento& outro) const {
    return !(*this == outro);
}

bool Evento::operator>(const Evento& outro) const {
    return dataHora > outro.dataHora;
}

bool Evento::operator<=(const Evento& outro) const {
    return !(*this > outro);
}

bool Evento::operator>=(const Evento& outro) const {
    return !(*this < outro);
}

Evento::~Evento() {}

Escalonador::Escalonador(int capacidadeMax) : capacidade(capacidadeMax), tamanho(0), relogio(0.0) {
    heap = new Evento[capacidade];
}

Escalonador::~Escalonador() {
    delete[] heap;
}

void Escalonador::heapifyDown(int indice) {
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

void Escalonador::heapifyUp(int indice) {
    int pai = (indice - 1) / 2;

    if (indice && heap[indice] < heap[pai]) {
        std::swap(heap[indice], heap[pai]);
        heapifyUp(pai);
    }
}

void Escalonador::inicializa(float tempoInicial) {
    relogio = tempoInicial;
}

void Escalonador::insereEvento(const Evento& evento) {
    if (tamanho == capacidade) {
        throw std::overflow_error("Heap cheio");
    }

    heap[tamanho] = evento;
    heapifyUp(tamanho);
    tamanho++;
}

Evento Escalonador::retiraProximoEvento() {
    if (tamanho == 0) {
        throw std::underflow_error("Heap vazio");
    }

    Evento evento = heap[0];
    heap[0] = heap[tamanho - 1];
    tamanho--;
    heapifyDown(0);

    return evento;
}

bool Escalonador::temEventos() const {
    return tamanho > 0;
}

float Escalonador::avancaRelogio() {
    if (tamanho == 0) {
        throw std::underflow_error("Heap vazio");
    }

    relogio = heap[0].dataHora.getHorasDesdeReferencia();
    return relogio;
}

void Escalonador::finaliza() {
    delete[] heap;
    heap = nullptr;
    tamanho = 0;
    capacidade = 0;
}

float Escalonador::getRelogio() const {
    return relogio;
}