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
    if(ver->getGrauEntrada() == 0){ // Se o vertice alvo n tem grau de entrada n tem caminho ate ele
        cout << endl << "Nao existe caminho entre o vertice " << noI << " e o vertice " << noAlvo << endl;
        return caminho; 
    }

    int *dist = new int[grafo->getOrdem()]; // Vetor de distancia
    int *ant = new int[grafo->getOrdem()];  // Armazena predecessor

    for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){ // Percorre todos vertices do grafo
        Vertices* aux = *i;
        abertos.push_back(aux); // inclui todos nós no conjunto aberto
        int id = aux->getId();
        dist[id] = INT_MAX/2; // inicializa custo do vertice com infinito
        ant[id] = -1; // inicializa predecessor do vertice para sem predecessor
    }
    dist[noI] = 0; // vertice inicial, custo 0
    
    for(int j = 0; j < (grafo->getOrdem())-1; j++) {
        Vertices* no1 = menorDist(dist);  // busca vertice aberto com menor custo
        abertos.remove(no1); // remove vertice do conjunto de nvertices abertos
        for (auto i = no1->ListAdj.begin(); i != no1->ListAdj.end(); i++) { // Percorre lista de adjacencia do vertice
            Arestas* arestaAux = grafo->existeAresta(no1->getId(), *i); // Busca aresta
            if (dist[*i] > (dist[no1->getId()] + arestaAux->getPeso())) { // custo de no2 maior que a soma da dist de no1 mais o peso da aresta
                dist[*i] = dist[no1->getId()] + arestaAux->getPeso(); // atualiza custo de no2
                ant[*i] = no1->getId(); // indica o predecessor
            }
        }
    }

    if(dist[noAlvo]<INT_MAX/2){ // se houve caminho encontrado
        criaCaminho(noAlvo, ant, noI); // cria lista do menor caminho encontrado
        cout << endl << "Custo do caminho minimo: " << dist[noAlvo] << endl;
    }
    else // nao foi encontrado caminho entre os vertices
        cout << endl << "Nao existe caminho entre o vertice " << noI << " e o vertice " << noAlvo << endl;
    delete dist; // free memory
    delete ant; // free memory
    return caminho;
}

Vertices* Dijkstra::menorDist(int dist[]) { // busca vertice aberto com menor custo salvo
    Vertices *id;
    int menor = INT_MAX/2; // menor assume valor inicializado
    for(auto i = abertos.begin(); i != abertos.end(); i++){ // percorre conjunto de vertices abertos
        Vertices *aux = *i;
            if(dist[aux->getId()] < menor){ // se custo do vertice for menor que o selecionado anteriormente
                menor = dist[aux->getId()];
                id = aux; // menor recebe vertice
        }
    }
    return id; // retorna o vertice com menor custo
}

void Dijkstra::criaCaminho(int noA, int ant[], int noI){ // Busca nos predecessores para fazer o caminho
    if(noA != noI){ // vertice selecionado diferente do vertice inicial
        caminho.push_front(noA); // puxa vertice para o comeco
        int aux = ant[noA];
        criaCaminho(aux, ant, noI); // passa anterior do vertice recursivamente
    }
    else // vertice selecionado é o vertice inicial
        caminho.push_front(noI); // puxa vertice inicial para comeco do caminho
}