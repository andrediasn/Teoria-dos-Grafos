#include "Agm.h"

Agm::Agm(){}
Agm::~Agm(){}

void Agm::insereVertice(Vertices* v) { // Insere vertice passando id
    this->nosAgm.push_back(v);
}

void Agm::insereAresta(int id1, int id2,int nv, Arestas* a) { // Insere aresta passando id do vertice de origem, vertice alvo, e o peso
    Vertices* Agmv1;
    Vertices* Agmv2;
    switch(nv){
        case 0: 
            Agmv1 = new Vertices(id1);
            Agmv2 = new Vertices(id2);
            break;
        case 1:
            Agmv1 = retornaVertice(id1);
            Agmv2 = new Vertices(id2);
            break;
        case 2:
            Agmv1 = new Vertices(id1);
            Agmv2 = retornaVertice(id2);
            break;
        default:
            Agmv1 = retornaVertice(id1);
            Agmv2 = retornaVertice(id2);
            break;
    }
    Agmv1->addGrau();
    Agmv2->addGrau();
    Agmv1->adicionaAdjacenciaV(Agmv2);
    Agmv2->adicionaAdjacenciaV(Agmv1);
    insereVertice(Agmv1);
    insereVertice(Agmv2);
    this->arestasAgm.push_back(a);
}

void Agm::arrumaVisitado(){ // Seta visitados para false
    for(auto i = nosAgm.begin(); i != nosAgm.end(); i++){
        Vertices* aux = *i;
        aux->setVisitado(false);
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

void Agm::saidaResult(string instancia, float time){
    int lb = 0;
    for(auto i = arestasAgm.begin(); i != arestasAgm.end(); i++){
        Arestas* auxiliar = *i;
        lb += auxiliar->getPeso(); 
    }
    cout<< "Lower Bound: " << lb << endl;
    ofstream arq("Resultado/resultGuloso.txt", ios::app);
    arq << instancia << "; ;" << lb << ";" << time << "s" << endl;
    arq.close();
}

void Agm::saidaAgmDot(){
    ofstream arq("Resultado/agm.txt", ios::out);
    arq << "graph {" << endl;

    for (auto i = arestasAgm.begin(); i != arestasAgm.end(); i++){
        Arestas* aux = *i;
        arq << "    " << aux->getId() << " -- " << aux->getId_alvo() << " [label = " << aux->getPeso() << "]" <<endl;
    }
  
    arq << "}" << endl;
    arq.close();
}