#include "Grafo.h"
#include "Vertices.h"
#include "Agm.h"
#include "Dijkstra.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>


using namespace std;

//construtor do grafo
Grafo::Grafo(int ordem, bool direcionado, bool pesoArestas, bool pesoVertices){
    this->ordem = ordem;//inicializa a ordem com a ordem passada
    this->direcionado = direcionado;//inicializa o grafo se é direcionado ou nao
    this->pesoArestas = pesoArestas;//inicializa o grafo com peso nas arestas ou nao
    this->pesoVertice = pesoVertices;//inicializa o grafo com peso nos vertices ou nao
    for(int i=0; i<this->ordem;i++)//inicializa a lista de vertices do grafo com todos os vertices de 0 a n-1 sendo n a ordem do grafo
    {
        insereVertice(i);//insere cada vertice do grafo de uma vez (ja que sabemos o numero de nos pela "ordem")
    }
    

}

Grafo::~Grafo()//destrutor
{
    

}


int Grafo::getOrdem(){
    return this->ordem;
}
void Grafo::insereVertice(int id)// Insere vertice passando id
{
    if(existeVertice(id))//pesquisa o id do vertice
    {
        cout << "O no jah existe no grafo.\n";//se ja existir printa que ja existe
        return;//e volta
    }
    Vertices* no = new Vertices(id);//aloca um novo no dinamicamente
    nosGrafo.push_back(no);//cria um novo no
    //cout << "No inserido com sucesso.\n";//printa que foi inserido com sucesso
}

void Grafo::insereAresta(int id, int id_alvo,bool direcionado, float pesoArestas)// Inseri aresta passando id do vertice de origem, vertice alvo, e o peso
{

    if(!nosGrafo.empty()){//se o grafo nao for vazio
        if(!existeVertice(id)){//se nao existir o no no grafo
            cout << "O vertice de origem nao existe no grafo.\n";//printa que nao tem vertice
            return;//e volta
        }else if(!existeVertice(id_alvo)){//se nao existir o vertice alvo
            cout << id_alvo <<"  vertice de destino nao existe no grafo.\n";//printa que nao existe
            return;//e volta
        }
        else{//caso tenha os 2
            Arestas* auxAresta;//cria uma aresta auxiliar
            if(direcionado == false)//se ela nao for direcionada
            {
                Vertices* no1 = procurarNo(id);//cria um vertice auxiliar para alterarmos os dados dos vertices
                Vertices* no2 = procurarNo(id_alvo);//cria um auxiliar para o vertice alvo igual ao primeiro
                auxAresta = no1->insereAresta(id, id_alvo, pesoArestas);//insere aresta no grafo passando o vertice inicial, final e peso
                no1->adicionarGrauSaida();//adiciona 1 ao grau de saida
                no1->adicionarGrauEntrada();//adiciona grau de entrada, ja que nao é direcionado
                //como nao é um grafo direcionado temos que fazer o mesmo para o vertice 2 tambem para adicionarmos a adjacencia
                //Obs: nao é necessario adicionar uma nova aresta se nao teriamos uma multiaresta
                no2->adicionaAdjacencia(id);//adiciona adjacencia do vertice1 no vertice2
                no2->adicionarGrauEntrada();//adiciona o grau de entrada
                no2->adicionarGrauSaida();//adiciona o grau de saida
                arestasGrafo.push_back(auxAresta);//poe ela na lista de arestas do grafo
                Arestas *arestasContraria = new Arestas(id_alvo,id,pesoArestas);
                arestasGrafo.push_back(arestasContraria);
                
            }
            else if(direcionado == true)//se for direcionada
            {
                Vertices* no1 = procurarNo(id);//cria um vertice auxiliar para alterarmos os dados dos vertices
                Vertices* no2 = procurarNo(id_alvo);//cria um auxiliar para o vertice alvo igual ao primeiro
                //adicionando peso nos vertices
                auxAresta = no1->insereAresta(id, id_alvo, pesoArestas);//insere aresta no grafo passando o vertice inicial, final e peso
                no1->adicionarGrauSaida();//adiciona 1 ao grau de saida
                no2->adicionarGrauEntrada();//adiciona o grau de entrada
                arestasGrafo.push_back(auxAresta);//poe ela na lista de arestas do grafo
                no2->ListAnt.push_back(no1->getId());
            }
            //cout << "Aresta inserida com sucesso!\n";//printa aresta inserida com sucesso
        }
    }
}

