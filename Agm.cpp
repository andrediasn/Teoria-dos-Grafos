#include "Agm.h"

Agm::Agm(){}
Agm::~Agm(){}

void Agm::insereVertice(Vertices* v) { // Insere vertice passando id
    this->nosAgm.push_back(v);
}

void Agm::insereAresta(int id1, int id2,int nv, Arestas* a) { // Insere aresta passando id do vertice de origem, vertice alvo, e o peso
    Vertices* Agmv1;
    Vertices* Agmv2;
    switch(nv)
    {
        case 0: 
            Agmv1 = new Vertices(id1);
            Agmv1->addGrau();
            Agmv1->adicionaAdjacencia(id2);
            Agmv2 = new Vertices(id2);
            Agmv2->addGrau();
            Agmv2->adicionaAdjacencia(id1);
            insereVertice(Agmv1);
            insereVertice(Agmv2);
            this->arestasAgm.push_back(a);
            break;
        case 1:
            Agmv1 = retornaVertice(id1);
            Agmv1->addGrau();
            Agmv1->adicionaAdjacencia(id2);
            Agmv2 = new Vertices(id2);
            Agmv2->addGrau();
            Agmv2->adicionaAdjacencia(id1);
            insereVertice(Agmv2);
            this->arestasAgm.push_back(a);
            break;
        case 2:
            Agmv1 = new Vertices(id1);
            Agmv1->addGrau();
            Agmv1->adicionaAdjacencia(id2);
            Agmv2 = retornaVertice(id2);
            Agmv2->addGrau();
            Agmv2->adicionaAdjacencia(id1);
            insereVertice(Agmv1);
            this->arestasAgm.push_back(a);
            break;
        default:
            Agmv1 = retornaVertice(id1);
            Agmv1->addGrau();
            Agmv1->adicionaAdjacencia(id2);
            Agmv2 = retornaVertice(id2);
            Agmv2->addGrau();
            Agmv2->adicionaAdjacencia(id1);
            this->arestasAgm.push_back(a);
            break;
    }
}






Vertices* Agm::retornaVertice(int id){//pesquisa vertice no grafo e retorna ele
    for (auto i = nosAgm.begin();i!=nosAgm.end();i++){//percorre os vertices do grafo 
        Vertices* aux = *i;//cria um vertice auxiliar
        if (aux->getId() == id)//se o id do vertice passado for igual
            return aux;//retorna o vertice
    }
    return nullptr;//se nao, retorna null
}

void Agm::imprimeAGM()
{
    for(auto i = arestasAgm.begin(); i != arestasAgm.end(); i++)
    {
        Arestas* auxiliar = *i;
        cout<< auxiliar->getId() << " "<<auxiliar->getId_alvo() <<" " << auxiliar->getPeso()<<endl;
    }
}