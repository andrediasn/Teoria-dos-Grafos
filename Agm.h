#ifndef AGM_H_INCLUDED
#define AGM_H_INCLUDED
#include "Vertices.h"
#include <list>
#include <vector>

class Agm{
    public:
    std::list<Arestas*> arestasAgm; // lista com arestas do grafo   
    std::list<Vertices*> nosAgm; //lista com nos do grafo    

    Agm();
    ~Agm();
    void insereVertice(Vertices* v);     
    void insereAresta(Arestas* a);

};
#endif //AGM_H_INCLUDED