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

list<int> Floyd::caminhoMinimo(Grafo* grafo, int noI, int noAlvo){
    Vertices* ver =  grafo->procurarNo(noAlvo);
    if(ver->getGrauEntrada() == 0){ // Se o alvo nao tem entrada
        cout << endl << "Nao existe caminho entre o vertice " << noI << " e o vertice " << noAlvo << endl;
        return caminho; 
    }

    int n = grafo->getOrdem();
    int **F; // Alocando Matriz de custos
    F = new int *[n];
    for(int i = 0; i < n; i++)
        F[i] = new int[n];
    int **P; // Alocando Matriz de antecessores
    P = new int *[n];
    for(int i = 0; i < n; i++)
        P[i] = new int[n];
    
    for (int i=0; i<n;i++){ //Inicializando matriz com infinito, e iguais com 0
        for (int j=0; j<n;j++){
            P[i][j] = -1; // Antecessor recebe -1
            if(i==j)
                F[i][j] = 0;
            else 
                F[i][j] = INT_MAX/2;
        }
    }
    
    for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){ // Criando matriz inicial do grafo
        Vertices* auxI = *i;
        for(auto j = auxI->ListAdj.begin(); j != auxI->ListAdj.end(); j++){ // Inicializando as arestas no grafo
            Vertices* auxJ = grafo->procurarNo(*j);
            Arestas* arestaAux = grafo->existeAresta(auxI->getId(), auxJ->getId());
            F[auxI->getId()][auxJ->getId()] = arestaAux->getPeso();
        }
    }

    // Algoritimo de Floyd
    int ant, dep, soma, teste;
    for(int k=0;k<n;k++){
        Vertices* vK = grafo->procurarNo(k);
        for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){
            Vertices *auxI = *i;
            ant = auxI->getId();
            for(auto j = grafo->nosGrafo.begin(); j != grafo->nosGrafo.end(); j++){
                Vertices *auxJ = *j;
                dep = auxJ->getId();
                if(ant != dep){
                    soma = F[ant][k] + F[k][dep];
                    teste = F[ant][dep];
                    if(soma < teste){
                        F[ant][dep] = soma;
                        P[ant][dep] = k;
                    }
                }
            }
        }  
    }

    if(F[noI][noAlvo] < INT_MAX/2){ // Se encontrou caminho
        criaCaminho(noI, noAlvo, P);
        cout << endl << "Custo do caminho minimo: " << F[noI][noAlvo] << endl;
    }
    else
        cout << endl << "Nao existe caminho entre o vertice " << noI << " e o vertice " << noAlvo << endl;
    
    delete F;
    delete P;
    return caminho;
}

void Floyd::criaCaminho(int noI, int noF, int **P) { //Busca caminho percorrendo predecessores
    int aux = P[noI][noF];
    if(P[noI][noF] > -1){ //Se existe antecessor
        caminho.push_front(noF); // Salva antecessor na lista
        criaCaminho(noI, aux, P); // Chama recursivamente antecessor do antecessor
    }
    else if(aux == -1){ // Não houver antecessor
        caminho.push_front(noF); // Inclui vertice final na lista
        caminho.push_front(noI); // Inclui ultimo antecessor
    }
}

void Floyd::matrizCSV(int n, int **P){
    ofstream mat("Dados/matriz.csv");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            mat << P[i][j] << ",";
        mat<<endl;
    }
    mat.close();
}

