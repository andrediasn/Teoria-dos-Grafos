#ifndef AGM_H_INCLUDED
#define AGM_H_INCLUDED
#include "Vertices.h"
#include <list>
#include <vector>

class Agm{
    public:
        Agm();
        ~Agm();

        std::list<Arestas*> arestasAgm; // lista com arestas do grafo   
        std::list<Vertices*> nosAgm; //lista com nos do grafo    

        void insereVertice(Vertices* v); // Insere vertice passando id    
        void insereAresta(Arestas* a); // Insere aresta passando id do vertice de origem, vertice alvo, e o peso
        string ProcuraVertice(int id);

};
#endif //AGM_H_INCLUDED