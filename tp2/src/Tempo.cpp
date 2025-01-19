#include "Tempo.hpp"
#include <chrono>
#include <ctime>

Tempo::Tempo(const DataHora& dh, const DataHora& ref) : referencia(ref) {
    horasDesdeReferencia = calcularHorasReferencia(dh);
}

double Tempo::calcularHorasReferencia(const DataHora& dh) const {
    std::tm ref_time = { 0, 0, 0, referencia.dia, referencia.mes - 1, referencia.ano - 1900 };
    std::tm dh_time = { 0, 0, 0, dh.dia, dh.mes - 1, dh.ano - 1900 };
    std::time_t ref_time_t = std::mktime(&ref_time);
    std::time_t dh_time_t = std::mktime(&dh_time);
    double diff_seconds = std::difftime(dh_time_t, ref_time_t);
    double diff_hours = diff_seconds / 3600.0 + dh.hora - referencia.hora;
    return diff_hours;
}

double Tempo::getHorasDesdeReferencia() const {
    return horasDesdeReferencia;
}

std::string Tempo::paraString() const {
    std::tm ref_time = { 0, 0, 0, referencia.dia, referencia.mes - 1, referencia.ano - 1900 };
    std::time_t ref_time_t = std::mktime(&ref_time);
    std::time_t t = ref_time_t + static_cast<std::time_t>(horasDesdeReferencia * 3600);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%c");
    return oss.str();
}

bool Tempo::operator<(const Tempo& outro) const {
    return horasDesdeReferencia < outro.horasDesdeReferencia;
}

bool Tempo::operator<=(const Tempo& outro) const {
    return horasDesdeReferencia <= outro.horasDesdeReferencia;
}

bool Tempo::operator>(const Tempo& outro) const {
    return horasDesdeReferencia > outro.horasDesdeReferencia;
}

bool Tempo::operator>=(const Tempo& outro) const {
    return horasDesdeReferencia >= outro.horasDesdeReferencia;
}

bool Tempo::operator==(const Tempo& outro) const {
    return horasDesdeReferencia == outro.horasDesdeReferencia;
}

bool Tempo::operator!=(const Tempo& outro) const {
    return horasDesdeReferencia != outro.horasDesdeReferencia;
}

void Tempo::somaHoras(double horas) {
    horasDesdeReferencia += horas;
}
