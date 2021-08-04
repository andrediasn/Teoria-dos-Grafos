#ifndef GRAFOS2_DIJKSTRA_H
#define GRAFOS2_DIJKSTRA_H
#include "Grafo.h"
#include "Vertices.h"
#include <vector>

class Dijkstra {
public:
    int dijkstra(Grafo *grafo, int noI, int noAlvo);
    
private:
    void atualizaDist(Grafo *grafo, int *dist, int *noP, Vertices* no1, Vertices* no2);
    bool verOpen(Grafo *grafo);
    Vertices* menorDist(Grafo *grafo, int *dist);
};

#endif //GRAFOS2_DIJKSTRA_H*/