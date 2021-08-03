#include "Vertices.h"
#include "Arestas.h"
#include <iostream>
#include <vector>
#include <list>

Vertices::Vertices(int id, float peso){ // construtor passando o identificador como parametro

    this->id = id; // seta o identificador
    this->grau_de_entrada = 0;// coloca grau de entrada como 0
    this->grau_de_saida = 0;// coloca grau de saida como 0
    this->peso = peso;// declara peso , se nao for passado é igual a 0
    this->visitado = false;

}

Arestas* Vertices::insereAresta(int id, int id_alvo, float peso)//insere aresta passando como parametro o identificador, o identificador do vertice alvo e o peso
{ 
    Arestas* aresta = new Arestas(id, id_alvo,peso);//declara uma nova aresta
    adicionaAdjacencia(id_alvo); //aloca o id do vertice na lista de adj na lista de adjacencia 
    return aresta;       
}

void Vertices::adicionarGrauSaida()
{
    this->grau_de_saida = grau_de_saida + 1;//adiciona em 1 o grau de saida do vertice solicitado
}

void Vertices::subtrairGrauSaida()
{
    this->grau_de_saida = grau_de_saida - 1;//subtrai em 1 o grau de saida do vertice solicitado
}

void Vertices::adicionarGrauEntrada()
{
    this->grau_de_entrada = grau_de_entrada + 1;//incrementa em 1 o grau de entrada
}

void Vertices::subtrairGrauEntrada()
{
    this->grau_de_entrada = grau_de_entrada - 1;//decrementa em 1 o grau de entrada
}

void Vertices::adicionaAdjacencia(int id_alvo)
{
    this->ListAdj.push_back(id_alvo);
}

int Vertices::getId()
{
    return this->id;
}

void Vertices::setPeso(float P)
{
    this->peso = P;
}

bool Vertices::getVisitado(){
    return this->visitado ;
}

void Vertices::setVisitado(bool visitado){
    this->visitado = visitado;
}