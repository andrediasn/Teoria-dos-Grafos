#ifndef ARESTAS_H_INCLUDED
#define ARESTAS_H_INCLUDED
#include <iostream>
#include <fstream>
#include <sstream>
#include "Vertices.h"

class Vertices;
class Arestas{ //classe aresta
   private:// atributos privados
      float Peso;
      Vertices* v1;
      Vertices* v2;

   public:
      Arestas(Vertices* v1,Vertices *v2, float peso = 0);
      ~Arestas();
      float getPeso();
      Vertices* getV1();
      Vertices* getV2();
      void setPeso(float peso);
      void setV1(Vertices* v1);
      void setV2(Vertices* v2);
};

#endif // ARESTAS_H_INCLUDED
