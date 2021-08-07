#include "Floyd.h"
#include "Vertices.h"
#include "Grafo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
#include <limits.h>

Floyd::Floyd(){

}
Floyd::~Floyd(){
    
}

int Floyd::criaFloyd(Grafo* grafo, int noI, int noAlvo){
    Vertices* ver =  grafo->procurarNo(noAlvo);
    if(ver->getGrauEntrada() == 0){ // Se o alvo n tem entrada
        cout << endl << "Nao existe caminho entre o noh " << noI << " e o noh " << noAlvo << endl;
        return 0; 
    }

    int n = grafo->getOrdem();
    int F[n][n][n];
    //Inicializando matriz com infinito, e iguais com 0
    for (int k=0; k<n;k++){
        for (int i=0; i<n;i++){
            for (int j=0; j<n;j++){
                if(i==j){
                    F[k][i][j] = 0;
                }
                else {
                    F[k][i][j] = INT_MAX/2;
                }
            }
        }
    }
    //impMat(F, n);

    // Criando matriz inicial do grafo
    for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){
        Vertices* auxI = *i;
        for(auto j = auxI->ListAdj.begin(); j != auxI->ListAdj.end(); j++){
            Vertices* auxJ = grafo->procurarNo(*j);
            Arestas* arestaAux = grafo->existeAresta(auxI->getId(), auxJ->getId());
            F[0][auxI->getId()][auxJ->getId()] = arestaAux->getPeso();

        }
    }
    int teste = F[n-1][noI][noAlvo];
    // Algoritimo de Floyd
    for(int k=0;k<n;k++){
        /* Quais vertices chegam no 0 ? */
        for(auto i = grafo->arestasGrafo.begin(); i != grafo->arestasGrafo.end(); i++){
            Arestas* auxA = *i;
            if(auxA->getId_alvo() == k){
                
            }
            /* Quais o vertices 0 alcança?
            Dos vert q chegam no 0, existe caminho menor doq caminho ate o
            vert q o 0 alcanca? */

            int vI = auxI->getId();
            for(auto j = auxI->ListAdj.begin(); j != auxI->ListAdj.end(); j++){
                Vertices* auxJ = grafo->procurarNo(*j);
                Arestas* arestaAux = grafo->existeAresta(auxI->getId(), auxJ->getId());
                if(F[k][vI][*j] < F[k][vI][k]+F[k][k][*j]){
                    F[k][vI][*j] = F[k][vI][*j];
                }
                else {
                    F[k][vI][*j] = F[k][vI][k]+F[k][k][*j];
                }
            }
        }
    }
    

    teste = F[n-1][noI][noAlvo];
    if(F[n-1][noI][noAlvo] == 0){ // se houve custo menor que o valor iniciado
        cout << endl << "Nao existe caminho entre o noh " << noI << " e o noh " << noAlvo << endl;
        return 0;
    }
    else{
        cout << "Custo minimo: " << F[n-1][noI][noAlvo] << endl;
        return F[n-1][noI][noAlvo];
    }
}

void Floyd::impMat(int **F[], int n){
    for(int k=0;k<n;k++){
        cout << endl << "It: " << k << endl;
        for(int i=0;i<n;i++){
            cout << "Linha " << i << ": " << endl;   
            for(int j=0;j<n;j++){
                cout << F[k][i][j] << " ";
            }
        }
    }
}

