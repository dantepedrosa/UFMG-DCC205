#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>

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
