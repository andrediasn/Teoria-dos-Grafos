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

void Floyd::caminhoMinimo(Grafo* grafo, int noI, int noAlvo){
    Vertices* ver =  grafo->procurarNo(noAlvo);
    if(ver->getGrauEntrada() == 0) // Se o alvo nao tem grau de entrada, nao ha caminho ate ele
        cout << endl << "Nao existe caminho entre o vertice " << noI << " e o vertice " << noAlvo << endl;

    int n = grafo->getOrdem();
    int **F; // Alocando Matriz de custos
    F = new int *[n];
    for(int i = 0; i < n; i++)
        F[i] = new int[n];
    
    for (int i=0; i<n;i++){ //Inicializando matriz com infinito, e i=j com 0
        for (int j=0; j<n;j++){
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
            F[auxI->getId()][auxJ->getId()] = arestaAux->getPeso(); // salva peso na matriz
        }
    }

    int ant, dep, soma, teste; // variaveis para auxiliar
    for(int k=0;k<n;k++){
        for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){
            Vertices *auxI = *i; 
            ant = auxI->getId(); // ant recebe i
            for(auto j = grafo->nosGrafo.begin(); j != grafo->nosGrafo.end(); j++){
                Vertices *auxJ = *j;
                dep = auxJ->getId(); // dep recebe j
                if(ant != dep){ // se i != j, foi inicializado com 0
                    soma = F[ant][k] + F[k][dep]; 
                    teste = F[ant][dep]; // valor atual
                    if(soma < teste) // se a soma for menor que valor atual
                        F[ant][dep] = soma; // F[i][j] recebe soma
                }
            }
        }  
    }

    if(F[noI][noAlvo] < INT_MAX/2) // Se encontrou caminho entre os vertices inicial e alvo
        cout << endl << "Custo do caminho minimo: " << F[noI][noAlvo] << endl;
    else
        cout << endl << "Nao existe caminho entre o vertice " << noI << " e o vertice " << noAlvo << endl;
    
    delete F; // free memory
}

