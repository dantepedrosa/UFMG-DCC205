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