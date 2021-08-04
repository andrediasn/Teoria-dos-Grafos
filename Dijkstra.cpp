#include "Dijkstra.h"
#include "Grafo.h"
#include "Vertices.h"
#include <iostream>
#include <limits.h>

using namespace std;

int Dijkstra::dijkstra(Grafo grafo, int noI, int noAlvo){
    
    int dist[grafo.getOrdem()]; // Vetor de distancia
    int ant[grafo.getOrdem()];  // Armazena predecessor

    for(auto i = grafo.nosGrafo.begin(); i != grafo.nosGrafo.end(); i++){
        Vertices* aux = *i;
        int id = aux->getId();
        dist[id] = INT_MAX/2;
        ant[id] = -1; // sem predecessor
    }
    dist[noI] = 0;
    
    while (verOpen(grafo)) {
        Vertices* no1 = menorDist(grafo, dist);
        no1->setVisitado(true);
   
        for (auto i = no1->ListAdj.begin(); i != no1->ListAdj.end(); i++) {
            Arestas* arestaAux = grafo.existeAresta(no1->getId(), *i);
            if (dist[*i] > (dist[no1->getId()] + arestaAux->getPeso())) { // dist de no2 maior que a soma da dist de no1 mais o peso da aresta
                dist[*i] = dist[no1->getId()] + arestaAux->getPeso(); // atualiza dist de no2
                ant[*i] = no1->getId(); // indica o predecessor
            }
        }
    }
    grafo.arrumaVisitado();
    return dist[noAlvo];
}

bool Dijkstra::verOpen(Grafo grafo) {
    for(auto i = grafo.nosGrafo.begin(); i != grafo.nosGrafo.end(); i++){
        Vertices* aux = *i;
        if(aux->getVisitado())
            return true;
    }
    return false;
}

Vertices* Dijkstra::menorDist(Grafo grafo, int dist[]) {
    Vertices *aux, *id;
    int menor = INT_MAX/2;
    for(auto i = grafo.nosGrafo.begin(); i != grafo.nosGrafo.end(); i++){
        aux = *i;
        if(!(aux->getVisitado())){  // busca primeiro vertice aberto
            if(dist[aux->getId()] < menor){
                menor = dist[aux->getId()];
                id = aux;
            } 
        }
    }
    return id; // retorna o vertice com menor distancia
}

