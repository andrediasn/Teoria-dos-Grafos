#ifndef FLOYD_H_INCLUDED
#define FLOYD_H_INCLUDED
#include "Vertices.h"
#include "Arestas.h"
#include "Grafo.h"

class Floyd{
    private:

    public:
    Floyd();
    ~Floyd();

    int criaFloyd(Grafo* grafo, int noI, int noAlvo);


};
#endif //FLOYD_H_INCLUDED
