#ifndef VERTICES_H_INCLUDED
#define VERTICES_H_INCLUDED
#include "Arestas.h" //incluindo o arestas.h
#include <vector>
#include <list>

using namespace std;

class Vertices{ //classe vertice

   //atributos
private:// atributos privados

    int id; // identificador do vertice
    int grau_de_entrada; // grau de entrada do vertice (direcionado)
    int grau_de_saida;// grau de saida do vertice (direcionado) 
    int grau;
    float peso;// peso dos vertices
    bool visitado;//visitado? sim ou nao
    float x;
    float y;
    

public: // declaraçoes publicas
    
    list<Vertices*> ListAdjV;
    list<int> ListAnt; // Lista de predecessores
    list<int> ListAdj; //lista de adjacencia de vertice               

    Vertices(int id, float x=0, float y=0, float peso=0); // construtor, passando como parametro o identificador do vertice
    // Destructor
    ~Vertices(); // destrutor
    // Getters (declaracao dos gets)
    int getId();//retorna o identificador
    int getGrauEntrada();//retorna o grau de entrada do vertice (direcionado)
    int getGrauSaida();//retorna o grau de saida do vertice (direcionado)
    int getGrau();
    void setGrau(int x);
    float getPeso();//retorna o peso do vertice se houver
    // Setters (declaracao do sets)
    void setPeso(float peso);//insere o peso no vertice
    void adicionarGrauSaida();//incrementa grau de saida
    void subtrairGrauSaida();//decrementa grau de saida
    void adicionarGrauEntrada();//incrementa grau de entrada
    void subtrairGrauEntrada();//decrementa grau de entrada
    void addGrau();

    // Other methods
    void adicionaAdjacencia(int id_alvo); // add adjacencia
    void adicionaAntecessor(int id_ant); // add predecessor
    void adicionaAdjacenciaV(Vertices* v);
    bool buscaAresta(int id_alvo);//existe esse vertice no grafo? passando o id do vertice alvo
    //Arestas* insereAresta(int id, int id_alvo, float peso = 0);//insere novo vertice passando como parametro id e peso (se houver), se nao houver passa 0
    void removeTodasArestas();// remove todas as arestas
    int removeAresta(int id, bool direcionado, Vertices* target_node);// remove aresta
    
    bool getVisitado(); // retorna se esta visitado
    void setVisitado(bool visitado); // altera visitado

    float getX();
    float getY();
        

};

#endif // VERTICES_H_INCLUDED