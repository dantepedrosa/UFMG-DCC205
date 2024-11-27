#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <linux/time.h>

/**
 * @brief Calcula o n-ésimo número de Fibonacci de forma recursiva.
 * 
 * @param n A posição do número de Fibonacci a ser calculado.
 * @return O n-ésimo número de Fibonacci.
 */
double rec_fibonacci(int n);

/**
 * @brief Calcula o n-ésimo número de Fibonacci de forma iterativa.
 * 
 * @param n A posição do número de Fibonacci a ser calculado.
 * @return O n-ésimo número de Fibonacci.
 */
double it_fibonacci(int n);

/**
 * @brief Calcula o fatorial de um número de forma recursiva.
 * 
 * @param n O número cujo fatorial será calculado.
 * @return O fatorial de n.
 */
double rec_factorial(int n);

/**
 * @brief Calcula o fatorial de um número de forma iterativa.
 * 
 * @param n O número cujo fatorial será calculado.
 * @return O fatorial de n.
 */
double it_factorial(int n);


/**
 * @brief Displays the usage instructions for the program.
 *
 * This function prints the correct usage of the program to the standard error stream.
 * It includes instructions for calculating factorial and Fibonacci numbers both
 * recursively and iteratively, as well as how to specify an input file.
 *
 * Usage:
 * - fat -r {numero/inicio} {fim} : Calculate factorial recursively.
 * - fat -i {numero/inicio} {fim} : Calculate factorial iteratively.
 * - fib -r {numero/inicio} {fim} : Calculate Fibonacci number recursively.
 * - fib -i {numero/inicio} {fim} : Calculate Fibonacci number iteratively.
 * - "./caminho/ArquivoDeEntrada.txt" : Specify the path to the input file.
 */
void uso();

double rec_fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return rec_fibonacci(n - 1) + rec_fibonacci(n - 2);
}

double it_fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    double a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

double rec_factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * rec_factorial(n - 1);
}

double it_factorial(int n) {
    double result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

void execute_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
/*
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char type;
        int n;
        if (sscanf(line, "%c %d", &type, &n) == 2) {
            if (type == 'r') {
                printf("Recursive Fibonacci of %d is %d\n", n, rec_fibonacci(n));
                printf("Recursive Factorial of %d is %d\n", n, rec_factorial(n));
            } else if (type == 'i') {
                printf("Iterative Fibonacci of %d is %d\n", n, it_fibonacci(n));
                printf("Iterative Factorial of %d is %d\n", n, it_factorial(n));
            }
        }
    }
    */
    fclose(file);
}

void uso(){
    fprintf(stderr, "Uso:\n");
    fprintf(stderr, "\tfat -r {numero/inicio} {fim}\n");
    fprintf(stderr, "\tfat -i {numero/inicio} {fim}\n");
    fprintf(stderr, "\tfib -r {numero/inicio} {fim}\n");
    fprintf(stderr, "\tfib -i {numero/inicio} {fim}\n");
    fprintf(stderr, "\t\"./caminho/ArquivoDeEntrada.txt\"\n");
}

int main(int argc, char *argv[]) {

    clock_t t;    

    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            uso();
            return 0;
        } else {
            execute_file(argv[1]);
            return 0;
        }
    } /*else if (argc == 3) {
        int n = atoi(argv[2]);
        if (strcmp(argv[1], "fib") == 0) {
            printf("Iterative Fibonacci of %d is %d\n", n, it_fibonacci(n));
        } else if (strcmp(argv[1], "fat") == 0) {
            printf("Iterative Factorial of %d is %d\n", n, it_factorial(n));
        } else {
            uso();
            return 1;
        }
    } else if (argc == 4) {
        int n = atoi(argv[3]);

        if (strcmp(argv[1], "fib") == 0 && strcmp(argv[2], "-r") == 0) {
            printf("Recursive Fibonacci of %d is %d\n", n, rec_fibonacci(n));
        } else if (strcmp(argv[1], "fib") == 0 && strcmp(argv[2], "-i") == 0) {
            printf("Iterative Fibonacci of %d is %d\n", n, it_fibonacci(n));
        } else if (strcmp(argv[1], "fat") == 0 && strcmp(argv[2], "-r") == 0) {
            printf("Recursive Factorial of %d is %d\n", n, rec_factorial(n));
        } else if (strcmp(argv[1], "fat") == 0 && strcmp(argv[2], "-i") == 0) {
            printf("Iterative Factorial of %d is %d\n", n, it_factorial(n));
        } else {
            uso();
            return 1;
        }
    } */else if (argc == 5) {
        int init = atoi(argv[3]);
        int fim = atoi(argv[4]);

        double result;

        struct timespec start_time, end_time;

        if (strcmp(argv[1], "fib") == 0 && strcmp(argv[2], "-r") == 0) {
            for (int i = init; i <= fim; i++) {
                clock_gettime(CLOCK_MONOTONIC, &start_time);

                result = rec_fibonacci(i);

                clock_gettime(CLOCK_MONOTONIC, &end_time);

                double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec);
                printf("%s %s of %d is %f elapsed time %f nanoseconds\n",argv[1], argv[2], i, result, time_taken);
            
            }
        } else if (strcmp(argv[1], "fib") == 0 && strcmp(argv[2], "-i") == 0) {
            
            for (int i = init; i <= fim; i++) {
                clock_gettime(CLOCK_MONOTONIC, &start_time);

                result = it_fibonacci(i);

                clock_gettime(CLOCK_MONOTONIC, &end_time);

                double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec);
                printf("%s %s of %d is %f elapsed time %f nanoseconds\n",argv[1], argv[2], i, result, time_taken);
            }

        } else if (strcmp(argv[1], "fat") == 0 && strcmp(argv[2], "-r") == 0) {
            
            for (int i = init; i <= fim; i++) {
                clock_gettime(CLOCK_MONOTONIC, &start_time);

                result = rec_factorial(i);

                clock_gettime(CLOCK_MONOTONIC, &end_time);

                double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec);
                printf("%s %s of %d is %f elapsed time %f nanoseconds\n",argv[1], argv[2], i, result, time_taken);
            
            }
        } else if (strcmp(argv[1], "fat") == 0 && strcmp(argv[2], "-i") == 0) {
            
            for (int i = init; i <= fim; i++) {
                
                clock_gettime(CLOCK_MONOTONIC, &start_time);

                result = it_factorial(i);

                clock_gettime(CLOCK_MONOTONIC, &end_time);

                double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec);
                printf("%s %s of %d is %f elapsed time %f nanoseconds\n",argv[1], argv[2], i, result, time_taken);
            }
        } else {
            uso();
            return 1;
        }
    } else {
        uso();
        return 1;
    }
    return 0;
}