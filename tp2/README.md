# TP 2 - Trabalho Prático 2 - Sistema de Escalonamento Hospitalar

## Resumo Enunciado

O sistema acompanha o paciente desde sua admissão ao Hospital Zambi até o recebimento de sua alta hospitalar. O processo é dividido em 3 etapas:

1. **Triagem:** Determina o grau de urgência do paciente, podendo ser:
    - Verde: Paciente não corre risco de vida
    - Amarelo: Paciente tem uma condição grave
    - Vermelho: Paciente tem que ser atendido imediatamente, pois corre risco de vida iminente.
2. Atendimento 
3. Internação
4. Alta

Serão no total 6 filas de atendimento, sendo estas realizadas como fila de prioridade. Para cada prioridade pode haver também uma fila:

**Filas obrigatórias:**

- Fila de Triagem
- Fila de Atendimento

**Filas de ações:**

- Fila de Medidas Hospitalares 
- Fila de Testes de Laboratório
- Fila de Exames de Imagem
- Fila de Instrumentos/Medicamentos

Para as filas de ações médicas, o paciente pode pegar várias até que receba alta. 


### Escalonador

O escalonamento deve seguir os seguintes passos:

1. registra o tempo que a unidade a ser utilizada ficou ociosa;
2. registra o tempo que o paciente ficou esperando na fila;
3. calcula a duração do serviço a ser executado;
4. define o tempo do evento, que é o tempo atual somado ao tempo do serviço a ser
executado, ou seja, o tempo de término do serviço; e
5. insere o evento no escalonador.

## Tipos Abstratos de Dados

Para o projeto, deverão ser implementados 4 tipos abstratos de dados:
- Paciente
- Procedimento
- Fila
- Escalonador

## Entrega e VPL

Seu código deve ser executado utilizando a seguinte linha de comando:

bin/tp2.out arquivo.csv

Note que o nome do arquivo não será necessariamente "arquivo.csv"(seu codigo vai receber o arquivo como argumento). Certifique-se de que o código funcione independentemente do nome fornecido.

O conteúdo do arquivo CSV não será necessariamente o mesmo do exemplo no enunciado, mas seguirá o mesmo formato. Certifique-se de que seu código seja capaz de processar arquivos nesse formato corretamente.

Atente-se ao formato da saída, que deve seguir o exemplo dado na documentação do trabalho. A saída deve ser exibida no terminal.