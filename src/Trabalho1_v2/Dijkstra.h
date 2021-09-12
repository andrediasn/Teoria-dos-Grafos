#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
#include "Grafo.h"
#include "Vertices.h"
#include <list>

class Dijkstra {
private:
    list<string> caminho;
    list<Vertices*> abertos;
    Vertices* menorDist(int dist[]); // busca vertice aberto com menor custo salvo
    void criaCaminho(Grafo* grafo, int no, int ant[], int noI); // Busca nos predecessores para fazer o caminho
    
public:
    Dijkstra();
    ~Dijkstra();
    list<string> caminhoMinimo(Grafo *grafo, int noI, int noAlvo); //base do algoritimo
    
};
  
#endif //DIJKSTRA_H_INCLUDED