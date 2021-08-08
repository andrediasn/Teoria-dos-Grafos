#ifndef FLOYD_H_INCLUDED
#define FLOYD_H_INCLUDED
#include "Vertices.h"
#include "Arestas.h"
#include "Grafo.h"

class Floyd{
    private:
    void criaCaminho(int noI, int noF, int **P);
    list<int> caminho;

    public:
    Floyd();
    ~Floyd();

    list<int> criaFloyd(Grafo* grafo, int noI, int noAlvo);


};
#endif //FLOYD_H_INCLUDED
