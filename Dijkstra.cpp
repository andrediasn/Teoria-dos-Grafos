/*#include "Dijkstra.h"
#include "Grafo.h"
#include <vector>
#include <iostream>
#include <limits.h>

using namespace std;



int Dijkstra::dijkstra(Grafo *grafo, int noI){
    int *dist = (int *)malloc(grafo->ordem*sizeof(int)); // aloca espaço pra array de distancias

    int noP[grafo->ordem]; // aloca espaço para os predecessores
    
    for (int i=0; i<grafo->ordem; i++) { // inicializa todos nos com distancia = infinito
        dist[i] = INT_MAX/2; // Maior inteiro/2, pois maior inteiro +1 é negativo
        noP[i] = -1; // sem predecessor
    }
    dist[noI] = 0; // Distancia com ele mesmo

    for(auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
        Vertices* aux = *i;
        aux->setVisitado(false);
    }
    
    while (verOpen(grafo, open)) {
        int no1 = menorDist(grafo, open, dist);
        open[no1] = false;
   
        ADJACENCIA *ad = grafo->adj[no1].cab;
        while (ad) {
            atualizaDist(grafo, dist, noP, no1, ad->vertice);
            ad = ad->prox;
        }
    }
    return(dist);
}

void Dijkstra::atualizaDist(Grafo *grafo, int *dist, int *noP, int no1, int no2) {
    ADJACENCIA *ad = grafo->adj[no1].cab;

    while (ad && ad->vertice != no2)
        ad = ad->prox;
    if(ad){
        if (dist[no2] > dist[no1] + ad->peso) { // dist de no2 maior que a soma da dist de no1 mais o peso da aresta
            dist[no2] = dist[no1] + ad->peso; // atualiza dist de no2
            noP[no2] = no1; // indica o predecessor
        }
    }
}

bool Dijkstra::verOpen(Grafo *grafo) {
    for(int i=0; i < grafo->ordem; i++) {
        Vertices* aux = *i;
        if(aux->getVisitado())
            return true;
        else
            return false;
    }
}

int Dijkstra::menorDist(Grafo *grafo, bool *open, int *dist) {
    int i;
    for(i=0; i<grafo->ordem; i++)
        if(open[i])  // busca primeiro vertice aberto
            break;   // interrompe for ao achar
    if(i == grafo->ordem)   // se após busca não encontrou vertice aberto
        return(-1); 
    int menor = i; // se achou, assumimos i como sendo a menor distancia
    for (i=menor+1; i<grafo->ordem; i++) // continua a busca por outro vertice aberto
        if(open[i] && (dist[menor]>dist[i]))   // se encontra outro aberto e a dist do atual menor for maior que o novo vertice aberto
            menor = i; // atualiza menor
    return(menor); // retorna o vertice com menor distancia
}*/

