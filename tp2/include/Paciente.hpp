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
“Não chegou ainda ao hospital´´ é o estado inicial de todos os pacientes e ele se encerra na
data-hora de admissão atribuída a cada paciente no arquivo de entrada. Um outro caso
a ser tratado é de quando o paciente tem alta logo após o atendimento, indo de “Sendo
atendido´´ para "Alta hospitalar´´.
O TAD paciente, além de manter o prontuário do paciente (quais e quantos procedimentos
deve realizar), deve armazenar o estado atual, e as estatísticas de atendimento do paci-
ente, em particular o tempo ocioso e o tempo sendo atendido. Essas informações serão
fundamentais para o cálculo das estatísticas gerais do sistema
*/



#include <string>


class Paciente
{
private:
    
public:
    Paciente(/* args */);
    ~Paciente();
};
