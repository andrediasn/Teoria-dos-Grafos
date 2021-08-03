/*#ifndef GRAFOS2_DIJKSTRA_H
#define GRAFOS2_DIJKSTRA_H
#include "Grafo.h"
#include <vector>

class Dijkstra {
public:
    int *dijkstra(Grafo *grafo, int noI);
    
private:
    void atualizaDist(Grafo *grafo, int *dist, int *noP, int no1, int no2);
    bool verOpen(Grafo *grafo, bool *open);
    int menorDist(Grafo *grafo, bool *open, int *dist);
};

#endif //GRAFOS2_DIJKSTRA_H*/