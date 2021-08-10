#ifndef FLOYD_H_INCLUDED
#define FLOYD_H_INCLUDED
#include "Vertices.h"
#include "Arestas.h"
#include "Grafo.h"

class Floyd{
    private:
    list<int> caminho;

    void criaCaminho(int noI, int noF, int **P);
    void matrizCSV(int n, int **P);

    public:
    Floyd();
    ~Floyd();

    list<int> caminhoMinimo(Grafo* grafo, int noI, int noAlvo);


};
#endif //FLOYD_H_INCLUDED
