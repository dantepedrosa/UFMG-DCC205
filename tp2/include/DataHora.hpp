#include <string>
#include <ctime>

#define ANO 1000000
#define MES 10000
#define DIA 100
#define HORA 60

/**
 * @brief Estrutura que representa uma data.
 */
struct Data
{
private:
    int dia;   // Dia da data
    int mes;   // Mês da data
    int ano;   // Ano da data

public:
    /**
     * @brief Constrói um novo objeto Data.
     * 
     * @param dia Dia da data
     * @param mes Mês da data
     * @param ano Ano da data
     */
    Data(int dia, int mes, int ano);

    /**
     * @brief Destrói o objeto Data.
     */
    ~Data();

    /**
     * @brief Obtém o dia da data.
     * 
     * @return int Dia da data
     */
    int getDia();

    /**
     * @brief Obtém o mês da data.
     * 
     * @return int Mês da data
     */
    int getmes();

    /**
     * @brief Obtém o ano da data.
     * 
     * @return int Ano da data
     */
    int getAno();
};

/**
 * @brief Classe que representa uma data e hora.
 */
class DataHora
{
private:
    int codDataHora; // Código que representa a data e hora

    /**
     * @brief Converte uma data e hora para um código personalizado.
     * 
     * @param data Data a ser convertida
     * @param hora Hora a ser convertida
     * @return int Código personalizado
     */
    int converteParaCodigo(Data data, float hora);

    /**
     * @brief Converte um código personalizado para uma string de data e hora.
     * 
     * @param codigo Código personalizado
     * @param formato Formato da string de data e hora
     * @return std::string Data e hora como uma string
     */
    std::string converteDeCodigo(int codigo, std::string formato);

public:
    /**
     * @brief Constrói um novo objeto DataHora.
     * 
     * @param dataReferencia Data de referência
     * @param dataAtual Data atual
     * @param horaAtual Hora atual
     */
    DataHora(Data dataReferencia, Data dataAtual, float horaAtual);

    /**
     * @brief Destrói o objeto DataHora.
     */
    ~DataHora();

    /**
     * @brief Obtém a data e hora como uma string no formato especificado.
     * 
     * @param formato Formato da string de data e hora
     * @return std::string Data e hora como uma string
     */
    std::string getStringDataHora(std::string formato);

    /**
     * @brief Imprime a data e hora no formato especificado.
     * 
     * @param formato Formato da string de data e hora
     */
    void printDataHora(std::string formato);

    /**
     * @brief Obtém o código que representa a data e hora.
     * 
     * @return int Código que representa a data e hora
     */
    int getCodDataHora();

    /**
     * @brief Soma um número de horas ao código de data e hora.
     * 
     * @param horas Número de horas a serem somadas
     */
    void somaHoras(float horas);

    /**
     * @brief Obtém a data a partir do código de data e hora.
     * 
     * @return Data A data correspondente ao código
     */
    Data getData();

    /**
     * @brief Obtém a hora a partir do código de data e hora.
     * 
     * @return float A hora correspondente ao código
     */
    float getHora();

    /**
     * @brief Compara se a data e hora atual é menor que a data e hora passada.
     * 
     * @param outra DataHora a ser comparada
     * @return true Se a data e hora atual é menor
     * @return false Caso contrário
     */
    bool operator<(const DataHora& outra) const;

    /**
     * @brief Compara se a data e hora atual é maior que a data e hora passada.
     * 
     * @param outra DataHora a ser comparada
     * @return true Se a data e hora atual é maior
     * @return false Caso contrário
     */
    bool operator>(const DataHora& outra) const;

    /**
     * @brief Compara se a data e hora atual é menor ou igual à data e hora passada.
     * 
     * @param outra DataHora a ser comparada
     * @return true Se a data e hora atual é menor ou igual
     * @return false Caso contrário
     */
    bool operator<=(const DataHora& outra) const;

    /**
     * @brief Compara se a data e hora atual é maior ou igual à data e hora passada.
     * 
     * @param outra DataHora a ser comparada
     * @return true Se a data e hora atual é maior ou igual
     * @return false Caso contrário
     */
    bool operator>=(const DataHora& outra) const;

    /**
     * @brief Compara se a data e hora atual é igual à data e hora passada.
     * 
     * @param outra DataHora a ser comparada
     * @return true Se a data e hora atual é igual
     * @return false Caso contrário
     */
    bool operator==(const DataHora& outra) const;

    /**
     * @brief Compara se a data e hora atual é diferente da data e hora passada.
     * 
     * @param outra DataHora a ser comparada
     * @return true Se a data e hora atual é diferente
     * @return false Caso contrário
     */
    bool operator!=(const DataHora& outra) const;
};
