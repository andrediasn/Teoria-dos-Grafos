#include "Grafo.h"
#include "Vertices.h"
#include "Arestas.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>

Arestas::Arestas(int id, int id_alvo, float peso)
{
    this->id = id;
    this->id_alvo = id_alvo;
    this->Peso = peso;
}

Arestas::~Arestas()
{
    
}

float Arestas::getPeso()
{
    return this->Peso;
}

void Arestas::setPeso(float peso)
{
    this->Peso = peso;
}

int Arestas::getId()
{
    return this->id;
}

void Arestas::setId(int id)
{
    this->id = id;
}

int Arestas::getId_alvo()
{
    return this->id_alvo;
}

void Arestas::setId_alvo(int id_alvo)
{
    this->id_alvo = id_alvo;
}

