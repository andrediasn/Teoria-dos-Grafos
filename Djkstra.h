#ifndef DJKSTRA_H_INCLUDED
#define DJKSTRA_H_INCLUDED
#include "Grafo.h"
#include "Vertices.h"
#include <list>

class Djkstra {
private:
    list<int> caminho;
    list<Vertices*> abertos;
    Vertices* menorDist(int dist[]);
    void criaCaminho(int no, int ant[], int noI);
    
public:
    Djkstra();
    ~Djkstra();
    list<int> caminhoMinimo(Grafo *grafo, int noI, int noAlvo);
    
};
  
#endif //DJKSTRA_H_INCLUDED