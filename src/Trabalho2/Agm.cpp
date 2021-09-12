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
            insereVertice(Agmv1);
            insereVertice(Agmv2);
            break;
        case 1:
            Agmv1 = retornaVertice(id1);
            Agmv2 = new Vertices(id2);
            insereVertice(Agmv2);
            break;
        case 2:
            Agmv1 = new Vertices(id1);
            Agmv2 = retornaVertice(id2);
            insereVertice(Agmv1);
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
    Arestas* aux = new Arestas(Agmv1,Agmv2,a->getPeso());
    this->arestasAgm.push_back(aux);
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

void Agm::saidaResultGuloso(string instancia, string out, double time){
    string saida = out + "/ResultadoGuloso.txt";

    int lb = 0;
    for(auto i = arestasAgm.begin(); i != arestasAgm.end(); i++){
        Arestas* auxiliar = *i;
        lb += auxiliar->getPeso(); 
    }

    ofstream arq(saida, ios::app);
    ifstream v(saida);
    if(vazio(v))
       arq << "Instancia;Solucao;Tempo(s)" << endl;
    v.close();
    arq << instancia << ";"<< lb << ";" << time << endl;
    arq.close();
}

void Agm::saidaResultReativo(string instancia, string out, int sol, double time, int max, int bloco){
    string saida = out + "/ResultadoReativo.txt";

    ofstream arq(saida, ios::app);
    ifstream v(saida);
    if(vazio(v))
       arq << "Instancia;Solucao;Tempo(s);Quantidade de Iteracoes;Tamanho do Bloco" << endl;
    v.close();
    arq << instancia << ";"<< sol << ";" << time << ";" << max << ";" << bloco << endl;
    arq.close();
}

bool Agm::vazio(ifstream& arq){
    return arq.peek() == std::ifstream::traits_type::eof();
}


void Agm::saidaAgmDot(){
    ofstream arq("Resultado/Graph/agm.txt", ios::out);
    arq << "graph {" << endl;

    for (auto i = arestasAgm.begin(); i != arestasAgm.end(); i++){
        Arestas* aux = *i;
        Vertices* v1 = aux->getV1();
        Vertices* v2 = aux->getV2();
        arq << "    " << v1->getId() << " -- " << v2->getId() << " [label = " << aux->getPeso() << "]" <<endl;
    }

    arq << "}" << endl;
    arq.close();
}

void Agm::saidaAgmDot2(string instancia){
    string saida = "Resultado/Graph/" + instancia + ".txt";
    ofstream arq(saida, ios::out);
    arq << "graph {" << endl;

    for (auto i = arestasAgm.begin(); i != arestasAgm.end(); i++){
        Arestas* aux = *i;
        Vertices* v1 = aux->getV1();
        Vertices* v2 = aux->getV2();
        arq << "    " << v1->getId() << " -- " << v2->getId() << " [label = " << aux->getPeso() << "]" <<endl;
    }
  
    arq << "}" << endl;
    arq.close();
}

bool Agm::ehVazia()
{
    if(nosAgm.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Agm::calculaPesoTotal()
{
    int lb = 0;
    for(auto i = arestasAgm.begin(); i != arestasAgm.end(); i++){
        Arestas* auxiliar = *i;
        lb += auxiliar->getPeso(); 
    }
    return lb;
}
