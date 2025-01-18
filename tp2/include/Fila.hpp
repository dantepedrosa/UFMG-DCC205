/*
O TAD fila tem por objetivo controlar os pacientes aguardando para cada procedimento
e, se for o caso, em cada prioridade. Idealmente você deve implementar um único TAD
que será instanciado múltiplas vezes, um para cada fila a ser simulada.
As operações a serem suportadas pelo TAD são as tradicionais:
1. Inicializa
2. Enfileira
3. Desenfileira
4. FilaVazia
5. Finaliza
Em termos de estatísticas, é importante registrar o tempo que um dado paciente ficou na
fila e o tamanho da fila em cada intervalo de tempo, com vistas a calcular a contenção
pelo procedimento. As estatísticas devem ser geradas quando da finalização da fila
 */

#pragma once

#ifndef FILA_HPP
#define FILA_HPP

template <typename TipoItem>
class TipoCelula
{
public:
    TipoCelula();

private:
    TipoItem item;
    TipoCelula *prox;

    template <typename T>
    friend class FilaEncadeada;
};

template <typename TipoItem>
class FilaEncadeada
{
public:
    FilaEncadeada();
    virtual ~FilaEncadeada();

    void inicializa();
    void enfileira(TipoItem item);
    TipoItem desenfileira();
    bool filaVazia() const;
    void finaliza();

private:
    TipoCelula<TipoItem> *frente;
    TipoCelula<TipoItem> *tras;
};

#endif // FILA_HPP
