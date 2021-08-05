#include "Dijkstra.h"
#include "Grafo.h"
#include "Vertices.h"
#include <iostream>
#include <limits.h>
#include <list>

using namespace std;
Dijkstra::Dijkstra(){}

Dijkstra::~Dijkstra(){}

void Dijkstra::criaCaminho(int noA, int ant[], int noI){
    cout << " No A: " << noA << " Ant: "<< ant[noA] << " Inicial: " << noI <<endl;
    if(noA != noI){
        caminho.push_front(noA);
        int aux = ant[noA];
        criaCaminho(aux, ant, noI);
    }
    else
        caminho.push_front(noI);
}


list<int> Dijkstra::caminhoMinimo(Grafo *grafo, int noI, int noAlvo){
    grafo->arrumaVisitado();

    Vertices* ver =  grafo->procurarNo(noAlvo);
    if(ver->getGrauEntrada() == 0){
        cout << endl << "Nao existe caminho do noh " << noI << " ate o noh " << noAlvo << endl;
        return caminho; 
    }

    int dist[grafo->getOrdem()]; // Vetor de distancia
    int ant[grafo->getOrdem()];  // Armazena predecessor

    for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){
        Vertices* aux = *i;
        int id = aux->getId();
        dist[id] = INT_MAX/2;
        ant[id] = -1; // sem predecessor
    }
    dist[noI] = 0;
    
    for(int j = 0; j < (grafo->getOrdem())-1; j++) {
        Vertices* no1 = menorDist(grafo, dist);
        no1->setVisitado(true);
        //cout << "Fechei: " << no1->getId() << endl;
        for (auto i = no1->ListAdj.begin(); i != no1->ListAdj.end(); i++) {
            Arestas* arestaAux = grafo->existeAresta(no1->getId(), *i);
            if (dist[*i] > (dist[no1->getId()] + arestaAux->getPeso())) { // dist de no2 maior que a soma da dist de no1 mais o peso da aresta
                dist[*i] = dist[no1->getId()] + arestaAux->getPeso(); // atualiza dist de no2
                ant[*i] = no1->getId(); // indica o predecessor
            }
        }
    }
    int d = dist[noAlvo];
    cout << "Distancia: " << d << endl;


    criaCaminho(noAlvo, ant, noI);
    grafo->arrumaVisitado();
    return caminho;
}

Vertices* Dijkstra::menorDist(Grafo *grafo, int dist[]) {
    Vertices *aux, *id;
    int menor = INT_MAX/2;
    for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){
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

