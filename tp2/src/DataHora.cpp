#include "../include/DataHora.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

#define ANO 1000000
#define MES 10000
#define DIA 100
#define HORA 60

// Implementação da classe Data
Data::Data(int dia, int mes, int ano) : dia(dia), mes(mes), ano(ano) {}
Data::~Data() {}

int Data::getDia() { return dia; }
int Data::getmes() { return mes; }
int Data::getAno() { return ano; }

// Implementação da classe DataHora
DataHora::DataHora(Data dataReferencia, Data dataAtual, float horaAtual)
{
    // TODO - Trocar metodo de conversão
    codDataHora = converteParaCodigo(dataAtual, horaAtual);
}

DataHora::~DataHora() {}

int DataHora::converteParaCodigo(Data data, float hora)
{
    int codigo = 0;
    codigo += data.getAno() * ANO;
    codigo += data.getmes() * MES;
    codigo += data.getDia() * DIA;
    codigo += (int)(hora * HORA);
    return codigo;
}

std::string DataHora::converteDeCodigo(int codigo, std::string formato)
{
    // TODO - Trocar a função para utilizar o getData e getHora
    // Converte o código personalizado para uma string de data e hora
    int ano = codigo / ANO;
    int mes = (codigo / MES) % 100;
    int dia = (codigo / DIA) % 100;
    int hora = (codigo % ANO) / HORA;
    int minutos = codigo % HORA;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << dia << "/"
        << std::setw(2) << std::setfill('0') << mes << "/"
        << ano << " "
        << std::setw(2) << std::setfill('0') << hora << ":"
        << std::setw(2) << std::setfill('0') << minutos;
    return oss.str();
}

std::string DataHora::getStringDataHora(std::string formato)
{
    return converteDeCodigo(codDataHora, formato);
}

void DataHora::printDataHora(std::string formato)
{
    std::cout << getStringDataHora(formato) << std::endl;
}

int DataHora::getCodDataHora()
{
    return codDataHora;
}

void DataHora::somaHoras(float horas)
{
    // TODO - Consertar somaHoras
    int minutosAdicionais = (int)(horas * HORA);
    codDataHora += minutosAdicionais;
}

Data DataHora::getData()
{
    int ano = codDataHora / ANO;
    int mes = (codDataHora / MES) % 100;
    int dia = (codDataHora / DIA) % 100;
    return Data(dia, mes, ano);
}

float DataHora::getHora()
{
    int minutosTotais = codDataHora % ANO;
    int horas = minutosTotais / HORA;
    int minutos = minutosTotais % HORA;
    return horas + minutos / 60.0;
}

bool DataHora::operator<(const DataHora& outra) const
{
    return codDataHora < outra.codDataHora;
}

bool DataHora::operator>(const DataHora& outra) const
{
    return codDataHora > outra.codDataHora;
}

bool DataHora::operator<=(const DataHora& outra) const
{
    return codDataHora <= outra.codDataHora;
}

bool DataHora::operator>=(const DataHora& outra) const
{
    return codDataHora >= outra.codDataHora;
}

bool DataHora::operator==(const DataHora& outra) const
{
    return codDataHora == outra.codDataHora;
}

bool DataHora::operator!=(const DataHora& outra) const
{
    return codDataHora != outra.codDataHora;
}
