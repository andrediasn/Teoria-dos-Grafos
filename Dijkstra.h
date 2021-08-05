#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
#include "Grafo.h"
#include "Vertices.h"
#include <list>

class Dijkstra {
private:
    list<int> caminho;
    Vertices* menorDist(Grafo *grafo, int dist[]);
    void criaCaminho(int no, int ant[], int noI);
    
public:
    Dijkstra();
    ~Dijkstra();
    list<int> caminhoMinimo(Grafo *grafo, int noI, int noAlvo);
    
};
  
#endif //DIJKSTRA_H_INCLUDED