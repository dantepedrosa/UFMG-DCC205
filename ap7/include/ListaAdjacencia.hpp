#pragma once

#include "ListaEncadeada.hpp"

/**
 * @class ListaAdjacencia
 * @brief Classe que representa um grafo utilizando uma lista de adjacência.
 * 
 * A classe ListaAdjacencia fornece métodos para adicionar vértices e arestas,
 * obter vizinhos de um vértice, grau de um vértice, número de vértices e número de arestas.
 */
class ListaAdjacencia {
public:
    /**
     * @brief Construtor padrão da classe ListaAdjacencia.
     */
    ListaAdjacencia();

    /**
     * @brief Destrutor da classe ListaAdjacencia.
     */
    ~ListaAdjacencia();

    /**
     * @brief Adiciona um novo vértice ao grafo.
     */
    void adicionarVertice();

    /**
     * @brief Adiciona uma aresta entre os vértices v e w.
     * 
     * @param v O vértice de origem.
     * @param w O vértice de destino.
     */
    void adicionarAresta(int v, int w);

    /**
     * @brief Obtém a lista de vizinhos de um vértice.
     * 
     * @param v O vértice cujo vizinhos serão obtidos.
     * @return ListaEncadeada<int>& A lista de vizinhos do vértice.
     */
    ListaEncadeada<int>& obterVizinhos(int v);

    /**
     * @brief Obtém o grau de um vértice.
     * 
     * @param v O vértice cujo grau será obtido.
     * @return int O grau do vértice.
     */
    int obterGrau(int v);

    /**
     * @brief Obtém o número de vértices no grafo.
     * 
     * @return int O número de vértices.
     */
    int obterNumVertices();

    /**
     * @brief Obtém o número de arestas no grafo.
     * 
     * @return int O número de arestas.
     */
    int obterNumArestas();

private:
    ListaEncadeada<ListaEncadeada<int>> adjList;    // Lista de adjacência que armazena os vizinhos de cada vértice.
    int numVertices;                                // Número de vértices no grafo.
    int numArestas;     	                        // Número de arestas no grafo.
};