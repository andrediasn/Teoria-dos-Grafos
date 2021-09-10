#include "Agm.h"
#include "Vertices.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>

Agm::Agm(){}
Agm::~Agm(){}

void Agm::insereVertice(Vertices* v) { // Insere vertice passando id
    this->nosAgm.push_back(v);
}

void Agm::insereAresta(Arestas* a) { // Insere aresta passando id do vertice de origem, vertice alvo, e o peso
    this->arestasAgm.push_back(a);
}
