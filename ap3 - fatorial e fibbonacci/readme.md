# Eficiência de Recursividade - Fatorial e Fibbonacci

## Descrição

Nesta atividade prática você vai avaliar o desempenho de códigos recursivos e não recursivos para as mesmas tarefas.
A atividade prática se divide em duas tarefas:


Tarefa 1: Cálculo de fatorial: crie um código recursivo e um iterativo para o cálculo de fatorial de um número.

Tarefa 2: Número de Fibonacci: crie um código recursivo e um iterativo para o cálculo do número de Fibonacci.

## O que deve ser feito

Codifique em linguagem C ou C++ cada versão. Para facilitar, empregue um parâmetro de linha de comando que define a tarefa a ser utilizada, nominalmente o fatorial ou o número de Fibonacci.

Descreva o seu plano de experimentos, ou seja, qual a faixa de valores para a qual as versões serão avaliadas (por exemplo, fatorial de 1 a 20). 

Meça o tempo de relógio para as várias configurações e verifique a sua correlação com a ordem de complexidade do respectivo algoritmo.

Meça os tempos de utilização de recursos (usuário e sistema) e compare com os tempos de relógio.

Para o algoritmo recursivo,  meça o tempo de execução para cada chamada usando o tempo de relógio e o gprof, compare as diferenças.

Para o algoritmo recursivo, insira, na chamada recursiva, uma função que consuma recursos computacionais (por exemplo calcule o seno de um número 1 milhão de vezes), e repita as medições do item 5.


Gere um relatório PDF com todos esses experimentos para ambas as tarefas.

## Observações

Você deve utilizar a linguagem C ou C++ para o desenvolvimento. O uso de estruturas pré-implementadas pelas bibliotecas-padrão da linguagem ou terceiros é terminantemente vetado.

Todos os arquivos relacionados à prática de aprendizagem devem ser submetidos na atividade designada para tal no Moodle. A entrega deve ser feita em um único arquivo com extensão .pdf, nomeado nome_ultimosobrenome_matricula.zip, onde nome, último sobrenome e matrícula devem ser substituídos por suas informações pessoais. O arquivo .pdf deve conter um relatório descrevendo as comparações feitas entre os tempos de relógio e sistema, a recursividade e a não recursividade para os códigos para Fibonacci e fatorial, o código não precisa ser entregue.