#include <string>
#include <ctime>
#include "DataHora.hpp"



/**
 * @brief Classe que representa uma data e hora.
 */
class DataHoraTm
{
private:
    std::tm dataHora; // Estrutura que representa a data e hora

public:
    /**
     * @brief Constrói um novo objeto DataHoraTm.
     * 
     * @param dataAtual Data atual
     * @param horaAtual Hora atual
     */
    DataHoraTm(Data dataAtual, float horaAtual);

    /**
     * @brief Destrói o objeto DataHoraTm.
     */
    ~DataHoraTm();

    /**
     * @brief Obtém a data e hora como uma string no formato especificado.
     * 
     * @param formato Formato da string de data e hora
     * @return std::string Data e hora como uma string
     */
    std::string getStringDataHora(const std::string& formato);

    /**
     * @brief Imprime a data e hora no formato especificado.
     * 
     * @param formato Formato da string de data e hora
     */
    void printDataHora(const std::string& formato);

    /**
     * @brief Soma um número de horas ao objeto DataHoraTm.
     * 
     * @param horas Número de horas a serem somadas
     */
    void somaHoras(float horas);

    /**
     * @brief Obtém a data a partir do objeto DataHoraTm.
     * 
     * @return Data A data correspondente
     */
    Data getData();

    /**
     * @brief Obtém a hora a partir do objeto DataHoraTm.
     * 
     * @return int A hora correspondente
     */
    int getHora();

    /**
     * @brief Obtém o componente de minutos da hora.
     * 
     * @return int O componente de minutos da hora.
     */
    int getMinutos();

    /**
     * @brief Compara se a data e hora atual é menor que a data e hora passada.
     * 
     * @param outra DataHoraTm a ser comparada
     * @return true Se a data e hora atual é menor
     * @return false Caso contrário
     */
    bool operator<(const DataHoraTm& outra) const;

    /**
     * @brief Compara se a data e hora atual é maior que a data e hora passada.
     * 
     * @param outra DataHoraTm a ser comparada
     * @return true Se a data e hora atual é maior
     * @return false Caso contrário
     */
    bool operator>(const DataHoraTm& outra) const;

    /**
     * @brief Compara se a data e hora atual é menor ou igual à data e hora passada.
     * 
     * @param outra DataHoraTm a ser comparada
     * @return true Se a data e hora atual é menor ou igual
     * @return false Caso contrário
     */
    bool operator<=(const DataHoraTm& outra) const;

    /**
     * @brief Compara se a data e hora atual é maior ou igual à data e hora passada.
     * 
     * @param outra DataHoraTm a ser comparada
     * @return true Se a data e hora atual é maior ou igual
     * @return false Caso contrário
     */
    bool operator>=(const DataHoraTm& outra) const;

    /**
     * @brief Compara se a data e hora atual é igual à data e hora passada.
     * 
     * @param outra DataHoraTm a ser comparada
     * @return true Se a data e hora atual é igual
     * @return false Caso contrário
     */
    bool operator==(const DataHoraTm& outra) const;

    /**
     * @brief Compara se a data e hora atual é diferente da data e hora passada.
     * 
     * @param outra DataHoraTm a ser comparada
     * @return true Se a data e hora atual é diferente
     * @return false Caso contrário
     */
    bool operator!=(const DataHoraTm& outra) const;
};
