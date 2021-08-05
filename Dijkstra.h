#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
#include "Grafo.h"
#include "Vertices.h"
#include <list>


class Dijkstra {
public:
    Dijkstra();
    ~Dijkstra();
    list<int> caminhoMinimo(Grafo *grafo, int noI, int noAlvo);
    
private:
    list<int> caminho;
    Vertices* menorDist(Grafo *grafo, int dist[]);
    void criaCaminho(int no, int ant[], int noI);
};
  
#endif //DIJKSTRA_H_INCLUDED