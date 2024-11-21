/**
 * @file mat.h
 * @brief Definitions for the MAT Abstract Data Type (ADT)
 * 
 * This file contains the definitions and function prototypes for the MAT ADT.
 * 
 * @author Wagner Meira Jr. (meira@dcc.ufmg.br)
 * @date 2021-10-18
 * @date 2021-10-21 - directory structure
 */

#ifndef MATH
#define MATH

#ifndef MAXTAM 
#define MAXTAM 5
#endif

/**
 * @struct mat
 * @brief Structure representing a matrix.
 * 
 * This structure represents a matrix with a maximum size of MAXTAM x MAXTAM.
 * 
 * @var mat::m
 * Matrix elements stored in a 2D array.
 * @var mat::tamx
 * Number of rows in the matrix.
 * @var mat::tamy
 * Number of columns in the matrix.
 * @var mat::id
 * Identifier for the matrix.
 */
typedef struct mat {
	double m[MAXTAM][MAXTAM];
	int tamx, tamy;
	int id;
} mat_tipo;

/**
 * @brief Creates a matrix with specified dimensions and ID.
 * 
 * @param mat Pointer to the matrix structure to be initialized.
 * @param tx Number of rows.
 * @param ty Number of columns.
 * @param id Identifier for the matrix.
 */
void criaMatriz(mat_tipo * mat, int tx, int ty, int id);

/**
 * @brief Initializes the matrix with all elements set to zero.
 * 
 * @param mat Pointer to the matrix structure to be initialized.
 */
void inicializaMatrizNula(mat_tipo * mat);

/**
 * @brief Initializes the matrix with random elements.
 * 
 * @param mat Pointer to the matrix structure to be initialized.
 */
void inicializaMatrizAleatoria(mat_tipo * mat);

/**
 * @brief Accesses the matrix elements.
 * 
 * @param mat Pointer to the matrix structure.
 * @return A double value representing the accessed element.
 */
double acessaMatriz(mat_tipo * mat);

/**
 * @brief Prints the matrix elements.
 * 
 * @param mat Pointer to the matrix structure to be printed.
 */
void imprimeMatriz(mat_tipo * mat);

/**
 * @brief Saves the matrix to a file.
 * 
 * @param mat Pointer to the matrix structure to be saved.
 * @param file Pointer to the file where the matrix will be saved.
 */
void salvaMatriz(mat_tipo * mat, FILE *file);

/**
 * @brief Writes a value to a specific element in the matrix.
 * 
 * @param mat Pointer to the matrix structure.
 * @param x Row index.
 * @param y Column index.
 * @param v Value to be written.
 */
void escreveElemento(mat_tipo * mat, int x, int y, double v);

/**
 * @brief Reads a value from a specific element in the matrix.
 * 
 * @param mat Pointer to the matrix structure.
 * @param x Row index.
 * @param y Column index.
 * @return A double value representing the read element.
 */
double leElemento(mat_tipo * mat, int x, int y);

/**
 * @brief Copies the contents of one matrix to another.
 * 
 * @param src Pointer to the source matrix structure.
 * @param dst Pointer to the destination matrix structure.
 * @param dst_id Identifier for the destination matrix.
 */
void copiaMatriz(mat_tipo * src, mat_tipo * dst, int dst_id);

/**
 * @brief Adds two matrices and stores the result in a third matrix.
 * 
 * @param a Pointer to the first matrix structure.
 * @param b Pointer to the second matrix structure.
 * @param c Pointer to the result matrix structure.
 */
void somaMatrizes(mat_tipo * a, mat_tipo * b, mat_tipo * c);

/**
 * @brief Multiplies two matrices and stores the result in a third matrix.
 * 
 * @param a Pointer to the first matrix structure.
 * @param b Pointer to the second matrix structure.
 * @param c Pointer to the result matrix structure.
 */
void multiplicaMatrizes(mat_tipo * a, mat_tipo * b, mat_tipo * c);

/**
 * @brief Transposes the matrix.
 * 
 * @param a Pointer to the matrix structure to be transposed.
 */
void transpoeMatriz(mat_tipo *a);

/**
 * @brief Destroys the matrix and frees any allocated resources.
 * 
 * @param a Pointer to the matrix structure to be destroyed.
 */
void destroiMatriz(mat_tipo *a);

#endif