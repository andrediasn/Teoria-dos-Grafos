#include "Arestas.h"


Arestas::Arestas(Vertices* v1,Vertices *v2, float peso){
    this->v1 = v1;
    this->v2 = v2;
    this->Peso = peso;
}

Arestas::~Arestas(){}

float Arestas::getPeso(){
    return this->Peso;
}

void Arestas::setPeso(float peso){
    this->Peso = peso;
}

Vertices* Arestas::getV1(){
    return this->v1;
}

void Arestas::setV1(Vertices* v1){
    this->v1 = v1;
}

Vertices* Arestas::getV2(){
    return this->v2;
}

void Arestas::setV2(Vertices* v2){
    this->v2 = v2;
}

