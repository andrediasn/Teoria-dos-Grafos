#include "Grafo.h"

Grafo::Grafo(int ordem, float **coord, bool direcionado, bool pesoArestas, bool pesoVertices ){//construtor do grafo
    this->ordem = ordem;//inicializa a ordem com a ordem passada
    this->direcionado = direcionado;//inicializa o grafo se é direcionado ou nao
    this->pesoArestas = pesoArestas;//inicializa o grafo com peso nas arestas ou nao
    this->pesoVertice = pesoVertices;//inicializa o grafo com peso nos vertices ou nao
    for(int i=1; i<=this->ordem;i++) {//inicializa a lista de vertices do grafo com todos os vertices de 0 a n-1 sendo n a ordem do grafo
        insereVertice(i, coord[i-1][0], coord[i-1][1]);//insere cada vertice do grafo de uma vez (ja que sabemos o numero de nos pela "ordem")
    }
}
Grafo::~Grafo(){}

int Grafo::getOrdem(){
    return this->ordem;
}

void Grafo::insereVertice(int id, float x, float y){// Insere vertice passando id
    if(existeVertice(id))//pesquisa o id do vertice
        cout << "O no jah existe no grafo.\n";//se ja existir printa que ja existe
    else{
    Vertices* no = new Vertices(id, x, y);//aloca um novo no dinamicamente
    nosGrafo.push_back(no);//cria um novo no
    }
}

int Grafo::calculaDist(int id, int id_alvo){
    Vertices* no1 = procurarNo(id);
    Vertices* no2 = procurarNo(id_alvo);
    float valf = pow((no2->getX()-no1->getX()),2)+pow((no2->getY()-no1->getY()),2);
    valf = sqrt(valf);
    int vali = (int)valf;
    float var = fabs(valf - vali);
    if(var >= 0.5)
        vali++;
    return vali;
}

void Grafo::insereAresta(int id, int id_alvo,bool direcionado){// Inseri aresta passando id do vertice de origem, vertice alvo, e o peso
    if(!nosGrafo.empty()){//se o grafo nao for vazio
        Arestas* auxAresta;//cria uma aresta auxiliar
        int peso = calculaDist(id, id_alvo);
        if(direcionado == false){//se ela nao for direcionada
            Vertices* no1 = procurarNo(id);//cria um vertice auxiliar para alterarmos os dados dos vertices
            Vertices* no2 = procurarNo(id_alvo);//cria um auxiliar para o vertice alvo igual ao primeiro
            auxAresta = new Arestas(no1, no2, peso);//declara uma nova aresta
            no1->adicionaAdjacencia(id_alvo);//insere aresta no grafo passando o vertice inicial, final e peso
            no1->adicionarGrauSaida();//adiciona 1 ao grau de saida
            no1->adicionarGrauEntrada();//adiciona grau de entrada, ja que nao é direcionado
            //como nao é um grafo direcionado temos que fazer o mesmo para o vertice 2 tambem para adicionarmos a adjacencia
            //Obs: nao é necessario adicionar uma nova aresta se nao teriamos uma multiaresta
            no2->adicionaAdjacencia(id);//adiciona adjacencia do vertice1 no vertice2
            no2->adicionarGrauEntrada();//adiciona o grau de entrada
            no2->adicionarGrauSaida();//adiciona o grau de saida
            arestasGrafo.push_back(auxAresta);//poe ela na lista de arestas do grafo
                           
        }
    }
}


void Grafo::removeNode(int id){ //remove vertice
    if(existeVertice(id)){//se o vertice nao existe no grafo entra no if
        for (auto i = nosGrafo.begin();i!=nosGrafo.end();i++){//percorre os vertices do grafo 
            Vertices* aux = *i;//cria um vertice auxiliar
            if (aux->getId() == id)//se o id do vertice passado for igual
                nosGrafo.erase(i);//apaga o no do grafo na posiçao i
        }
    }
}

Vertices* Grafo::procurarNo(int id){//pesquisa vertice no grafo e retorna ele
    for (auto i = nosGrafo.begin();i!=nosGrafo.end();i++){//percorre os vertices do grafo 
        Vertices* aux = *i;//cria um vertice auxiliar
        if (aux->getId() == id)//se o id do vertice passado for igual
            return aux;//retorna o vertice
    }
    return nullptr;//se nao, retorna null
}

