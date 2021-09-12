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
string Agm::ProcuraVertice(int id)
{
    for(auto i = nosAgm.begin(); i != nosAgm.end(); i++)
    {
        Vertices* comparativo = *i;
        if(comparativo->getId() == id)
        {
            return comparativo->getNome();
        }
    }
    return {};
}