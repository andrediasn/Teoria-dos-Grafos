#include "Floyd.h"
#include "Vertices.h"
#include "Grafo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
#include <limits.h>

Floyd::Floyd(){}
Floyd::~Floyd(){}

list<int> Floyd::criaFloyd(Grafo* grafo, int noI, int noAlvo){
    Vertices* ver =  grafo->procurarNo(noAlvo);
    if(ver->getGrauEntrada() == 0){ // Se o alvo n tem entrada
        cout << endl << "Nao existe caminho entre o noh " << noI << " e o noh " << noAlvo << endl;
        return caminho; 
    }

    int n = grafo->getOrdem();
    int F[n][n]; // Matriz grafo
    int **P;
    P = new int *[n];
    for(int i = 0; i < n; i++)
        P[i] = new int[n];
    //Inicializando matriz com infinito, e iguais com 0
    for (int i=0; i<n;i++){
        for (int j=0; j<n;j++){
            P[i][j] = -1;
            if(i==j)
                F[i][j] = 0;
            else 
                F[i][j] = INT_MAX/2;
        }
    }
    
    // Criando matriz inicial do grafo
    for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){
        Vertices* auxI = *i;
        for(auto j = auxI->ListAdj.begin(); j != auxI->ListAdj.end(); j++){
            Vertices* auxJ = grafo->procurarNo(*j);
            Arestas* arestaAux = grafo->existeAresta(auxI->getId(), auxJ->getId());
            F[auxI->getId()][auxJ->getId()] = arestaAux->getPeso();
        }
    }

    // Algoritimo de Floyd
    int ant, dep, soma, teste;
    for(int k=0;k<n;k++){
        Vertices* vK = grafo->procurarNo(k);
        for(auto i=vK->ListAnt.begin();i!=vK->ListAnt.end();i++){
            ant = *i;
            for(auto j = grafo->nosGrafo.begin(); j != grafo->nosGrafo.end(); j++){
                Vertices *aux = *j;
                dep = aux->getId();
                soma = F[ant][k] + F[k][dep];
                teste = F[ant][dep];
                if(soma < teste){
                    F[ant][dep] = soma;
                    P[ant][dep] = k;
                }
            }
        }  
    }

    if(F[noI][noAlvo] < INT_MAX/2){ // se houve custo menor que o valor iniciado
        criaCaminho(noI, noAlvo, P);
        cout << "Custo minimo: " << F[noI][noAlvo] << endl;
    }
    else{
        cout << endl << "Nao existe caminho entre o noh " << noI << " e o noh " << noAlvo << endl;
    }
    return caminho;
}

void Floyd::criaCaminho(int noI, int noF, int **P) {
    int aux = P[noI][noF];
    cout <<aux << endl;
    if(P[noI][noF] > -1){
        caminho.push_back(noI);
        criaCaminho(aux, noF, P);
    }
    else if(aux == -1)
        caminho.push_back(noF);
}

