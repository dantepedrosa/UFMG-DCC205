#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <cmath>

/**
 * @file Tempo.hpp
 * @brief Declaração da classe Tempo e da estrutura DataHora.
 */

/**
 * @brief Estrutura que representa data e hora.
 */
struct DataHora {
    int dia;  // Dia do mês
    int mes;  // Mês do ano
    int ano;  // Ano
    float hora;  // Hora do dia como número decimal (ex.: 14.5 para 14:30)

    DataHora() : dia(0), mes(0), ano(0), hora(0.0) {}  // Construtor padrão
    DataHora(int d, int m, int a, float h) : dia(d), mes(m), ano(a), hora(h) {}

    bool operator<(const DataHora& outro) const {
        if (ano != outro.ano) return ano < outro.ano;
        if (mes != outro.mes) return mes < outro.mes;
        if (dia != outro.dia) return dia < outro.dia;
        return hora < outro.hora;
    }

    bool operator==(const DataHora& outro) const {
        return (dia == outro.dia) && (mes == outro.mes) &&
               (ano == outro.ano) && (hora == outro.hora);
    }

    std::string paraString() const {

        std::ostringstream oss;
        oss << dia << "/" << mes << "/" << ano << " " << std::fixed << std::setprecision(2) << hora;

        
        return oss.str();
    }
};

/**
 * @brief Classe que representa o tempo relativo a uma data de referência.
 */
class Tempo {
private:
    double horasDesdeReferencia;  // Tempo em horas desde a data de referência
    DataHora referencia;          // Data de referência

    /**
     * @brief Calcula o tempo em horas desde a data de referência.
     * 
     * @param dh DataHora a ser calculada.
     * @return double Tempo em horas desde a data de referência.
     */
    double calcularHorasReferencia(const DataHora& dh) const {
        std::tm ref_time = { 0, 0, 0, referencia.dia, referencia.mes - 1, referencia.ano - 1900 };
        std::tm dh_time = { 0, 0, 0, dh.dia, dh.mes - 1, dh.ano - 1900 };
        std::time_t ref_time_t = std::mktime(&ref_time);
        std::time_t dh_time_t = std::mktime(&dh_time);
        double diff_seconds = std::difftime(dh_time_t, ref_time_t);
        double diff_hours = diff_seconds / 3600.0 + dh.hora - referencia.hora;
        return diff_hours;
    }

public:
    Tempo() : horasDesdeReferencia(0.0), referencia() {}  // Construtor padrão

    Tempo(const DataHora& dh, const DataHora& ref) : referencia(ref) {
        horasDesdeReferencia = calcularHorasReferencia(dh);
    }

    Tempo(double horas, const DataHora& ref) : horasDesdeReferencia(horas), referencia(ref) {}

    double getHorasDesdeReferencia() const {
        return horasDesdeReferencia;
    }

    void setHorasDesdeReferencia(double horas) {
        horasDesdeReferencia = horas;
    }

    std::string paraString() const {
        std::tm ref_time = { 0, 0, 0, referencia.dia, referencia.mes - 1, referencia.ano - 1900 };
        std::time_t ref_time_t = std::mktime(&ref_time);
        std::time_t t = ref_time_t + static_cast<std::time_t>(horasDesdeReferencia * 3600);
        std::tm tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%c");
        return oss.str();
    }

    DataHora getReferencia() const {
        return referencia;
    }

    DataHora getDataHora() const {
        std::tm ref_time = { 0, 0, 0, referencia.dia, referencia.mes - 1, referencia.ano - 1900 };
        std::time_t ref_time_t = std::mktime(&ref_time);
        std::time_t t = ref_time_t + static_cast<std::time_t>(horasDesdeReferencia * 3600);
        std::tm tm = *std::localtime(&t);
        return DataHora(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour + tm.tm_min / 60.0);
    }

    bool operator<(const Tempo& outro) const {
        return horasDesdeReferencia < outro.horasDesdeReferencia;
    }

    bool operator<=(const Tempo& outro) const {
        return horasDesdeReferencia <= outro.horasDesdeReferencia;
    }

    bool operator>(const Tempo& outro) const {
        return horasDesdeReferencia > outro.horasDesdeReferencia;
    }

    bool operator>=(const Tempo& outro) const {
        return horasDesdeReferencia >= outro.horasDesdeReferencia;
    }

    bool operator==(const Tempo& outro) const {
        return horasDesdeReferencia == outro.horasDesdeReferencia;
    }

    bool operator!=(const Tempo& outro) const {
        return horasDesdeReferencia != outro.horasDesdeReferencia;
    }

    void somaHoras(double horas) {
        horasDesdeReferencia += horas;
    }
};
