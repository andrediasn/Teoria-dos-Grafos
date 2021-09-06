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
#include "Agm.h"

using namespace std;

class Dijkstra;
class Floyd;

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
    Arestas* existeAresta(int id ,int id_alvo); //retorna aresta se existir
    Vertices* procurarNo(int id); //retorna vertice se existir
    
    list<Arestas*> arestasGrafo; // lista com arestas do grafo       
    list<Vertices*> nosGrafo; //lista com nos do grafo            
    
    int getOrdem(); //retorna ordem do grafo
    bool conexo(); // verifica se grafo eh conexo
    void arrumaVisitado(); // seta todos vertices.visitado como false 
    
    Agm* arestaMaisBarata(Vertices* v,Agm* agm);  
    list<int> fechoDireto(int ID);//funçao para achar o fecho transitivo direto
    list<int> fechoDiretoAux(int ID, list<int> ListaFechoDireto); //auxiliar para recursividade do fecho
    list<int> fechoIndireto(int ID);//achar o fecho transitivo indireto
    list<int> fechoIndiretoAux(int ID, list<int> listaFechoIndireto);//achar o fecho transitivo indireto
    list<int> caminhoMinimoDijkstra(int ID1, int ID2);//caminho minimo entre v1 e v2 passados por parametro usando Dijkstra
    void caminhoMinimoFloyd(int ID1, int ID2); // custo minimo entre v1 e v2 passados por parametro usando floyd
    Agm* arvoreGeradoraMinimaPrim(int v);//cria uma arvore geradora minima usando prim
    Agm* caminhoEmProfundidade(int id);//caminha em profundidade pelo grafo
    int caminhoEmProfundidadeAux(Agm* solucao, int id, int ultimo);//aux do caminha em profundidade pelo grafo
    void ordenacaoTopologica();//faz a ordenaçao topologica do grafo
    Agm* arvoreGeradoraMinimaKruskal();//cria uma arvore geradora minima usando kruskal
    void unir(int v1,int v2, int *ciclo); // Usado para verificar ciclos
    int pai(int v, int *ciclo); // Usado para verificar ciclos

    void Guloso();
    list<Arestas*> ordenaArestas(list<Arestas*> lista);
    void quickSort(vector<Arestas*> *copia, int inicio, int fim); // ordenacao pelo metodo de quicksort
    int partQuick(vector<Arestas*> *copia, int inicio, int fim); // aux do quicksort
    bool verAciclico(int id, int alvo, Agm *agm);
    bool aciclico(int id, int alvo, Agm *agm);

};

#endif //GRAFO_H_INCLUDED