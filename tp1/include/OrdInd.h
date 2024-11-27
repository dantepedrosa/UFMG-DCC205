#ifndef ORDIND_H
#define ORDIND_H

#include <vector>
#include <string>

/**
 * @class OrdInd
 * @brief Classe para manipulação da base de dados e índices de ordenação.
 * 
 * Essa classe gerencia os registros, permitindo acesso à base e aos vetores de índices,
 * sem implementar a lógica de ordenação diretamente.
 */
class OrdInd {
private:
    std::vector<std::vector<std::string>> dados; ///< Base de dados original.
    std::vector<int> indicesNome;               ///< Vetor de índices para ordenação por Nome.
    std::vector<int> indicesCPF;                ///< Vetor de índices para ordenação por CPF.
    std::vector<int> indicesEndereco;           ///< Vetor de índices para ordenação por Endereço.

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
     * @brief Retorna o vetor de índices para o Nome.
     * @return Referência ao vetor de índices.
     */
    std::vector<int> &getIndicesNome();

    /**
     * @brief Retorna o vetor de índices para o CPF.
     * @return Referência ao vetor de índices.
     */
    std::vector<int> &getIndicesCPF();

    /**
     * @brief Retorna o vetor de índices para o Endereço.
     * @return Referência ao vetor de índices.
     */
    std::vector<int> &getIndicesEndereco();

    /**
     * @brief Acessa o dado correspondente ao índice e atributo.
     * @param index Índice do registro.
     * @param atributo Índice do atributo.
     * @return Valor do atributo como string.
     */
    const std::string &getDado(int index, int atributo) const;

    /**
     * @brief Retorna o número total de registros.
     */
    int getNumRegistros() const;
};

#endif // ORDIND_H
