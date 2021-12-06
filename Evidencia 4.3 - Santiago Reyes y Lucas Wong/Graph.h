#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <unordered_map>
#include "registro.h"

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
    std::unordered_map<std::string, std::vector<Registro>> listaAdjacencia;
    std::vector<bool> visited;

    void loadGraphList(std::istream &input);
    void loadGraphMatrix(std::istream &input);
    void split(std::string line, std::vector<int> &res);
    void printAdjList();
    void printAdjMatrix();
    void explore(int v);

public:
    Graph();
    Graph(int nodes);
    ~Graph();
    //void printGraph();
    //void DFS(int v);
    //void BFS(int v);
    //void copyGraph(int, Graph &res);
    void addToList(std::string origen, Registro destino);
    void addToGraph(std::string origen);
    int getListLength(std::string origen);

    //void addToList();
    std::unordered_map<std::string, std::vector<Registro>> getListaAdjacencia();
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

void Graph::addToList(std::string origen, Registro destino)
{
        listaAdjacencia[origen].push_back(destino);
        numEdges++;
    
}

void Graph::addToGraph(std::string origen)
{
        listaAdjacencia.insert({{origen, {}}});
        numNodes++;
        //visited.resize(numNodes + 1);
    
}

int Graph::getListLength(std::string origen){
  return listaAdjacencia[origen].size();
}

std::unordered_map<std::string, std::vector<Registro>> Graph::getListaAdjacencia()
{
    return listaAdjacencia;
}




#endif // __GRAPH_H_