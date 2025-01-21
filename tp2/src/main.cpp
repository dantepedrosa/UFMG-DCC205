#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Tempo.hpp"
#include "../include/Paciente.hpp"
#include "../include/Fila.hpp"
#include "../include/Procedimento.hpp"
#include "../include/Escalonador.hpp"

/*
Inicializa Condição de Término para FALSO
Inicializa as variáveis de estado do sistema
Inicializa o Relógio (usualmente zero)
Escalona a chegada de pacientes
Enquanto houver eventos ou filas não vazias
    Remove o próximo evento do escalonador
    Avança o relógio para o instante do próximo evento
    Verifica o próximo estado do paciente
    Se houver mais serviços para paciente
        Enfileira o paciente na fila adequada
    Senão
        Finaliza o atendimento (Alta Hospitalar)
    Para cada fila de espera que tenha pacientes
        Se há unidade disponível para execução
            Escalonar o evento de execução do serviço
    Atualizar as estatísticas
Fim
Gerar relatórios de estatísticas


Paciente* criarPaciente(const std::string& linha, const DataHora& referencia) {
    std::istringstream iss(linha);
    int id, alta, ano, mes, dia, hora, urgencia, mh, tl, ei, im;
    
    iss >> id >> alta >> ano >> mes >> dia >> hora >> urgencia >> mh >> tl >> ei >> im;

    DataHora admissao(ano, mes, dia, hora);
    Tempo tAdmissao(admissao, referencia);

    return new Paciente(id, alta == 1, tAdmissao, urgencia, mh, tl, ei, im);
}




int main(int argc, char const *argv[])
{
    // Erro entrada
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <caminho_para_arquivo>" << std::endl;
        return 1;
    }

    // abertura de arquivo
    std::string filePath = argv[1];
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
        return 1;
    }

    std::string line;

    // Cria Triagem
    std::getline(inputFile, line);
    std::istringstream iss(line);
    int durMin; float unidades;
    iss >> durMin >> unidades;
    Procedimento triagem("Triagem", durMin, unidades);
    
    // Cria Triagem
    std::getline(inputFile, line);
    std::istringstream iss(line);
    int durMin; float unidades;
    iss >> durMin >> unidades;
    Procedimento triagem("Triagem", durMin, unidades);

    // Cria Triagem
    std::getline(inputFile, line);
    std::istringstream iss(line);
    int durMin; float unidades;
    iss >> durMin >> unidades;
    Procedimento triagem("Triagem", durMin, unidades);

    // Cria Triagem
    std::getline(inputFile, line);
    std::istringstream iss(line);
    int durMin; float unidades;
    iss >> durMin >> unidades;
    Procedimento triagem("Triagem", durMin, unidades);

    // Cria Triagem
    std::getline(inputFile, line);
    std::istringstream iss(line);
    int durMin; float unidades;
    iss >> durMin >> unidades;
    Procedimento triagem("Triagem", durMin, unidades);

    // Cria Triagem
    std::getline(inputFile, line);
    std::istringstream iss(line);
    int durMin; float unidades;
    iss >> durMin >> unidades;
    Procedimento triagem("Triagem", durMin, unidades);



    



    inputFile.close();

    return 0;
}

*/

// main

// abrir arquivo

// inicializa variaveis
// para cada linha, chamar função de criar procedimento a partir de string x 6 vezes
// ler numero de linhas


// definir data de referência
// loop de pacientes (linhas)
    // para cada paciente (linhas), chamar função de criar paciente a partir de string.]
    // para cada paciente, enfileirar em cadastroPacientes (os pacientes devem ser impressos na mesma ordem no arquivo de saída)
    // para cada paciente, criado, criar evento de chegada e adicionar ao escalonador


// apos escalonar todos os pacientes
// loop while com temEventos()
    // retirar proximo evento
    // avançar relógio para o instante do próximo evento
    // conferir qual deve ser o proximo estado do paciente (a partir de vários ifs)
    // a depender do próximo estado do paciente
        // se houver mais serviços para paciente
            // enfileirar paciente na fila adequada
        // senão
            // finalizar atendimento (alta hospitalar)
    // para cada fila de espera que tenha pacientes
        // conferir se ha unidade disponivel para procedimento
            // escalonar evento de execução do serviço

    // atualizar estatisticas

// desinfileirar todos os pacientes de cadastroPacientes na ordem, imprimindo também as estatisticas coletadas