bool Grafo::existeVertice(int id){//procura se existe aquele vertice
     for (auto i = nosGrafo.begin();i!=nosGrafo.end();i++){//percorre os vertices do grafo 
        Vertices* aux = *i;//cria um auxiliar para conferencia
        if (aux->getId() == id)//se o id do vertice passado for igual
            return true;//retorna que existe o vertice
    }
    return false;//se nao, retorna falso
}

void Grafo::arrumaVisitado(){ // Seta visitados para false
    for(auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
        Vertices* aux = *i;
        aux->setVisitado(false);
    }
}

bool Grafo::conexo(){
    for (auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
        Vertices* auxVertice = *i;
        if(auxVertice->ListAdj.empty() == true)
            return false;
    }
    return true;
}

/*void Grafo::Guloso(){
    vector<Arestas*> arestas;
    arestas.reserve((ordem*(ordem-1))/2);

    for (auto i = this->arestasGrafo.begin(); i != this->arestasGrafo.end();i++)//copia lista de vertices
        arestas.push_back(*i);
    quickSort(&arestas, 0, (((ordem*(ordem-1))/2)-1)); 

    arrumaVisitado();
    Agm* solucao = new Agm;
    for(auto i= arestas.begin(); i != arestas.end(); i++)
    {
        Arestas* auxiliar = *i;
        Vertices* v1 = procurarNo(auxiliar->getId());
        Vertices* v2 = procurarNo(auxiliar->getId_alvo());
        Vertices* Spartida = solucao->retornaVertice(v1->getId());

        if(solucao->nosAgm.empty()){
           solucao->insereAresta(v1,v2,auxiliar);
        }
        else
        {
            if(v1->getVisitado() == false || v2->getVisitado() == false)
            {
                if(Spartida !=nullptr && Spartida->getGrauSaida()<3)
                {
                    solucao->insereAresta(v1->getId(),v2->getId(),auxiliar);
                }
            }
        }
        
    }
}*/

void Grafo::Guloso(string instancia){
    clock_t start, mid, end;
    start = clock();
    vector<Arestas*> arestas;
    arestas.reserve((ordem*(ordem-1))/2);
    
    for (auto i = this->arestasGrafo.begin(); i != this->arestasGrafo.end();i++)//copia lista de vertices
        arestas.push_back(*i);
    quickSort(&arestas, 0, (((ordem*(ordem-1))/2)-1)); 
    mid = clock();
    
    Agm* solucao = new Agm;
    for(auto i= arestas.begin(); i != arestas.end(); i++){
        Arestas* aux = *i;
        Vertices* v1 = aux->getV1();
        Vertices* v2 = aux->getV2();
        if(v1->getGrau() < 3 && v2->getGrau() < 3){
            if(!v1->getVisitado() || !v2->getVisitado()){
                int nv = 0;
                if(v1->getVisitado())
                    nv = 1;
                if(v2->getVisitado())
                    nv = 2;
                solucao->insereAresta(v1->getId(), v2->getId(), nv, aux);
                //aux->addProb();
                v1->setVisitado(true);
                v2->setVisitado(true);
                v1->addGrau();
                v2->addGrau();
            }
            else if (verAciclico(v1->getId(), v2->getId(), solucao)){
                solucao->insereAresta(v1->getId(), v2->getId(), 4, aux);
                v1->setVisitado(true);
                v2->setVisitado(true);
                v1->addGrau();
                v2->addGrau();
            }
        }
    }
    end=clock();
    cout << "Tempo de execucao QuickSort: " << ((float)(mid-start))/1000 << "s\n";
    cout << "Tempo de execucao Guloso: " << ((float)(end-mid))/1000 << "s\n";
    cout << "Tempo de execucao Total: " << ((float)(end-start))/1000 << "s\n";

    solucao->saidaAgmDot();
    solucao->saidaResult(instancia, ((float)(end-start))/1000);
} 


