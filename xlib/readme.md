# Bibliotecas de estruturas de Dados

Esta é uma pasta para compilar todas as estruturas de dados utilizadas em scripts da disciplina de DCC 205.

Para todas as implementações deve haver um construtor e um destrutor.

## Lista

Deve possuir os seguintes métodos:

- GetTamanho
- Vazia
- GetItem
- SetItem
- InsereInicio
- InsereFinal
- InserePosicao
- RemoveInicio
- RemoveFinal
- RemovePosicao
- Pesquisa
- Imprime
- Limpa

## Pilha

Deve possuir os seguintes métodos:

- GetTamanho
- Vazia
- Empilha
- Desempilha
- Limpa

## Fila

Deve possuir os seguintes métodos:

- GetTamanho
- Vazia
- Enfileira
- Desenfileira
- Limpa

## Árvore

Possui os seguinte métodos

- Insere: Chama o método insere recursivo
- Caminha
- Limpa

E os seguintes métodos privados:

- InsereRecursivo
- ApagaRecursivo
- PorNivel
- PreOrdem
- InOrdem
- PosOrdem

O tipo de nó deve possuir o item armazenado e dois ponteiros, para o filho da esquerda (esq) e outro para o filho da direita (dir)

Utilizar friend class e, na inicialização, inicializar com item = -1 e ponteiros igual à NULL.

```hpp

class TipoNo
{
    public:
        TipoNo();
    private:
        TipoItem item;
        TipoNo *esq;
        TipoNo *dir;
    friend class ArvoreBinaria;
}

class ArvoreBinaria
{
    public:
        ArvoreBinaria();
        ~ArvoreBinaria();
        void Insere(TipoItem item);
        void Caminha(int tipo);
        void Limpa();
    private:
        void InsereRecursivo(TipoNo* &p, TipoItem item);
        void ApagaRecursivo(TipoNo* p);
        void PorNivel();
        void PreOrdem(TipoNo* p);
        void InOrdem(TipoNo* p);
        void PosOrdem(TipoNo* p);
        TipoNo *raiz;
};

```

## Grafo

### Heap, Heapsort


## Matrizes Esparsas

[comment]: <> (TODO)


