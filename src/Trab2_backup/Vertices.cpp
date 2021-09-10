#include "Vertices.h"
#include "Arestas.h"
#include <iostream>
#include <vector>
#include <list>

Vertices::Vertices(int id, float x, float y, float peso){ // construtor passando o identificador como parametro

    this->id = id; // seta o identificador
    this->grau_de_entrada = 0;// coloca grau de entrada como 0
    this->grau_de_saida = 0;// coloca grau de saida como 0
    this->peso = peso;// declara peso , se nao for passado é igual a 0
    this->grau= 0;
    this->visitado = false;
    this->x = x; // Coordenadas x
    this->y = y; // Coordenadas y
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
void Vertices::addGrau(){
    this->grau ++;
}

void Vertices::adicionaAdjacenciaV(Vertices* v){
    this->ListAdjV.push_back(v);
}

void Vertices::adicionaAdjacencia(int id_alvo)
{
    this->ListAdj.push_back(id_alvo);
}

void Vertices::adicionaAntecessor(int id_ant)
{
    this->ListAnt.push_back(id_ant);
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

int Vertices::getGrauEntrada(){
    return this->grau_de_entrada;
}

int Vertices::getGrauSaida(){
    return this->grau_de_saida;
}

int Vertices::getGrau(){
    return this->grau;
}

void Vertices::setGrau(int x){
    this->grau = x;
}

float Vertices::getX(){
    return this->x;
}

float Vertices::getY(){
    return this->y;
}