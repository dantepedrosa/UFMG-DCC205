#ifndef MAT_H
#define MAT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <getopt.h>

#include "msgassert.h"


#define MAXTAM 5

/**
 * @brief Estrutura que representa uma matriz.
 * 
 * @struct mat
 * @var mat::m Matriz de valores do tipo double.
 * @var mat::tamx Número de linhas.
 * @var mat::tamy Número de colunas.
 * @var mat::id Identificador único.
 */
typedef struct mat{
    double m[MAXTAM][MAXTAM];
    int tamx, tamy;
    int id;
} mat_tipo;

// Limite superior da inicializacao aleatoria
#define INITRANDOMRANGE 10
// Macro que realiza swap sem variavel auxiliar */
#define ELEMSWAP(x,y) (x+=y,y=x-y,x-=y)

/**
 * @brief Cria matriz com dimensoes tx X ty
 * 
 * @param mat Ponteiro para a matriz
 * @param tx Numero de linhas
 * @param ty Numero de colunas
 * @param id Identificador da matriz
 */
void criaMatriz(mat_tipo * mat, int tx, int ty, int id);

/**
 * @brief Inicializa mat com valores nulos
 * 
 * @param mat Ponteiro para a matriz
 */
void inicializaMatrizNula(mat_tipo * mat);

/**
 * @brief Inicializa mat com valores aleatorios
 * 
 * @param mat Ponteiro para a matriz
 */
void inicializaMatrizAleatoria(mat_tipo * mat);

/**
 * @brief Acessa mat para fins de registro de acesso
 * 
 * @param mat Ponteiro para a matriz
 * @return double Valor acessado
 */
double acessaMatriz(mat_tipo * mat);

/**
 * @brief Imprime a matriz com a identificacao de linhas e colunas
 * 
 * @param mat Ponteiro para a matriz
 */
void imprimeMatriz(mat_tipo * mat);

/**
 * @brief Salva a matriz em arquivo
 * 
 * @param mat Ponteiro para a matriz
 * @param out Ponteiro para o arquivo de saida
 */
void salvaMatriz(mat_tipo * mat, FILE * out);

/**
 * @brief Atribui o valor v ao elemento (x,y) de mat
 * 
 * @param mat Ponteiro para a matriz
 * @param x Linha do elemento
 * @param y Coluna do elemento
 * @param v Valor a ser atribuido
 */
void escreveElemento(mat_tipo * mat, int x, int y, double v);

/**
 * @brief Retorna o elemento (x,y) de mat
 * 
 * @param mat Ponteiro para a matriz
 * @param x Linha do elemento
 * @param y Coluna do elemento
 * @return double Valor do elemento
 */
double leElemento (mat_tipo * mat, int x, int y);

/**
 * @brief Faz uma copia de src em dst
 * 
 * @param src Ponteiro para a matriz fonte
 * @param dst Ponteiro para a matriz destino
 * @param dst_id Identificador da matriz destino
 */
void copiaMatriz(mat_tipo *src, mat_tipo * dst, int dst_id);

/**
 * @brief Soma as matrizes a e b e armazena o resultado em c
 * 
 * @param a Ponteiro para a matriz a
 * @param b Ponteiro para a matriz b
 * @param c Ponteiro para a matriz resultado
 */
void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);

/**
 * @brief Multiplica as matrizes a e b e armazena o resultado em c
 * 
 * @param a Ponteiro para a matriz a
 * @param b Ponteiro para a matriz b
 * @param c Ponteiro para a matriz resultado
 */
void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);

/**
 * @brief Transpoe a matriz a
 * 
 * @param a Ponteiro para a matriz
 */
void transpoeMatriz(mat_tipo *a);

/**
 * @brief Destroi a matriz a, que se torna inacessível
 * 
 * @param a Ponteiro para a matriz
 */
void destroiMatriz(mat_tipo *a);


#endif // MAT_H