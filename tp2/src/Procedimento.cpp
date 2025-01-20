/*
Procedimentos são todos os serviços à disposição de um paciente. Para cada serviço é
definido um tempo médio de execução e o número de unidades que executam o serviço.
Por exemplo, se é definido que <numerotriagem> é 5, isso significa que há 5 atendentes
para a triagem, o que permite atender até 5 pacientes simultaneamente. Para fins da
simulação, um serviço, na prática cada uma das suas unidades, pode estar ocupado ou
ocioso.
O TAD procedimento deve registrar a utilização de cada unidade de cada procedimento
e/ou seu tempo ocioso. Também é importante manter a data hora até a qual cada unidade
está ocupada.


*/

#include "../include/Procedimento.hpp"
#include "../include/Tempo.hpp"

Procedimento::Procedimento(const std::string& nome, int numUnidades, float tempoAtendimentoMedio)
    : nome(nome), numUnidades(numUnidades), tempoAtendimentoMedio(tempoAtendimentoMedio) {
    unidades = new Unidade[numUnidades];
}

Procedimento::~Procedimento() {
    delete[] unidades;
}

bool Procedimento::unidadeDisponivel(const Tempo& dataHora) const {
    for (int i = 0; i < numUnidades; ++i) {
        if (!unidades[i].ocupada || unidades[i].ocupadoAte.getHorasDesdeReferencia() <= dataHora.getHorasDesdeReferencia()) {
            return true;
        }
    }
    return false;
}

int Procedimento::alocarUnidade(const Tempo& dataHoraInicio, float duracao) {
    for (int i = 0; i < numUnidades; ++i) {
        if (!unidades[i].ocupada || unidades[i].ocupadoAte.getHorasDesdeReferencia() <= dataHoraInicio.getHorasDesdeReferencia()) {
            unidades[i].ocupada = true;
            DataHora dhFim = dataHoraInicio.getReferencia();
            dhFim.hora += duracao;
            unidades[i].ocupadoAte = Tempo(dhFim, dataHoraInicio.getReferencia());
            return i;
        }
    }
    throw std::runtime_error("Nenhuma unidade disponível");
}

void Procedimento::liberarUnidade(int indice, const Tempo& dataHoraFim) {
    if (indice < 0 || indice >= numUnidades) {
        throw std::out_of_range("Índice de unidade inválido");
    }
    unidades[indice].ocupada = false;
    unidades[indice].tempoOcioso += dataHoraFim.getHorasDesdeReferencia() - unidades[indice].ocupadoAte.getHorasDesdeReferencia();
}

float Procedimento::calcularTempoOciosoTotal() const {
    float tempoOciosoTotal = 0.0;
    for (int i = 0; i < numUnidades; ++i) {
        tempoOciosoTotal += unidades[i].tempoOcioso;
    }
    return tempoOciosoTotal;
}

std::string Procedimento::getNome() const {
    return nome;
}

int Procedimento::getNumUnidades() const {
    return numUnidades;
}

