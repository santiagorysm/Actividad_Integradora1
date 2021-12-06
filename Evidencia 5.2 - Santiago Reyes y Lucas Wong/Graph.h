//Escrito por Santiago Reyes Moran - A01639030 y Lucas Wong Mang - A01639032
//Con referencia al profesor Eduardo Arturo Rodríguez Tello
//04/12/2021

#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <unordered_map>

class Graph
{
private:
    int numNodes;
    int numEdges;
    int representation; // 1 Adjacency list; 2 Adjacency matrix
    // Matriz de adyacencia
    //int **adjMatrix;
    // Lista de adyacencia (vector de vectores)
    //std::vector<std::vector<int>> adjList;
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> listaAdjacencia;
    std::vector<bool> visited;

public:
    Graph();
    Graph(int nodes);
    ~Graph();
    //void printGraph();
    //void DFS(int v);
    //void BFS(int v);
    //void copyGraph(int, Graph &res);
    void addToList(std::string origen, std::string destino);
    void addToGraph(std::string origen);
    int getListLength(std::string origen);

    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> getListaAdjacencia();
};

Graph::Graph()
{
    numEdges = 0;
    numNodes = 0;
    representation = 1;
}

Graph::Graph(int nodes)
{
    representation = 1;
    visited.resize(nodes + 1);
}

Graph::~Graph()
{

    visited.clear();
}

void Graph::addToList(std::string origen, std::string destino)
{
    //int 0 si el origen esta accesando a otra ip
    //int 1 si el origen esta siendo accesada por otra ip
    std::pair<std::string, int> par1(destino, 0);
    std::pair<std::string, int> par2(origen, 1);

    listaAdjacencia[origen].push_back(par1);

    if (!listaAdjacencia.count(destino))
    {
        addToGraph(destino);
    }
    listaAdjacencia[destino].push_back(par2);
    numEdges++;
}

void Graph::addToGraph(std::string origen)
{
    listaAdjacencia.insert({{origen, {}}});
    numNodes++;
    //visited.resize(numNodes + 1);
}

int Graph::getListLength(std::string origen)
{
    return listaAdjacencia[origen].size();
}

std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> Graph::getListaAdjacencia()
{
    return listaAdjacencia;
}

#endif // __GRAPH_H_