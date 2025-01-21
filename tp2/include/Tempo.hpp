#ifndef TEMPO_HPP
#define TEMPO_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>

struct DataHora {
    int dia; //Dia do mês
    int mes; //Mês do ano
    int ano; //Ano
    float hora; //Hora do dia como número decimal (por exemplo, 14.5 para 14:30)

    DataHora() : dia(0), mes(0), ano(0), hora(0.0) {} // Construtor padrão
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
};

class Tempo {
private:
    double horasDesdeReferencia; //Tempo em horas desde a data de referência
    DataHora referencia; //Data de referência

    /**
     * @brief Calcula o tempo em horas desde a data de referência.
     * 
     * @param dh DataHora a ser calculada.
     * @return double Tempo em horas desde a data de referência.
     */
    double calcularHorasReferencia(const DataHora& dh) const;

public:
    Tempo() : horasDesdeReferencia(0.0), referencia() {} // Construtor padrão
    Tempo(const DataHora& dh, const DataHora& ref);

    /**
     * @brief Obtém o tempo em horas desde a data de referência.
     * 
     * @return double Tempo em horas desde a data de referência.
     */
    double getHorasDesdeReferencia() const;

    /**
     * @brief Converte o tempo para string.
     * 
     * @return std::string Tempo em formato string.
     */
    std::string paraString() const;

    /**
     * @brief Obtém a data de referência.
     * 
     * @return DataHora Data de referência.
     */
    DataHora getReferencia() const;

    /**
     * @brief Obtém a data e hora correspondente ao tempo.
     * 
     * @return DataHora Data e hora correspondente ao tempo.
     */
    DataHora getDataHora() const;

    bool operator<(const Tempo& outro) const;
    bool operator==(const Tempo& outro) const;
    bool operator<=(const Tempo& outro) const;
    bool operator>(const Tempo& outro) const;
    bool operator>=(const Tempo& outro) const;
    bool operator!=(const Tempo& outro) const;

    /**
     * @brief Soma um tempo em horas ao tempo atual.
     * 
     * @param horas Tempo em horas a ser somado.
     */
    void somaHoras(double horas);
};

#endif  // TEMPO_HPP
