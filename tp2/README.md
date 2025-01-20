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

## Exemplo

Considerando o paciente exemplo:

`0009600024 0 2017 3 21 6 0 7 15 5 38`

Procedimento | Tempo | Quant. | Total
---|---|---|--- 
Triagem | 12 min (0.2 horas) | 1 | 0.20
Atendimento | 30 min (0.5 horas) | 1 | 0.50
Medidas | 6 min (0.1 horas) | 7 | 0.70
Testes | 3 min (0.05 horas) | 15 | 0.75
Imagem | 30 min (0.5 horas) | 5 | 2.50
Instrumentos/Medicamentos | 3 min (0.05 horas) | 38 | 1.90
Tempo de Permanência Mínimo |||   6.55

Considerando os tempos mínimos das etapas, teríamos o cálculo do seu tempo mínimo de permanência apresentada na tabela abaixo. 
Esse é o tempo mínimo porque ainda é necessário contabilizar o tempo em fila(s) de espera.

Vamos agora ilustrar a simulação através de um exemplo completo. Seja o arquivo de entrada exemplo apresentado abaixo. Importante ressaltar que as primeiras 6 linhas contem as especificações do HZ, seguidas do número de pacientes e das informações dos pacientes, uma linha por paciente.

```
0.2 2
0.5 2
0.1 2
0.05 2
0.5 2
0.05 2
10
0009600008 0 2017 3 21 2 1 5 43 2 110
0009600009 0 2017 3 21 2 0 3 1 5 21
0009600010 0 2017 3 21 2 1 3 4 2 8
0009600011 0 2017 3 21 2 2 15 28 4 68
0009600012 0 2017 3 21 2 0 3 2 7 9
0009600013 1 2017 3 21 3 0 2 2 2 8
0009600015 1 2017 3 21 3 0 1 3 1 4
0009600016 0 2017 3 21 3 2 5 14 1 28
0009600017 1 2017 3 21 4 0 1 0 0 0
0009600018 0 2017 3 21 4 1 2 8 3 11
```

A saída esperada para o programa é apresentada abaixo. Por exemplo, a primeira linha traz informações do paciente 9600008, que foi admitido em Tue Mar 21 02:00:00 2017 e teve alta em Tue Mar 21 12:33:00 2017, tendo permanecido no HZ por 10.55 horas, das quais 9.85 horas em atendimento e 0.70 horas em espera.

```
9600008 Tue Mar 21 02:00:00 2017 Tue Mar 21 12:33:00 2017 10.55 9.85 0.70
9600009 Tue Mar 21 02:00:00 2017 Tue Mar 21 06:36:00 2017 4.60 4.60 0.00
9600010 Tue Mar 21 02:00:00 2017 Tue Mar 21 05:06:00 2017 3.10 2.60 0.50
9600011 Tue Mar 21 02:00:00 2017 Tue Mar 21 12:27:00 2017 10.45 9.00 1.45
9600012 Tue Mar 21 02:00:00 2017 Tue Mar 21 08:39:00 2017 6.65 5.05 1.60
9600013 Tue Mar 21 03:00:00 2017 Tue Mar 21 04:12:00 2017 1.20 0.70 0.50
9600015 Tue Mar 21 03:00:00 2017 Tue Mar 21 03:42:00 2017 0.70 0.70 0.00
9600016 Tue Mar 21 03:00:00 2017 Tue Mar 21 07:27:00 2017 4.45 3.80 0.65
9600017 Tue Mar 21 04:00:00 2017 Tue Mar 21 04:42:00 2017 0.70 0.70 0.00
9600018 Tue Mar 21 04:00:00 2017 Tue Mar 21 13:00:00 2017 9.00 3.35 5.65
```


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