void Grafo::removeNode(int id){ //remove vertice
    if(existeVertice(id)){//se o vertice nao existe no grafo entra no if
        cout << "O no nao existe no grafo!\n";//o vertice nao existe
    }
    for (auto i = nosGrafo.begin();i!=nosGrafo.end();i++)//percorre os vertices do grafo 
    {
        Vertices* aux = *i;//cria um vertice auxiliar
        if (aux->getId() == id)//se o id do vertice passado for igual
        {
            nosGrafo.erase(i);//apaga o no do grafo na posiçao i
        }
    }

}

Vertices* Grafo::procurarNo(int id)//pesquisa vertice no grafo e retorna ele
{
    for (auto i = nosGrafo.begin();i!=nosGrafo.end();i++)//percorre os vertices do grafo 
    {
        Vertices* aux = *i;//cria um vertice auxiliar
        if (aux->getId() == id)//se o id do vertice passado for igual
            return aux;//retorna o vertice
    }
    return nullptr;//se nao, retorna null
}

bool Grafo::existeVertice(int id)//procura se existe aquele vertice
{
     for (auto i = nosGrafo.begin();i!=nosGrafo.end();i++)//percorre os vertices do grafo 
    {
        Vertices* aux = *i;//cria um auxiliar para conferencia
        if (aux->getId() == id)//se o id do vertice passado for igual
            return true;//retorna que existe o vertice
    }
    return false;//se nao, retorna falso
}

// FUNCAO PARA ACHAR UMA ARESTA DADO DOIS VERTICES
Arestas* Grafo::existeAresta(int id ,int id_alvo){
    for (auto i = arestasGrafo.begin(); i != arestasGrafo.end(); i++){
        Arestas* verificador = *i;
        if(verificador->getId() == id && verificador->getId_alvo() == id_alvo){
            return verificador;
        }
    }
    cout << "Nao existe essa aresta no grafo." << endl;
    return NULL;
}


void Grafo::arrumaVisitado(){
    for(auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
        Vertices* aux = *i;
        aux->setVisitado(false);
    }
}

// FUNCAO PARA ACHAR A MENOR ARESTA DENTRE DOIS NOS 
Agm* Grafo::arestaMaisBarata(Vertices* v,Agm* agm){
    int menor = INT32_MAX; 
    
    v->setVisitado(true);
    Arestas* ponteiro = NULL;
    // Percorrengo toda a lista de adj do vertice v
    for(auto i = v->ListAdj.begin(); i != v->ListAdj.end(); i++){
        int aux = *i; 
        Vertices* proximo = procurarNo(*i);
        if(proximo->getVisitado() == false){
            Arestas* arestaAux = existeAresta(v->getId(),aux);
            if(arestaAux != NULL){
                if(arestaAux->getPeso() < menor){
                    menor = arestaAux->getPeso();
                    ponteiro = arestaAux;
                }
            }
        }
    }
    if(ponteiro != NULL){
        
        Vertices* verticeVisitado = procurarNo(ponteiro->getId_alvo());
        verticeVisitado->setVisitado(true);
        agm->insereVertice(v);
        agm->insereVertice(verticeVisitado);
        agm->insereAresta(ponteiro);
        arestaMaisBarata(verticeVisitado,agm);
    }
    return agm;
}

Agm* Grafo::arvoreGeradoraMinimaPrim(int v){
    // Verificar se o grafo e conexo
    // Se for faca tudo abaixo se nao saia do programa 
    Vertices* aux = procurarNo(v);

    Agm *agm = new Agm();             // Criando o conjunto solucao das arestas com menor peso 
    agm = arestaMaisBarata(aux,agm);// Procurar dentre todos os vizinhos do vertice inicial qual tem aresta com menor peso 
     
    // Percorrendo a lista de adj ate achar o mais barato
    arrumaVisitado();
    return agm;
}


