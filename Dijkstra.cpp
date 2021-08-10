#include "Dijkstra.h"
#include "Grafo.h"
#include "Vertices.h"
#include <iostream>
#include <limits.h>
#include <list>

using namespace std;
Dijkstra::Dijkstra(){}
Dijkstra::~Dijkstra(){}

list<int> Dijkstra::caminhoMinimo(Grafo *grafo, int noI, int noAlvo){
    Vertices* ver =  grafo->procurarNo(noAlvo);
    if(ver->getGrauEntrada() == 0){ // Se o alvo n tem entrada
        cout << endl << "Nao existe caminho entre o vertice " << noI << " e o vertice " << noAlvo << endl;
        return caminho; 
    }

    int *dist = new int[grafo->getOrdem()]; // Vetor de distancia
    int *ant = new int[grafo->getOrdem()];  // Armazena predecessor

    for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){
        Vertices* aux = *i;
        abertos.push_back(aux); // inclui todos nós no conjunto aberto
        int id = aux->getId();
        dist[id] = INT_MAX/2; // inicializa distancia com infinito
        ant[id] = -1; // sem predecessor
    }
    dist[noI] = 0; // no inicial, distancia 0
    
    for(int j = 0; j < (grafo->getOrdem())-1; j++) {
        Vertices* no1 = menorDist(dist);  // busca noh aberto com menor distancia salva
        abertos.remove(no1); // remove nó do conjunto de nós abertos
        for (auto i = no1->ListAdj.begin(); i != no1->ListAdj.end(); i++) { // Percorre lista de adjacencia
            Arestas* arestaAux = grafo->existeAresta(no1->getId(), *i); // busca aresta
            if (dist[*i] > (dist[no1->getId()] + arestaAux->getPeso())) { // dist de no2 maior que a soma da dist de no1 mais o peso da aresta
                dist[*i] = dist[no1->getId()] + arestaAux->getPeso(); // atualiza dist de no2
                ant[*i] = no1->getId(); // indica o predecessor
            }
        }
    }

    if(dist[noAlvo]<INT_MAX/2){ // se houve custo menor que o valor iniciado
        criaCaminho(noAlvo, ant, noI); // imprime menor caminho encontrado
        cout << endl << "Custo do caminho minimo: " << dist[noAlvo] << endl; 
    }
    else
        cout << endl << "Nao existe caminho entre o vertice " << noI << " e o vertice " << noAlvo << endl;
    delete dist;
    delete ant;
    return caminho;
}

Vertices* Dijkstra::menorDist(int dist[]) {
    Vertices *id;
    int menor = INT_MAX/2; 
    for(auto i = abertos.begin(); i != abertos.end(); i++){
        Vertices *aux = *i;
            if(dist[aux->getId()] < menor){
                menor = dist[aux->getId()];
                id = aux;
        }
    }
    return id; // retorna o vertice com menor distancia
}

void Dijkstra::criaCaminho(int noA, int ant[], int noI){
    //cout << " No A: " << noA << " Ant: "<< ant[noA] << " Inicial: " << noI <<endl;
    if(noA != noI){
        caminho.push_front(noA);
        int aux = ant[noA];
        criaCaminho(aux, ant, noI);
    }
    else
        caminho.push_front(noI);
}