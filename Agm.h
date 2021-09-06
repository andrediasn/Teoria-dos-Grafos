#ifndef AGM_H_INCLUDED
#define AGM_H_INCLUDED
#include "Vertices.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;
class Agm{
    public:
        Agm();
        ~Agm();

        std::list<Arestas*> arestasAgm; // lista com arestas do grafo   
        std::list<Vertices*> nosAgm; //lista com nos do grafo    

        void insereVertice(Vertices* v); // Insere vertice passando id    
        void insereAresta(int id1, int id2,int nv, Arestas* a); // Insere aresta passando id do vertice de origem, vertice alvo, e o peso
        Vertices* retornaVertice(int id);//pesquisa vertice no grafo e retorna ele
        void adicionaArestaAGM(Vertices* v1, Vertices* v2, Arestas* auxiliar);
        void imprimeAGM();
        void saidaAgmDot();
        void arrumaVisitado();
};
#endif //AGM_H_INCLUDED