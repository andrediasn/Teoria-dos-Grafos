#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "Vertices.h"
#include "Agm.h"
#include <list>
#include <vector>

class Dijkstra;
class Floyd;

class Grafo{
    //atributos
    private:
    int ordem; //ordem do grafo
    bool direcionado; //direcionado ou nao
    bool pesoArestas; //peso nas arestas
    bool pesoVertice; //peso nos vertices

    public:
    
    //  Deve ser implementadas
    void insereVertice(int id);     
    void insereAresta(int id,int id_alvo,bool direcionado = false ,float pesoArestas = 0);
    void removeNode(int id);

    bool existeVertice(int id);
    bool getDirecionado();
    bool nTemCiclo();          
    Arestas* existeAresta(int id ,int id_alvo);
    Vertices* procurarNo(int id);
    
    std::list<Arestas*> arestasGrafo; // lista com arestas do grafo       
    std::list<Vertices*> nosGrafo; //lista com nos do grafo            
    
    int getOrdem();
    bool conexo();
    void arrumaVisitado();

    Grafo(int ordem, bool direcionado = false, bool pesoArestas= false, bool pesoVertices = false);
    ~Grafo();
   
    
    Agm* arestaMaisBarata(Vertices* v,Agm* agm);

    //void adicionarAresta(Vertices* ID, Vertices* ID2);//adiciona aresta no grafo
    
    list<int> fechoDireto(int ID);//funçao para achar o fecho transitivo direto
    list<int> fechoDiretoAux(int ID, list<int> ListaFechoDireto); //auxiliar para recursividade do fecho
    list<int> fechoIndireto(int ID);//achar o fecho transitivo indireto
    list<int> fechoIndiretoAux(int ID, list<int> listaFechoIndireto);//achar o fecho transitivo indireto
    list<int> caminhoMinimoDijkstra(int ID1, int ID2);//caminho minimo entre v1 e v2 passados por parametro usando Dijkstra
    list<int> caminhoMinimoFloyd(int ID1, int ID2); // caminho minimo entre v1 e v2 passados por parametro usando floyd
    list<Vertices*> subconjuntoX();//cria um subconjunto de vertices
    Agm* arvoreGeradoraMinimaPrim(int v);//cria uma arvore geradora minima usando prim
    Agm* arvoreGeradoraMinimaKruskal();//cria uma arvore geradora minima usando kruskal
    Agm* caminhoEmProfundidade(int id);//caminha em profundidade pelo grafo
    int caminhoEmProfundidadeAux(Agm* solucao, int id, int ultimo);//aux do caminha em profundidade pelo grafo
    void ordenacaoTopologica();//faz a ordenaçao topologica do grafo
    list<int> ordenacaoTopologica2();

    void quickSort(vector<Vertices*> *copia, int inicio, int fim);
    int partQuick(vector<Vertices*> *copia, int inicio, int fim);

    void unir(int v1,int v2, int *ciclo);
    int pai(int v, int *ciclo);
};

#endif //GRAFO_H_INCLUDED