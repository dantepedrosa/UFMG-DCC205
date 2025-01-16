#include "../include/DataHora.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

// Implementação da classe Data
Data::Data(int dia, int mes, int ano) : dia(dia), mes(mes), ano(ano) {}
Data::~Data() {}

int Data::getDia() { return dia; }
int Data::getmes() { return mes; }
int Data::getAno() { return ano; }

// Implementação da classe DataHora
DataHora::DataHora(Data dataAtual, float horaAtual)
{
    codDataHora = converteParaCodigo(dataAtual, horaAtual);
}

DataHora::~DataHora() {}

unsigned int DataHora::converteParaCodigo(Data data, float hora)
{
    unsigned int codigo = 0;
    codigo += (data.getAno() - 2000) * ANO;
    codigo += data.getmes() * MES;
    codigo += data.getDia() * DIA;
    codigo += (int)(hora * HORA);
    return codigo;
}

std::string DataHora::converteDeCodigo(unsigned int codigo)
{
    Data data = getData();
    int hora = getHora();
    int minutos = getMinutos();
    std::string diaSemana = getDiaSemana(data);
    std::string mes = getMes(data);

    std::ostringstream oss;
    oss << diaSemana << " " << mes << " "
        << std::setw(2) << std::setfill('0') << data.getDia() << " "
        << std::setw(2) << std::setfill('0') << hora << ":"
        << std::setw(2) << std::setfill('0') << minutos << ":00 "
        << data.getAno();
    return oss.str();
}

std::string DataHora::getStringDataHora()
{
    return converteDeCodigo(codDataHora);
}

void DataHora::printDataHora()
{
    std::cout << getStringDataHora() << std::endl;
}

unsigned int DataHora::getCodDataHora()
{
    return codDataHora;
}

unsigned int DataHora::somaHoras(float horasSoma)
{
    int horaAtual = codDataHora % DIA; // Consegue as horas atuais (Ex. 2350)
    codDataHora -= horaAtual;          // Reseta para realizar os calculos

    horaAtual += (int)(horasSoma * HORA); // Soma com o número Ex. 2350 + 7530 = 9880

    if (horaAtual >= 24 * HORA)
    {
        int diasAdicionais = horaAtual / (24 * HORA); // Ex. diasAdicionais = 4
        codDataHora += diasAdicionais * DIA;          // Ex. codDataHora += 40000

        if (codDataHora % MES >= 31 * DIA)
            std::overflow_error("Número de dias do mês excedidos");

        horaAtual -= (diasAdicionais * 24 * HORA); // Ex. 9880 - (2400 * 4) = 280
    }

    codDataHora += horaAtual; // Ex. codDataHora += 280

    return codDataHora;
}

Data DataHora::getData()
{
    int ano = (int)(codDataHora / ANO) + 2000;
    int mes = ((int)(codDataHora / MES)) % 100;
    int dia = ((int)(codDataHora / DIA)) % 100;
    return Data(dia, mes, ano);
}

int DataHora::getHora()
{
    int horas = codDataHora % DIA;
    return (horas / 100);
}

int DataHora::getMinutos()
{
    float fracaoMinutos = codDataHora % HORA; // 2350 -> 50
    fracaoMinutos /= 100;
    int minutos = (int)(fracaoMinutos * 60);
    return minutos;
}

std::string DataHora::getDiaSemana(Data data)
{
    std::tm timeinfo = {};
    timeinfo.tm_year = data.getAno() - 1900;
    timeinfo.tm_mon = data.getmes() - 1;
    timeinfo.tm_mday = data.getDia();

    std::mktime(&timeinfo);

    char buffer[4];
    std::strftime(buffer, sizeof(buffer), "%a", &timeinfo);
    return std::string(buffer);
}

std::string DataHora::getMes(Data data)
{
    std::tm timeinfo = {};
    timeinfo.tm_year = data.getAno() - 1900;
    timeinfo.tm_mon = data.getmes() - 1;
    timeinfo.tm_mday = data.getDia();

    std::mktime(&timeinfo);

    char buffer[4];
    std::strftime(buffer, sizeof(buffer), "%b", &timeinfo);
    return std::string(buffer);
}

bool DataHora::operator<(const DataHora &outra) const
{
    return codDataHora < outra.codDataHora;
}

bool DataHora::operator>(const DataHora &outra) const
{
    return codDataHora > outra.codDataHora;
}

bool DataHora::operator<=(const DataHora &outra) const
{
    return codDataHora <= outra.codDataHora;
}

bool DataHora::operator>=(const DataHora &outra) const
{
    return codDataHora >= outra.codDataHora;
}

bool DataHora::operator==(const DataHora &outra) const
{
    return codDataHora == outra.codDataHora;
}

bool DataHora::operator!=(const DataHora &outra) const
{
    return codDataHora != outra.codDataHora;
}
