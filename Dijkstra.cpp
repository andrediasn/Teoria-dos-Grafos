#include "Dijkstra.h"
#include "Grafo.h"
#include "Vertices.h"
#include <vector>
#include <iostream>
#include <limits.h>

using namespace std;



int Dijkstra::dijkstra(Grafo *grafo, int noI, int noAlvo){
    
    int dist[grafo->getOrdem()]; // Vetor de distancia
    int noP[grafo->getOrdem()];  // Armazena predecessor

    for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){
        Vertices* aux = *i;
        aux->setVisitado(true); // Aberto/Fechado
        int id = aux->getId();
        dist[id] = INT_MAX/2;
        noP[id] = -1; // sem predecessor
    }
    dist[noI] = 0;
    
    while (verOpen(grafo)) {
        Vertices* no1 = menorDist(grafo, dist);
        no1->setVisitado(false);
   
       for (auto i = no1->ListAdj.begin(); i != no1->ListAdj.end(); i++) {
            Vertices* no2 = grafo->procurarNo(*i);
            atualizaDist(grafo, dist, noP, no1, no2);
        }
    }
    return(dist[noAlvo]);
}

void Dijkstra::atualizaDist(Grafo *grafo, int *dist, int *noP, Vertices* no1, Vertices* no2) {
    for (auto i = no1->ListAdj.begin(); i != no1->ListAdj.end(); i++) {  
        Vertices* aux = grafo->procurarNo(*i);
        if(aux == no2){
            if (dist[no2->getId()] > (dist[no1->getId()] + aresta->peso)) { // dist de no2 maior que a soma da dist de no1 mais o peso da aresta
                dist[no2->getId()] = dist[no1->getId()] + aresta->peso; // atualiza dist de no2
                noP[no2->getId()] = no1->getId(); // indica o predecessor
            }
            break;
        }
    }
}

bool Dijkstra::verOpen(Grafo *grafo) {
    for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){
        Vertices* aux = *i;
        if(aux->getVisitado())
            return true;
    }
    return false;
}

Vertices* Dijkstra::menorDist(Grafo *grafo, int *dist) {
    Vertices* aux;
    for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){
        aux = *i;
        if(aux->getVisitado())  // busca primeiro vertice aberto
            break;   // interrompe for ao achar
    }
    if(aux == grafo->nosGrafo.end())   // se após busca não encontrou vertice aberto
        return(aux); 

    Vertices* menor = aux; // se achou, assumimos i como sendo a menor distancia
    for (auto i = menor++; i != grafo->nosGrafo.end(); i++) {// continua a busca por outro vertice aberto
        aux = *i;
        if(aux->getVisitado() && (dist[menor->getId()]>dist[aux->getId()]))   // se encontra outro aberto e a dist do atual menor for maior que o novo vertice aberto
            menor = aux; // atualiza menor
    }
    return(menor); // retorna o vertice com menor distancia
}

