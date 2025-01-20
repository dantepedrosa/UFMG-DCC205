#pragma once

#include <string>
#include "../include/Tempo.hpp"

struct Unidade {
    bool ocupada;
    float tempoOcioso;
    Tempo ocupadoAte; // Quando a unidade estará disponível novamente

    Unidade() : ocupada(false), tempoOcioso(0.0), ocupadoAte() {}
};

class Procedimento {
private:
    std::string nome;
    int numUnidades;
    float tempoAtendimentoMedio;
    Unidade* unidades;

public:
    Procedimento(const std::string& nome, int numUnidades, float tempoAtendimentoMedio);
    ~Procedimento(); 

    // Gerenciamento de unidades
    bool unidadeDisponivel(const Tempo& dataHora) const;
    int alocarUnidade(const Tempo& dataHoraInicio, float duracao); // Retorna índice da unidade alocada
    void liberarUnidade(int indice, const Tempo& dataHoraFim);

    float calcularTempoOciosoTotal() const;

    std::string getNome() const;
    int getNumUnidades() const;
    float getTempoAtendimentoMedio() const;
};
