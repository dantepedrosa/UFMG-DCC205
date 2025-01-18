#include "../include/DataHoraTm.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

// Implementação da classe DataHoraTm
DataHoraTm::DataHoraTm(Data dataAtual, float horaAtual)
{
    dataHora.tm_year = dataAtual.getAno() - 1900;
    dataHora.tm_mon = dataAtual.getmes() - 1;
    dataHora.tm_mday = dataAtual.getDia();
    dataHora.tm_hour = static_cast<int>(horaAtual);
    dataHora.tm_min = static_cast<int>((horaAtual - dataHora.tm_hour) * 60);
    dataHora.tm_sec = 0;
    std::mktime(&dataHora);
}

DataHoraTm::~DataHoraTm() {}

std::string DataHoraTm::getStringDataHora(const std::string& formato)
{
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), formato.c_str(), &dataHora);
    return std::string(buffer);
}

void DataHoraTm::printDataHora(const std::string& formato)
{
    std::cout << getStringDataHora(formato) << std::endl;
}

void DataHoraTm::somaHoras(float horas)
{
    int horasInteiras = static_cast<int>(horas);
    int minutosAdicionais = static_cast<int>((horas - horasInteiras) * 60);
    dataHora.tm_hour += horasInteiras;
    dataHora.tm_min += minutosAdicionais;
    std::mktime(&dataHora); // Ajusta a data e hora corretamente
}

Data DataHoraTm::getData()
{
    return Data(dataHora.tm_mday, dataHora.tm_mon + 1, dataHora.tm_year + 1900);
}

int DataHoraTm::getHora()
{
    return dataHora.tm_hour;
}

int DataHoraTm::getMinutos()
{
    return dataHora.tm_min;
}

bool DataHoraTm::operator<(const DataHoraTm& outra) const
{
    return std::difftime(std::mktime(const_cast<std::tm*>(&dataHora)), std::mktime(const_cast<std::tm*>(&outra.dataHora))) < 0;
}

bool DataHoraTm::operator>(const DataHoraTm& outra) const
{
    return std::difftime(std::mktime(const_cast<std::tm*>(&dataHora)), std::mktime(const_cast<std::tm*>(&outra.dataHora))) > 0;
}

bool DataHoraTm::operator<=(const DataHoraTm& outra) const
{
    return !(*this > outra);
}

bool DataHoraTm::operator>=(const DataHoraTm& outra) const
{
    return !(*this < outra);
}

bool DataHoraTm::operator==(const DataHoraTm& outra) const
{
    return std::difftime(std::mktime(const_cast<std::tm*>(&dataHora)), std::mktime(const_cast<std::tm*>(&outra.dataHora))) == 0;
}

bool DataHoraTm::operator!=(const DataHoraTm& outra) const
{
    return !(*this == outra);
}
