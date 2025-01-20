/*
O paciente, cujas informações de entrada são lidas de um arquivo, representa a trajetória
de atendimento e serviços prestados pelo hospital. Além dessas informações de entrada, é
importante armazenar todos os momentos quando o paciente foi de alguma forma atendido,
assim como os intervalos de tempo que ele ficou em cada uma das filas. A partir dessas
informações é que será possível realizar as estatísticas de atendimento do hospital e avaliar
cenários de alocação de recursos e tempos para os procedimentos.
Para fins da simulação, um paciente pode estar em 14 estados:
1. Não chegou ainda ao hospital
2. Na fila de triagem
3. Sendo triado
4. Na fila de atendimento
5. Sendo atendido
6. Na fila de medidas hospitalares
7. Realizando medidas hospitalares
8. Na fila de testes de laboratório
9. Realizando testes de laboratório
10. Na fila de exames de imagem
11. Realizando exames de imagem
12. Na fila para instrumentos/medicamentos
13. Sendo aplicados instrumentos/medicamentos
14. Alta hospitalar
Note que há uma simplificação importante na simulação, o paciente assume os estados na
ordem apresentada e não há situação em que ele retorne a um estado anterior. O estado
“Não chegou ainda ao hospital” é o estado inicial de todos os pacientes e ele se encerra na
data-hora de admissão atribuída a cada paciente no arquivo de entrada. Um outro caso
a ser tratado é de quando o paciente tem alta logo após o atendimento, indo de “Sendo
atendido” para "Alta hospitalar”.
O TAD paciente, além de manter o prontuário do paciente (quais e quantos procedimentos
deve realizar), deve armazenar o estado atual, e as estatísticas de atendimento do paci-
ente, em particular o tempo ocioso e o tempo sendo atendido. Essas informações serão
fundamentais para o cálculo das estatísticas gerais do sistema.
*/

#pragma once

#include <string>
#include "Tempo.hpp"

class Paciente {
private:
    int id;
    bool altaImediata;
    Tempo admissaoHZ;
    int grauUrgencia;

    int numMH;  // Número de Medidas Hospitalares inicial
    int numTL;  // Número de Testes de Laboratório inicial
    int numEI;  // Número de Exames de Imagem inicial 
    int numIM;  // Número de Instrumentos/Medicamentos inicial

    int estado;  // Estado atual do paciente (1 a 14)

    int* procedimentosPendentes; // Número de procedimentos pendentes de cada tipo

    float* temposEspera; // Tempo de espera em cada fila
    float* temposAtendimento; // Tempo de atendimento em cada procedimento

    Tempo tempoUltimoEvento; // Data/hora do último evento processado para o paciente

    Tempo saidaHZ; // Data/hora de saída do paciente
    float tempoTotalAtendimento; // Tempo total de atendimento
    float tempoTotalEspera; // Tempo total de espera

public:
    Paciente();
    Paciente(int id, bool alta, const Tempo& admissao, int urgencia, int mh, int tl, int ei, int im);
    ~Paciente();

    // Atualiza estado do paciente
    void atualizarEstado(int novoEstado, const Tempo& dataHoraAtual);

    // Adiciona tempo de espera ou atendimento
    void registrarEspera(float tempo);
    void registrarAtendimento(float tempo);

    // Métodos de consulta
    int getEstado() const;
    std::string estadoParaString() const; // Converte o estado para string legível
    const Tempo& getAdmissaoHZ() const;

    // Getters para os procedimentos pendentes
    int getNumMH() const;
    int getNumTL() const;
    int getNumEI() const;
    int getNumIM() const;

    // Estatísticas
    float getTempoTotalAtendimento() const;
    float getTempoTotalEspera() const;
};