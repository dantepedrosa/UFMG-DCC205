#pragma once

#include <string>

class OrdInd
{
private:
    std::string** dados; // Dados carregados (matriz de strings)
    int linhas;          // Número de linhas
    int colunas;         // Número de colunas (atributos)
    std::string* atributos; // Nomes dos atributos
    int** indices;       // Índices ordenados por atributo

public:
    OrdInd();
    ~OrdInd();
    int CarregaArquivo(const std::string& nomeentrada);
    int NumAtributos() const;
    int NomeAtributo(int pos, std::string& nome) const;
    bool CriaIndice(int atribid);
    int OrdenaIndice(int atribid);
    int ImprimeOrdenadoIndice(int atribid) const;
};
