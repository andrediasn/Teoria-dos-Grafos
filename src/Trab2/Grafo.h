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


    public:
    
    Grafo(int ordem, float **coord, bool direcionado = false, bool pesoArestas= false, bool pesoVertices = false);
    ~Grafo();

    void insereVertice(int id, float x, float y); // Insere vertice no grafo 
    void insereAresta(int id,int id_alvo,bool direcionado = false); // Insere aresta no grafo
    int calculaDist(int id, int id_alvo);
    void removeNode(int id); // Remove vertice do grafo
    bool existeVertice(int id); // Procura vertice no grafo
    Vertices* procurarNo(int id); //retorna vertice se existir
    
    vector<Arestas*> arestasOrdenadas; // lista de arestas ordenadas
    list<Arestas*> arestasGrafo; // lista com arestas do grafo       
    list<Vertices*> nosGrafo; //lista com nos do grafo            
    
    int getOrdem(); //retorna ordem do grafo
    bool conexo(); // verifica se grafo eh conexo
    void arrumaVisitado(); // seta todos vertices.visitado como false 
    void arrumaGrau();

    void ordenaArestas();
    void quickSort(vector<Arestas*> *copia, int inicio, int fim); // ordenacao pelo metodo de quicksort
    int partQuick(vector<Arestas*> *copia, int inicio, int fim); // aux do quicksort
    
    void Guloso(string instancia, string caminho);
    int gulosoRandomizado(float alfa, int numInter, double tempo[], int seed);
    void gulosoRandomizadoReativo(int numInter,double tempo[], int bloco, int seed, string instancia, string caminho);
    float escolheAlfa(int probAlfa[], int seed);
    void atualizaProb(int *probAlfa,int **resultBloco);
    void resetBloco(int **resultBloco, int bloco);
};

#endif //GRAFO_H_INCLUDED