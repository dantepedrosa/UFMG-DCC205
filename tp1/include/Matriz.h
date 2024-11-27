#ifndef MATRIZ_H
#define MATRIZ_H

#include <cstring> // Para manipulação de strings

struct Matriz {
    char ***dados;  // Matriz de registros (linhas x colunas)
    int linhas;
    int colunas;

    Matriz(int linhas, int colunas);
    ~Matriz();

    void set(int linha, int coluna, const char *valor);
    const char *get(int linha, int coluna) const;
};

#endif // MATRIZ_H
