#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <algorithm>
#include <limits.h>
#include <stack>
#include <math.h>
#include <list>
#include <vector>
#include <ctime>
#include <bits/stdc++.h>
#include "Vertices.h"
#include "Arestas.h"
#include "Agm.h"

using namespace std;


class Grafo{
    //atributos
    private:
    int ordem; //ordem do grafo
    bool direcionado; //direcionado ou nao
    bool pesoArestas; //peso nas arestas
    bool pesoVertice; //peso nos vertices

    int calculaDist(int id, int id_alvo);

    public:
    
    Grafo(int ordem, float **coord, bool direcionado = false, bool pesoArestas= false, bool pesoVertices = false);
    ~Grafo();

    void insereVertice(int id, float x, float y); // Insere vertice no grafo 
    void insereAresta(int id,int id_alvo,bool direcionado = false); // Insere aresta no grafo
    void removeNode(int id); // Remove vertice do grafo
    bool existeVertice(int id); // Procura vertice no grafo
    Vertices* procurarNo(int id); //retorna vertice se existir
    
    list<Arestas*> arestasGrafo; // lista com arestas do grafo       
    list<Vertices*> nosGrafo; //lista com nos do grafo            
    
    int getOrdem(); //retorna ordem do grafo
    bool conexo(); // verifica se grafo eh conexo
    void arrumaVisitado(); // seta todos vertices.visitado como false 
    
    void Guloso(string instancia);
    list<Arestas*> ordenaArestas(list<Arestas*> lista);
    void quickSort(vector<Arestas*> *copia, int inicio, int fim); // ordenacao pelo metodo de quicksort
    int partQuick(vector<Arestas*> *copia, int inicio, int fim); // aux do quicksort
    //bool verAciclico(int id, int alvo, Agm *agm);
    //bool aciclico(Vertices *v, int alvo, Agm *agm);

    void gulosoRandomizado(float alfa, int numInter);

};

#endif //GRAFO_H_INCLUDED