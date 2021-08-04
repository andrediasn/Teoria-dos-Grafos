#ifndef GRAFOS2_DIJKSTRA_H
#define GRAFOS2_DIJKSTRA_H
#include "Grafo.h"
#include "Vertices.h"


class Dijkstra {
public:
    int dijkstra(Grafo grafo, int noI, int noAlvo);
    
private:
    bool verOpen(Grafo grafo);
    Vertices* menorDist(Grafo grafo, int dist[]);
};
  
#endif //GRAFOS2_DIJKSTRA_H*/