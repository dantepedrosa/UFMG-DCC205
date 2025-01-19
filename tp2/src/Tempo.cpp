#include "Tempo.hpp"

Tempo::Tempo(const DataHora& dh, const DataHora& ref) : referencia(ref) {
    horasDesdeReferencia = calcularHorasReferencia(dh);
}

double Tempo::calcularHorasReferencia(const DataHora& dh) const {
    std::tm time_in = { 0, 0, 0, dh.dia, dh.mes - 1, dh.ano - 1900 };
    std::time_t time_temp = std::mktime(&time_in);
    double horas = dh.hora;
    return std::difftime(time_temp, std::mktime(&time_in)) / 3600.0 + horas;
}

double Tempo::getHorasDesdeReferencia() const {
    return horasDesdeReferencia;
}

std::string Tempo::paraString() const {
    std::time_t t = std::time(nullptr) + static_cast<std::time_t>(horasDesdeReferencia * 3600);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%c %Y");
    return oss.str();
}

bool Tempo::operator<(const Tempo& outro) const {
    return horasDesdeReferencia < outro.horasDesdeReferencia;
}

bool Tempo::operator==(const Tempo& outro) const {
    return horasDesdeReferencia == outro.horasDesdeReferencia;
}

void Tempo::somaHoras(double horas) {
    horasDesdeReferencia += horas;
}
