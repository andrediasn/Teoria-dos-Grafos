#include "Grafo.h"
#include "Vertices.h"
#include "Agm.h"
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
            cout << "O vertice de destino nao existe no grafo.\n";//printa que nao existe
            return;//e volta
        }
        else{//caso tenha os 2
            Arestas* auxAresta;//cria uma aresta auxiliar
            if(direcionado == false)//se ela nao for direcionada
            {
                Vertices* no1 = procurarNo(id);//cria um vertice auxiliar para alterarmos os dados dos vertices
                Vertices* no2 = procurarNo(id_alvo);//cria um auxiliar para o vertice alvo igual ao primeiro
                auxAresta = no1->insereAresta(id, id_alvo, pesoArestas);//insere aresta no grafo passando o vertice inicial, final e peso
                cout << auxAresta->getPeso() <<endl;
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
// FUNCAO PARA ACHAR A MENOR ARESTA DENTRE DOIS NOS 

Agm* Grafo::arestaMaisBarata(Vertices* v,Agm* agm){
    int menor = 9999999999; 
    
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
   for (auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
      Vertices* verticeAux = *i;
      verticeAux->setVisitado(false);

   }
    cout << "aki 5" <<endl;
    return agm;
}


list<int> Grafo::fechoDireto(int ID)
{
    list<int> listaSolucao;//cria uma lista de soluçao
    if(this->direcionado == false){
        cout<< "esse grafo não é direcionado, portanto, nao contei fecho transitivo direto"<< endl;
    }
    else
    {
        fechoDiretoAux(ID,listaSolucao);//chama a funçao auxiliar para fazer de modo recursivo
        for (auto i = nosGrafo.begin(); i != nosGrafo.end(); i++)//for para resetar todos os nos para visitado como false
        {
            Vertices* setadordeVertice = *i;//aloca o conteudo de i em setador de vertice
            setadordeVertice->setVisitado(false);//coloca todos os vertices do grafo como nao visitados
        }
    }
    list<int>::iterator it;
    cout<< "Os vertices que sao alcansaveis a partir do informado sao: ( ";
    for ( it = listaSolucao.begin(); it != listaSolucao.end(); it++){
        
        cout<< *it << ", ";
    }
    cout<< ")" <<endl;
            

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
            ListaFechoDireto.push_back(VerticeAux->getId());//adiciona na lista soluçao
            fechoDiretoAux(verticeAdj->getId(),ListaFechoDireto);//entra novamente na recursao
        }
    }
    return ListaFechoDireto;//volta a lista no final
}