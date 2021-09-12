#ifndef AGM_H_INCLUDED
#define AGM_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include "Vertices.h"
#include "Arestas.h"

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
        
        void saidaAgmDot();
        void saidaAgmDot2(string instancia);
        void arrumaVisitado();
        int calculaPesoTotal();
        bool ehVazia();

        void saidaResultGuloso(string instancia, double time);
        void saidaResultReativo(string instancia, int sol, double time, int max, int bloco);
        bool vazio(ifstream& arq);
};
#endif //AGM_H_INCLUDED