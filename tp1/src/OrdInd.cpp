
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "OrdInd.hpp"


OrdInd::OrdInd() : dados(nullptr), linhas(0), colunas(0), atributos(nullptr), tipoAtributos(nullptr), indices(nullptr){
    // Inicializa todos os membros como 0 ou nullptr
}

OrdInd::~OrdInd() {

    // Destroi todos os apontadores presentes em dados
    if (dados) {
        for (int i = 0; i < linhas; ++i) {
            delete[] dados[i];
        }
        delete[] dados;
    }

    delete[] atributos;
    delete[] tipoAtributos;

    // Destrói todos os apontadores presentes em índices
    if (indices) {
        for (int i = 0; i < colunas; ++i) {
            delete[] indices[i];
        }
        delete[] indices;
    }
}

int OrdInd::CarregaArquivo(const std::string& nomeentrada) {

    // Testar se arquivo foi aberto
    std::ifstream Arquivo(nomeentrada);
    if (!Arquivo.is_open()) {
        std::cerr << "Error opening file: " << nomeentrada << std::endl;
        return -1;
    }

    // Inicialização de parâmetros usados múltiplas vezes
    std::string strLinha;
    std::string substr;

    // Ler quantidade de colunas
    getline(Arquivo, strLinha);
    this->colunas = stoi(strLinha);

    // Inicializa arrays de atributos e tipoAtributos
    this->atributos = new std::string[this->colunas];
    this->tipoAtributos = new std::string[this->colunas];

    // Inicializa array de indices
    this->indices = new ApontadorIndice**[this->colunas];
    for (int i = 0; i < this->colunas; ++i) {
        this->indices[i] = new ApontadorIndice*[this->linhas];
        for (int j = 0; j < this->linhas; ++j) {
            this->indices[i][j] = nullptr;
        }
    }

    // Ler nomes de colunas e tipo de dados
    for(int i=0; i < this->colunas; i++){
        getline(Arquivo, strLinha);
        std::stringstream ss(strLinha);
        getline(ss, substr, ',');
        this->atributos[i] = substr;
        getline(ss, substr, ',');
        this->tipoAtributos[i] = substr;
    }

    // Ler quantidade de entradas de dados
    getline(Arquivo, strLinha);
    this->linhas = stoi(strLinha);

    // Ler entradas de dados e armazenar em dados
    for(int i = 0; i < this->linhas; i++){
        
        getline(Arquivo, strLinha);
        std::stringstream ss(strLinha);
        
        for(int j = 0; j < this->colunas; j++){
            std::stringstream ss(strLinha);
            getline(ss, substr, ',');
            this->dados[i][j] = substr;
        }
    }

    return 0;
}

int OrdInd::NumAtributos() const {
    return colunas;
}

int OrdInd::NomeAtributo(int pos, std::string& nome) const {
    
    if (pos < 0 || pos >= colunas){
        std::cerr << "ID " << pos << " não representa nenhum atributo" << std::endl;
        return -1;
    }

    nome = atributos[pos];

    return 0;
}

int OrdInd::IDAtributo(std::string nome) {
    
    int i;
    for(i=0; i < colunas; i++){
        if(!atributos[i].compare(nome))
            return i; // Caso tenha encontrado
    }

    return -1;  // Caso não encontrado
}

int OrdInd::CriaIndice(int atribid) {
    
    if (atribid < 0 || atribid >= colunas) {
        std::cerr << "atribid " << atribid << " fora dos limites" << std::endl;
        return -1;
    }

    indices[atribid] = new ApontadorIndice*[linhas];

    int i;
    for (i = 0; i < linhas; ++i) {
        indices[atribid][i] = new ApontadorIndice;
        indices[atribid][i]->chave = dados[i][atribid];
        indices[atribid][i]->pos = i;
    }

    return 0;
}

int OrdInd::OrdenaIndice(int atribid, std::string ordenacao) {
    
    // Validação de entrada
    if (atribid < 0 || atribid >= colunas) {
        std::cerr << "atribid " << atribid << " fora dos limites" << std::endl;
        return -1;
    }

    if (ordenacao == "quick") {
        quicksort(indices[atribid], linhas);
    } else if (ordenacao == "shell") {
        shellSort(indices[atribid], linhas);
    } else if (ordenacao == "insertion") {
        insertionSort(indices[atribid], linhas);
    } else {                                                                
        std::cerr << "Ordenação " << ordenacao << " não suportada" << std::endl;    // Ordenação não suportada
        return -1;
    }
    
    /* TODO - Caso seja implementado bucket sort
    else if (ordenacao == "bucket") {
        bucketSort(indices[atribid], linhas);
    }
    */ 

    return 0;
}

int OrdInd::ImprimeOrdenadoIndice(int atribid) const {
    
    // Validação de entrada
    if (atribid < 0 || atribid >= colunas) {
        std::cerr << "atribid " << atribid << " fora dos limites" << std::endl;
        return -1;
    }

    for (int i = 0; i < linhas; ++i) {
        std::cout << indices[atribid][i]->chave << std::endl;
    }

    return 0;
}