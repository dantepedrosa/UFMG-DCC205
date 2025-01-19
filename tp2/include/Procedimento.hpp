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

#include <string>
#include "Paciente.hpp"
#include "DataHoraTm.hpp"

struct Unidade {
    bool ocupada;
    float tempoOcioso;
    DataHoraTm ocupadoAte; // Quando a unidade estará disponível novamente
};

class Procedimento {
private:
    std::string nome;
    int numUnidades;
    float tempoAtendimentoMedio;
    Unidade* unidades;

public:
    Procedimento(const std::string& nome, int numUnidades, float tempoAtendimentoMedio);

    // Gerenciar unidades
    bool unidadeDisponivel(const DataHoraTm& dataHora) const;
    int alocarUnidade(const DataHoraTm& dataHoraInicio, float duracao); // Retorna índice da unidade alocada
    void liberarUnidade(int indice, const DataHoraTm& dataHoraFim);

    // Estatísticas
    float calcularTempoOciosoTotal() const;

    // Getters
    std::string getNome() const;
    int getNumUnidades() const;
};