list<int> Grafo::fechoDireto(int ID)
{
    list<int> listaSolucao;//cria uma lista de soluçao
    if(this->direcionado == false){
        cout<< "Esse grafo nao eh direcionado, portanto, nao contem fecho transitivo direto"<< endl;
    }
    else
    {
        listaSolucao = fechoDiretoAux(ID,listaSolucao);//chama a funçao auxiliar para fazer de modo recursivo
        list<int>::iterator it;
        cout<< "Os vertices que sao alcansaveis a partir do informado sao: ( ";
        for ( it = listaSolucao.begin(); it != listaSolucao.end(); it++){
            
            cout<< *it << " ";
        }
        cout<< ")" <<endl;
    }
    arrumaVisitado();
    return listaSolucao;
}

list<int> Grafo::fechoDiretoAux(int ID, list<int> ListaFechoDireto)//funçao auxiliar recursiva de fecho direto
{
    Vertices* VerticeAux = procurarNo(ID);//procura o vertice com o id passado 
    for (auto i = VerticeAux->ListAdj.begin(); i != VerticeAux->ListAdj.end(); i++)//percorre os ids adjacentes a esse no 
    {
        Vertices* verticeAdj = procurarNo(*i);//variavel com o proximo vertice
        if(verticeAdj->getVisitado()==true)//se o no ja foi visitado
        {
            //nao faz nada
        }
        else//caso nao tenha sido visitado
        {
            verticeAdj->setVisitado(true);//coloque como visitado
            ListaFechoDireto.push_back(verticeAdj->getId());//adiciona na lista soluçao
            ListaFechoDireto = fechoDiretoAux(verticeAdj->getId(),ListaFechoDireto);//entra novamente na recursao
        }
    }
    return ListaFechoDireto;//volta a lista no final
}

list<int> Grafo::fechoIndireto(int ID){
    list<int> solucao;
    if(this->direcionado == false){
        cout<< "Esse grafo nao eh direcionado, portanto, nao contem fecho transitivo indireto"<< endl;
    }
    else {
        for(auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
            Vertices* aux = *i;
            aux->setVisitado(false);
        }

        solucao = fechoIndiretoAux(ID, solucao);
        cout << "Solucao FI: ( ";
        for (auto i = solucao.begin(); i!=solucao.end(); i++){
            cout << *i << " ";
        }
        cout << " )" << endl;
    }
    arrumaVisitado();
    return solucao;
}

list<int> Grafo::fechoIndiretoAux(int ID, list<int> solucao){
    Vertices* alvo = procurarNo(ID);
    alvo->setVisitado(true);
    for(auto i = alvo->ListAnt.begin(); i != alvo->ListAnt.end(); i++){
        Vertices* verifica = procurarNo(*i);
        if(!verifica->getVisitado()){
            solucao.push_back(*i);
            solucao = fechoIndiretoAux(*i, solucao);
        }
    }
    return solucao;
}


void Grafo::caminhoEmProfundidade(int id){
    Agm* solucao = new Agm();
    int ultimo = -1;
    for(auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
        Vertices* aux = *i;
        aux->setVisitado(false);
    }
    ultimo = caminhoEmProfundidadeAux(solucao, id, ultimo);
}
int Grafo::caminhoEmProfundidadeAux(Agm* solucao, int id, int ultimo){
    Vertices* inicial = procurarNo(id);
    solucao->insereVertice(inicial);
    inicial->setVisitado(true);
    int aux;
    for (auto i = inicial->ListAdj.begin(); i != inicial->ListAdj.end(); i++) {
        aux = *i;
        if(i != inicial->ListAdj.begin() && ultimo != -1){
            Arestas* retorno = new Arestas(ultimo, inicial->getId());
            solucao->insereAresta(retorno);
            cout << "Inserindo Aresta: (" << ultimo << "," << inicial->getId() << ")" << endl;
            ultimo = -1;
        }
        Vertices* vVisitado = procurarNo(aux);
        if(!vVisitado->getVisitado()){
            ultimo = caminhoEmProfundidadeAux(solucao, aux, ultimo);
        }
    }
    ultimo = inicial->getId();
    return ultimo;
}


Grafo* Grafo::caminhoMinimoDjkstra(int ID1, int ID2){
    Dijkstra aux;
    Grafo* teste = this;
    list<int> caminho = aux.caminhoMinimo(teste, ID1, ID2);
    if(caminho.size()>0){
        cout << "Caminho: ";
        for(auto i = caminho.begin(); i != caminho.end(); i++){
            cout << *i << " ";
        }
        cout << endl;
    }
}