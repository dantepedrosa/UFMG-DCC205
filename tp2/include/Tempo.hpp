#ifndef TEMPO_HPP
#define TEMPO_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>

struct DataHora {
    int dia;
    int mes;
    int ano;
    float hora; // Representa a hora como um número decimal (por exemplo, 14.5 para 14:30)

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
    double horasDesdeReferencia; // Representa o tempo em horas desde a data de referência
    DataHora referencia; // Referência específica para a instância

    double calcularHorasReferencia(const DataHora& dh) const;

public:
    Tempo() : horasDesdeReferencia(0.0), referencia() {} // Construtor padrão
    Tempo(const DataHora& dh, const DataHora& ref);

    double getHorasDesdeReferencia() const;
    std::string paraString() const;
    DataHora getReferencia() const;
    DataHora getDataHora() const; // Novo método para retornar DataHora

    bool operator<(const Tempo& outro) const;
    bool operator==(const Tempo& outro) const;
    bool operator<=(const Tempo& outro) const;
    bool operator>(const Tempo& outro) const;
    bool operator>=(const Tempo& outro) const;
    bool operator!=(const Tempo& outro) const;
    
    void somaHoras(double horas);
};

#endif  // TEMPO_HPP