void Grafo::Guloso_v2(string instancia){
    clock_t start, mid, end;
    start = clock();
    vector<Arestas*> arestas;
    arestas.reserve((ordem*(ordem-1))/2);
    
    for (auto i = this->arestasGrafo.begin(); i != this->arestasGrafo.end();i++)//copia lista de vertices
        arestas.push_back(*i);
    quickSort(&arestas, 0, (((ordem*(ordem-1))/2)-1)); 
    mid = clock();
    
    vector<int> conexo;
    for (int i = 0; i < ordem-1; i++) // ao contrario
        conexo[i] = -1;

    int aC = 0;
    int fim = ordem; // até 1

    Agm* solucao = new Agm;
    for(auto i= arestas.begin(); i != arestas.end(); i++){
        Arestas* aux = *i;
        Vertices* v1 = aux->getV1();
        Vertices* v2 = aux->getV2();
        if(v1->getGrau() < 3 && v2->getGrau() < 3){
            if(!v1->getVisitado() || !v2->getVisitado()){
                int nv = 0;
                if(v1->getVisitado())
                    nv = 1;
                else if(v2->getVisitado())
                    nv = 2;
                solucao->insereAresta(v1->getId(), v2->getId(), nv, aux);
                v1->setVisitado(true);
                v2->setVisitado(true);
                v1->addGrau();
                v2->addGrau();
            }
            else if (verAciclico(v1->getId(), v2->getId(), solucao)){
                solucao->insereAresta(v1->getId(), v2->getId(), 4, aux);
                v1->setVisitado(true);
                v2->setVisitado(true);
                v1->addGrau();
                v2->addGrau();
            }
        }
    }
    end=clock();
    cout << "Tempo de execucao QuickSort: " << ((float)(mid-start))/1000 << "s\n";
    cout << "Tempo de execucao Guloso: " << ((float)(end-mid))/1000 << "s\n";
    cout << "Tempo de execucao Total: " << ((float)(end-start))/1000 << "s\n";

    solucao->saidaAgmDot();
    solucao->saidaResult(instancia, ((float)(end-start))/1000);
} 


/*

randomizo nesse range(peso da segunda * alfa)


remove ou seta visitado

10 * 5 = 50

calular media tempo 
desvio padrao 
media
melhor retorna

10

system("./main instacia")


reativo:


reativo chama guloso rand com o alfa (retorna melhor custo)

50

5 = bloco com 1 vez cada alfa

0.3 0.175

bloco de 20

depois de bloco 20 ele recalcula prob de alfa (media de melhores custo daquele alfa salvo no vetor)



*/

void Grafo::quickSort(vector<Arestas*> *copia, int inicio, int fim){ 
    if(inicio < fim){ // Enquanto posicao de inicio nao ultrapassar final
        int p = partQuick(copia, inicio, fim); // Calcula posicao do pivo
        quickSort(copia, inicio, p - 1); // Recursividade da primeira metade do vetor
        quickSort(copia, p, fim); // Recursividade da segunda metade do vetor
    }
}
int Grafo::partQuick(vector<Arestas*> *copia, int esq, int dir){
    int p = esq + (dir - esq) / 2; // indicado do pivo recebe a metade do vetor como posicao
    Arestas* pivo = copia->at(p); // posiciona pivo utilizando ponteiro
    int i = esq; // Posicao percorrida pela esquerda
    int j = dir; // Posicao percorrida pela direita
    while(i<=j) { // Enquanto esquerda nao ultrapassar direita
        while(copia->at(i)->getPeso() < pivo->getPeso())  // Compara peso da aresta de pivo com posicao mais a esquerda
            i++;
        while(copia->at(j)->getPeso() > pivo->getPeso())  // Compara peso da aresta de pivo com posicao mais a direita
            j--;
         if(i <= j) { 
            Arestas *aux = copia->at(i); // auxiliar para fazer a troca
            copia->at(i) = copia->at(j);
            copia->at(j) = aux;
            i++;
            j--;
        }
    }
    return i; // Retorna indice para o pivo
}

bool Grafo::verAciclico(int id, int alvo, Agm *agm){ //Função melhorada
    agm->arrumaVisitado();
    Vertices *vId = agm->retornaVertice(id);
    bool ver = aciclico(vId, alvo, agm);
    return ver;
}

bool Grafo::aciclico(Vertices *v, int alvo, Agm *agm){
    for (auto i = v->ListAdjV.begin(); i != v->ListAdjV.end(); i++){ 
        Vertices* vAdj = *i;
        if(vAdj->getId() == alvo)
            return false;
        if(!vAdj->getVisitado()) {
            vAdj->setVisitado(true);
            if(!aciclico(vAdj, alvo, agm))
                return false;
        }
    }
    return true;//volta a lista no final
} 


