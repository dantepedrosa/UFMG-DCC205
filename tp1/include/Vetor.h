#ifndef VETOR_H
#define VETOR_H

struct Vetor {
    int *dados;
    int tamanho;

    Vetor(int tamanho);
    ~Vetor();

    int &operator[](int i);
    int size() const;
};

#endif // VETOR_H
