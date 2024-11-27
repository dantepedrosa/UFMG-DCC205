#ifndef ORDIND_H
#define ORDIND_H

#include <vector>
#include <string>

/**
 * @class OrdInd
 * @brief Classe para manipulação de ordenação indireta de registros.
 * 
 * A classe permite carregar uma base de dados, realizar ordenação indireta
 * com base em diferentes atributos (Nome, CPF, Endereço) e imprimir os dados
 * na ordem definida pelos índices.
 */
class OrdInd {
private:
    std::vector<std::vector<std::string>> dados; ///< Base de dados original.
    std::vector<int> indicesNome;               ///< Vetor de índices para ordenação por Nome.
    std::vector<int> indicesCPF;                ///< Vetor de índices para ordenação por CPF.
    std::vector<int> indicesEndereco;           ///< Vetor de índices para ordenação por Endereço.

    /**
     * @brief Função de comparação genérica para ordenação de índices.
     * @param i Índice do primeiro registro.
     * @param j Índice do segundo registro.
     * @param atributo Identificador do atributo a ser usado como chave de ordenação.
     * @return true se o registro `i` for menor que o registro `j` para o atributo dado.
     */
    bool compara(int i, int j, int atributo) const;

public:
    /**
     * @brief Construtor da classe OrdInd.
     * @param numRegistros Número total de registros.
     * @param numAtributos Número total de atributos por registro.
     */
    OrdInd(int numRegistros, int numAtributos);

    /**
     * @brief Carrega os dados de um arquivo .xcsv para a base de dados.
     * @param nomeEntrada Caminho do arquivo de entrada.
     * @return true se o arquivo for carregado com sucesso, false caso contrário.
     */
    bool carregaArquivo(const std::string &nomeEntrada);

    /**
     * @brief Ordena os índices com base no atributo Nome.
     */
    void ordenaPorNome();

    /**
     * @brief Ordena os índices com base no atributo CPF.
     */
    void ordenaPorCPF();

    /**
     * @brief Ordena os índices com base no atributo Endereço.
     */
    void ordenaPorEndereco();

    /**
     * @brief Imprime os registros na ordem definida pelo vetor de índices de Nome.
     */
    void imprimePorNome();

    /**
     * @brief Imprime os registros na ordem definida pelo vetor de índices de CPF.
     */
    void imprimePorCPF();

    /**
     * @brief Imprime os registros na ordem definida pelo vetor de índices de Endereço.
     */
    void imprimePorEndereco();
};

#endif // ORDIND_H
