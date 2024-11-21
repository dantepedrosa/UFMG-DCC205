/**
 * @file msgassert.h
 * @brief Assertion macros for error and warning messages.
 *
 * This header file provides macros for handling assertions with custom
 * error and warning messages. It includes macros for issuing warnings
 * and errors, printing the message to stderr, and optionally aborting
 * the program on errors.
 */

#ifndef MSGASSERTH
#define MSGASSERTH

#include <stdio.h>
#include <stdlib.h>

/**
 * @def avisoAssert(e, m)
 * @brief Issues a warning message if the expression is false.
 *
 * This macro checks the given expression @p e. If the expression is false,
 * it calls the internal function __avisoassert to print a warning message
 * to stderr.
 *
 * @param e The expression to evaluate.
 * @param m The warning message to print if the expression is false.
 */
#define avisoAssert(e,m) ((void) ((e)?0: __avisoassert (#e,__FILE__,__LINE__,m)))

/**
 * @def __avisoassert(e, file, line, m)
 * @brief Internal function to print a warning message.
 *
 * This function prints a warning message to stderr with the file name,
 * line number, expression, and custom message.
 *
 * @param e The expression that was evaluated.
 * @param file The name of the file where the warning occurred.
 * @param line The line number where the warning occurred.
 * @param m The custom warning message.
 */
#define __avisoassert(e,file,line,m) ((void) fprintf(stderr,"%s:%u: Aviso: '%s' - %s\n",file,line,e,m),0)

/**
 * @def erroAssert(e, m)
 * @brief Issues an error message and aborts the program if the expression is false.
 *
 * This macro checks the given expression @p e. If the expression is false,
 * it calls the internal function __erroassert to print an error message
 * to stderr and aborts the program.
 *
 * @param e The expression to evaluate.
 * @param m The error message to print if the expression is false.
 */
#define erroAssert(e,m) ((void) ((e)?0: __erroassert (#e,__FILE__,__LINE__,m)))

/**
 * @def __erroassert(e, file, line, m)
 * @brief Internal function to print an error message and abort the program.
 *
 * This function prints an error message to stderr with the file name,
 * line number, expression, and custom message, and then aborts the program.
 *
 * @param e The expression that was evaluated.
 * @param file The name of the file where the error occurred.
 * @param line The line number where the error occurred.
 * @param m The custom error message.
 */
#define __erroassert(e,file,line,m) ((void) fprintf(stderr,"%s:%u: Erro '%s' - %s\n",file,line,e,m), abort(),0)

#endif