#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>
#include <fstream>

class Voo {
public:
    std::string origem;
    std::string destino;
    float preco;
    int assentos;
    std::time_t partida;
    std::time_t chegada;
    int numParadas;
    std::time_t duracao;

    Voo(const std::string& linha) {
        std::istringstream ss(linha);
        std::string partidaStr, chegadaStr;

        ss >> origem >> destino >> preco >> assentos >> partidaStr >> chegadaStr >> numParadas;

        if (ss.fail()) {
            throw std::runtime_error("Erro ao processar a linha de entrada.");
        }

        partida = parseTempo(partidaStr);
        chegada = parseTempo(chegadaStr);
        duracao = chegada - partida;
    }

private:
    std::time_t parseTempo(const std::string& datetime) {
        std::tm tm = {};
        char tzSign;
        int tzHour, tzMinute;

        std::istringstream ss(datetime);
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
        ss >> tzSign >> std::setw(2) >> tzHour;
        ss.ignore(1);
        ss >> std::setw(2) >> tzMinute;

        if (ss.fail()) {
            throw std::runtime_error("Erro ao interpretar data/hora.");
        }

        std::time_t tt = std::mktime(&tm);

        int tzOffset = (tzHour * 3600) + (tzMinute * 60);
        if (tzSign == '-') {
            tt += tzOffset;
        } else {
            tt -= tzOffset;
        }

        return tt;
    }
};


void leVoosdeArquivo(const std::string& filePath, Voo** voos, int numLinhas) {
    std::ifstream inputFile(filePath);

    std::string line;
    std::istringstream iss;

    for(int i = 0; i < numLinhas; i++){
        std::getline(inputFile, line);
        voos[i] = new Voo(line);
    }

    inputFile.close();
}

void leVoosdeEntrada(Voo** voos, int numLinhas) {
    std::string line;
    std::istringstream iss;

    for(int i = 0; i < numLinhas; i++){
        std::getline(std::cin, line);
        voos[i] = new Voo(line);
    }
}

int main(int argc, char const* argv[]) {
    
    // Leitura de dados
    // ---------------------------------------------------

    bool fileEnabled = false;
    std::string filePath;

    switch (argc) {
        case 1:
            fileEnabled = false;
            return 1;
        case 2:
            fileEnabled = true;
            filePath = argv[1];
            break;
        default:
            std::cerr << "Uso: " << argv[0] << " <caminho_para_arquivo> [-f]" << std::endl;
            return 1;
    }

    std::string line;
    std::istringstream iss;
    int numLinhas;

    if(fileEnabled){
        std::ifstream inputFile(filePath);

        // Conseguir numero de linhas
        std::getline(inputFile, line);
        numLinhas = std::stoi(line);
        inputFile.close();
    } else {
        std::getline(std::cin, line);
        numLinhas = std::stoi(line);
    }

    Voo* voos[numLinhas];

    if(fileEnabled){
        leVoosdeArquivo(filePath, voos, numLinhas);
    } else {
        leVoosdeEntrada(voos, numLinhas);
    }

    // 
    // ---------------------------------------------------




    // TODO - Deletar voos com delete

    return 0;
}