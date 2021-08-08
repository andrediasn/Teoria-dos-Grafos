#ifndef ARESTAS_H_INCLUDED
#define ARESTAS_H_INCLUDED


class Arestas{ //classe aresta

   //atributos
private:// atributos privados
   float Peso;
   int id;
   int id_alvo;

public:
   Arestas(int id,int id_alvo, float peso = 1);
   ~Arestas();
   float getPeso();
   int getId();
   int getId_alvo();
   void setPeso(float peso);
   void setId(int id);
   void setId_alvo(int id_alvo);
};

#endif // ARESTAS_H_INCLUDED
