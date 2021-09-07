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
        if(!existeVertice(id)){//se nao existir o no no grafo
            cout << "O vertice de origem nao existe no grafo.\n";//printa que nao tem vertice
            return;//e volta
        }else if(!existeVertice(id_alvo)){//se nao existir o vertice alvo
            cout << id_alvo <<"  vertice de destino nao existe no grafo.\n";//printa que nao existe
            return;//e volta
        }
        else{//caso tenha os 2
            Arestas* auxAresta;//cria uma aresta auxiliar
            int peso = calculaDist(id, id_alvo);
            if(direcionado == false){//se ela nao for direcionada
                Vertices* no1 = procurarNo(id);//cria um vertice auxiliar para alterarmos os dados dos vertices
                Vertices* no2 = procurarNo(id_alvo);//cria um auxiliar para o vertice alvo igual ao primeiro
                auxAresta = new Arestas(id, id_alvo, peso);//declara uma nova aresta
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
            /* else if(direcionado == true){//se for direcionada
                Vertices* no1 = procurarNo(id);//cria um vertice auxiliar para alterarmos os dados dos vertices
                Vertices* no2 = procurarNo(id_alvo);//cria um auxiliar para o vertice alvo igual ao primeiro
                //adicionando peso nos vertices
                auxAresta = no1->insereAresta(id, id_alvo, pesoArestas);//insere aresta no grafo passando o vertice inicial, final e peso
                no1->adicionarGrauSaida();//adiciona 1 ao grau de saida
                no2->adicionarGrauEntrada();//adiciona o grau de entrada
                arestasGrafo.push_back(auxAresta);//poe ela na lista de arestas do grafo
                no2->adicionaAntecessor(no1->getId());
            } */
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

Arestas* Grafo::existeAresta(int id ,int id_alvo){ // FUNCAO PARA ACHAR UMA ARESTA DADO DOIS VERTICES
    for (auto i = arestasGrafo.begin(); i != arestasGrafo.end(); i++){
        Arestas* verificador = *i;
        if(verificador->getId() == id && verificador->getId_alvo() == id_alvo){
            return verificador;
        }
    }
    cout << "Nao existe essa aresta no grafo." << endl;
    return NULL;
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

// FUNCAO PARA ACHAR A MENOR ARESTA DENTRE DOIS NOS 
/* Agm* Grafo::arestaMaisBarata(Vertices* v,Agm* agm){
    int menor = INT_MAX/2; 
    
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
    Vertices* aux = procurarNo(v);

    Agm *agm = new Agm();             // Criando o conjunto solucao das arestas com menor peso 
    agm = arestaMaisBarata(aux,agm);// Procurar dentre todos os vizinhos do vertice inicial qual tem aresta com menor peso 
     
    // Percorrendo a lista de adj ate achar o mais barato
    arrumaVisitado();
    return agm;
} */


/* list<int> Grafo::fechoDireto(int ID){
    list<int> listaSolucao;//cria uma lista de soluçao
    Vertices *aux = procurarNo(ID);
    if(this->direcionado == false){
        cout<< "Esse grafo nao eh direcionado, portanto, nao contem fecho transitivo direto"<< endl;
    }
    else if(aux->getGrauSaida() == 0){
        cout << "Vertice nao possue fecho transitivo direto." << endl;
    }
    else
    {
        listaSolucao = fechoDiretoAux(ID,listaSolucao);//chama a funçao auxiliar para fazer de modo recursivo
        list<int>::iterator it;
        cout << endl << "Os vertices que sao alcansaveis a partir do "<< ID << " sao: " << endl;
        for ( it = listaSolucao.begin(); it != listaSolucao.end(); it++){
            
            cout<< *it << " ";
        }
        cout << endl;
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
} */

/* list<int> Grafo::fechoIndireto(int ID){
    list<int> solucao;
    Vertices* aux = procurarNo(ID);
    if(this->direcionado == false){
        cout << "Esse grafo nao eh direcionado, portanto, nao contem fecho transitivo indireto"<< endl;
    }
    else if(aux->getGrauEntrada() == 0){
        cout << "Vertice nao possue fecho transitivo indireto." << endl;
    }
    else {
        for(auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
            Vertices* aux = *i;
            aux->setVisitado(false);
        }

        solucao = fechoIndiretoAux(ID, solucao);
        cout<< endl << "Os vertices que alcansao o vertice "<< ID << " sao: " << endl;
        for (auto i = solucao.begin(); i!=solucao.end(); i++){
            cout << *i << " ";
        }
        cout << endl;
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
} */


/* Agm* Grafo::caminhoEmProfundidade(int id){
    Agm* solucao = new Agm();
    int ultimo = -1;
    for(auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
        Vertices* aux = *i;
        aux->setVisitado(false);
    }
    ultimo = caminhoEmProfundidadeAux(solucao, id, ultimo);
    return solucao;
}
int Grafo::caminhoEmProfundidadeAux(Agm* solucao, int id, int ultimo){
    Vertices* inicial = procurarNo(id);
    solucao->insereVertice(inicial);
    inicial->setVisitado(true);
    int aux;
    for (auto i = inicial->ListAdj.begin(); i != inicial->ListAdj.end(); i++) {
        aux = *i;
        if(i != inicial->ListAdj.begin() && ultimo != -1){
            Arestas *peso = existeAresta(inicial->getId(), ultimo);
            Arestas* retorno = new Arestas(ultimo, inicial->getId(), peso->getPeso());
            solucao->insereAresta(retorno);
            ultimo = -1;
        }
        Vertices* vVisitado = procurarNo(aux);
        if(!vVisitado->getVisitado()){
            ultimo = caminhoEmProfundidadeAux(solucao, aux, ultimo);
        }
    }
    ultimo = inicial->getId();
    return ultimo;
} */

/* Agm* Grafo::arvoreGeradoraMinimaKruskal(){
    Agm *agm = new Agm();             // Criando o conjunto solucao das arestas com menor peso
    vector<Arestas*> arestasAux;      // Criando vetor que guarda as arestas
    int *ciclo;
    ciclo = new int [arestasGrafo.size()];
    
    // Atribuindo as arestas do grafo no vetor que sera ordenado 
    for (auto  i = arestasGrafo.begin(); i != arestasGrafo.end(); i++){    
        Arestas* auxs = *i;
        arestasAux.push_back(auxs);
    }    
   
    Arestas* aux = NULL;   

    // Ordenar as arestas conforme o peso
    for(int i  = arestasAux.size() - 1 ;i >= 0 ;i--){
        for(int j = 0;j < i;j++){
            if(arestasAux[j]->getPeso() > arestasAux[j+1]->getPeso()){
                aux = arestasAux[j];
                arestasAux[j] = arestasAux[j + 1];
                arestasAux[j + 1] = aux;    
            }
        }
    }
     
    for (int i = 0;i < arestasAux.size();i++){
        ciclo[i] = i;
    }
    
    
    for (auto  i = arestasAux.begin(); i != arestasAux.end(); i++){
        Arestas*  j       = *i;
        // Detectando se com esta aresta forma ciclo:
		if ( pai(j->getId(), ciclo) != pai(j->getId_alvo(), ciclo)){ 
			unir(j->getId(), j->getId_alvo(), ciclo);

            agm->insereAresta(j);       // Insere aresta na arvore agm 
		}
    
    }
    delete[] ciclo;
    return agm;
  
}

// Funcao que uni o pai de dois vertices no ciclo para descobrir se forma ciclo
void Grafo::unir(int v1,int v2, int *ciclo){
    ciclo[pai(v1, ciclo)] = pai(v2, ciclo);
}

int Grafo::pai(int v, int *ciclo){
     if (ciclo[v] == v){
        return v;
	}
 
    ciclo[v] = pai(ciclo[v], ciclo);
 
    return ciclo[v];
} */



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
    int cp = 0;
    int p = arestas.size()/5;
    cout << "Executando [0%";
    for(auto i= arestas.begin(); i != arestas.end(); i++){
        Arestas* aux = *i;
        Vertices* v1 = procurarNo(aux->getId());
        Vertices* v2 = procurarNo(aux->getId_alvo());
        if(v1->getGrau() < 3 && v2->getGrau() < 3){
            if(!v1->getVisitado() || !v2->getVisitado()){
                int nv = 0;
                if(v1->getVisitado())
                    nv = 1;
                if(v2->getVisitado())
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
        if(cp == p)
            cout << " - 20%";
        else if(cp == 2*p)
            cout << " - 40%";
        else if(cp == 3*p)
            cout << " - 60%";
        else if(cp == 4*p)
            cout << " - 80%";

    }
    cout << " - 100%]" << endl << endl;
    end=clock();
    cout << "Tempo de execucao QuickSort: " << ((float)(mid-start))/1000 << "s\n";
    cout << "Tempo de execucao Guloso: " << ((float)(end-mid))/1000 << "s\n";
    cout << "Tempo de execucao Total: " << ((float)(end-start))/1000 << "s\n";

    solucao->saidaAgmDot();
    solucao->saidaResult(instancia, ((float)(end-start))/1000);
} 

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

/* bool Grafo::verAciclico(int id, int alvo, Agm *agm){
    agm->arrumaVisitado();
    bool ver = aciclico(id, alvo, agm);
    return ver;
}

bool Grafo::aciclico(int id, int alvo, Agm *agm){ // Para melhorar, alterar pra que o id ja seja o vertice
    Vertices *v = agm->retornaVertice(id);
    for (auto i = v->ListAdj.begin(); i != v->ListAdj.end(); i++){ // Para melhorar, alterar pra a lista ja ser de vertices.
        if(*i == alvo)
            return false;
        Vertices* vAdj = agm->retornaVertice(*i); // Para melhorar, alterar pra a lista ja ser de vertices.
        if(!vAdj->getVisitado()) {
            vAdj->setVisitado(true);
            if(!aciclico(*i, alvo, agm))
                return false;
        }
    }
    return true;//volta a lista no final
} */


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