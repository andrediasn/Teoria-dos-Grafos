#include "Grafo.h"

Grafo::Grafo(int ordem, float **coord, bool direcionado, bool pesoArestas, bool pesoVertices ){//construtor do grafo
    this->ordem = ordem;//inicializa a ordem com a ordem passada
    this->direcionado = direcionado;//inicializa o grafo se é direcionado ou nao
    this->pesoArestas = pesoArestas;//inicializa o grafo com peso nas arestas ou nao
    this->pesoVertice = pesoVertices;//inicializa o grafo com peso nos vertices ou nao
    for(int i=0; i<this->ordem;i++) {//inicializa a lista de vertices do grafo com todos os vertices de 0 a n-1 sendo n a ordem do grafo
        insereVertice(i, coord[i][0], coord[i][1]);//insere cada vertice do grafo de uma vez (ja que sabemos o numero de nos pela "ordem")
    }
}
Grafo::~Grafo(){}

int Grafo::getOrdem(){
    return this->ordem;
}

void Grafo::insereVertice(int id, float x, float y){// Insere vertice passando id
    Vertices* no = new Vertices(id, x, y);//aloca um novo no dinamicamente
    nosGrafo.push_back(no);//cria um novo no
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

void Grafo::arrumaGrau(){ // Seta visitados para false
    for(auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
        Vertices* aux = *i;
        aux->setGrau(0);
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

void Grafo::Guloso(string instancia){

    clock_t start, mid, end;
    start = clock();
    vector<Arestas*> arestas;
    arestas.reserve((ordem*(ordem-1))/2);
    
    for (auto i = this->arestasGrafo.begin(); i != this->arestasGrafo.end();i++)//copia lista de vertices
        arestas.push_back(*i);
    quickSort(&arestas, 0, (((ordem*(ordem-1))/2)-1)); 
    mid = clock();

    int conexo[ordem];
    for (int i = 0; i < ordem; i++) // ao contrario
        conexo[i] = -1;
  
    int cont = 1;

    Agm* solucao = new Agm;
    for(auto i= arestas.begin(); i != arestas.end(); i++){
        if(cont == this->ordem)
            break;

        Arestas* aux = *i;
        Vertices* v1 = aux->getV1();
        Vertices* v2 = aux->getV2();
        if(v1->getGrau() < 3 && v2->getGrau() < 3){       
            if(conexo[v1->getId()] == -1 && conexo[v2->getId()] == -1 ){
                solucao->insereAresta(v1->getId(), v2->getId(), 0, aux);
                v1->addGrau();
                v2->addGrau();
                conexo[v1->getId()] = cont;
                conexo[v2->getId()] = cont;
                cont ++;
            }
            else if(conexo[v1->getId()] == -1){
                solucao->insereAresta(v1->getId(), v2->getId(), 2, aux);
                v1->addGrau();
                v2->addGrau();
                conexo[v1->getId()] = conexo[v2->getId()];
                cont ++;
            }
            else if(conexo[v2->getId()] == -1){
                solucao->insereAresta(v1->getId(), v2->getId(), 1, aux);
                v1->addGrau();
                v2->addGrau();
                conexo[v2->getId()] = conexo[v1->getId()];
                cont ++;
            }
            else if(conexo[v1->getId()] != conexo[v2->getId()]){
                solucao->insereAresta(v1->getId(), v2->getId(), 3, aux);
                v1->addGrau();
                v2->addGrau();
                int pesoAux = conexo[v2->getId()];
                for(int i = 0; i < ordem; i++){
                    if(conexo[i] == pesoAux)
                        conexo[i] = conexo[v1->getId()];
                }
                cont ++;
            }
        }
    }
    end=clock();
    cout << "Tempo de execucao Total: " << ((float)(end-start))/1000 << "s\n";

    solucao->saidaAgmDot();
    solucao->saidaResult(instancia, ((float)(end-start))/1000);
} 

int Grafo::gulosoRandomizado(float alfa, int numInter, float* tempo, int seed){
    clock_t start, end;//criacao de variaveis de tempo
    start = clock();//salva o tempo inicial
    vector<Arestas*> arestasOrdenadas;//cria vetor de arestas para ordenar
    arestasOrdenadas.reserve((ordem*(ordem-1))/2);//reserva o espaço de memoria para o vetor

    for (auto i = this->arestasGrafo.begin(); i != this->arestasGrafo.end();i++)//copia lista de vertices
        arestasOrdenadas.push_back(*i);//faz a copia das arestas do grafo
    quickSort(&arestasOrdenadas, 0, (((ordem*(ordem-1))/2)-1)); //ordena pelo quicksort

    Agm* solucao = new Agm();//declara a agm soluçao
    Agm* melhorSolucao = new Agm();//declara a agm soluçao


    int k,it = 0;//contador de indice
    int pesoMelhorSol = 0;
    while (it<numInter) {   
        //cout << "Iteracao: " << it+1 << endl;
        int conexo[ordem];
        for (int i = 0; i < ordem; i++) {// ao contrario
            conexo[i] = -1;
        }
        int cont = 1;

        vector<Arestas*> arestas;
        //arestas.reserve((ordem*(ordem-1))/2);

        for (auto i = arestasOrdenadas.begin(); i != arestasOrdenadas.end();i++)//copia lista de vertices
            arestas.push_back(*i);

        int faixa = arestas[0]->getPeso()*(1+alfa);//obtendo o valor final possivel pra ser escolhido
        faixa ++;
        int range = 0;
        for (int i = 0; i < arestas.size(); i++){
            if(arestas[i]->getPeso()<=faixa)
                range = i;
            else
                break;
        }
        
        solucao = new Agm();
        
        while(cont < this->ordem && arestas.size() > 0){ 
            //cout << "Cont: " << cont << " Range: "<< range;
            srand(it*seed);
            k=rand()%(range+1);
            //cout << " Rand: " << k << " Peso: " << arestas[k]->getPeso() << " Faixa: " << faixa << endl;
            Arestas* aux = arestas[k];
            Vertices* v1 = aux->getV1();
            Vertices* v2 = aux->getV2();
            if(v1->getGrau() < 3 && v2->getGrau() < 3){   
                //cout << "if";
                if(conexo[v1->getId()] == -1 && conexo[v2->getId()] == -1 ){
                    //cout << "1";
                    solucao->insereAresta(v1->getId(), v2->getId(), 0, aux);
                    v1->addGrau();
                    v2->addGrau();
                    conexo[v1->getId()] = cont;
                    conexo[v2->getId()] = cont;
                    cont ++;
                }
                else if(conexo[v1->getId()] == -1){
                    //cout << "2";
                    solucao->insereAresta(v1->getId(), v2->getId(), 2, aux);
                    v1->addGrau();
                    v2->addGrau();
                    conexo[v1->getId()] = conexo[v2->getId()];
                    cont ++;
                }
                else if(conexo[v2->getId()] == -1){
                    //cout << "3";
                    solucao->insereAresta(v1->getId(), v2->getId(), 1, aux);
                    v1->addGrau();
                    v2->addGrau();
                    conexo[v2->getId()] = conexo[v1->getId()];
                    cont ++;
                }
                else if(conexo[v1->getId()] != conexo[v2->getId()]){
                    //cout << "4";
                    solucao->insereAresta(v1->getId(), v2->getId(), 3, aux);
                    v1->addGrau();
                    v2->addGrau();
                    int pesoAux = conexo[v2->getId()];
                    for(int i = 0; i < ordem; i++){
                        if(conexo[i] == pesoAux)
                            conexo[i] = conexo[v1->getId()];
                    }
                    cont ++;
                }
                //cout << "out" << endl;
            }
            //cout << "size: " << arestas.size() << endl;
            auto removedor = arestas.begin() + k;
            arestas.erase(removedor);
            
            range --;
            //cout << "removeu" << endl;
            int auxF = arestas[0]->getPeso()*(1+alfa);
            auxF ++;
            if(faixa < auxF) {
                //cout << "faixa: " << faixa << "auxF: " << auxF << endl;
                faixa = auxF;
                for (int i = 0; i < arestas.size(); i++){
                    if(arestas[i]->getPeso()<=faixa){
                        range = i;
                        if(range >= arestas.size())
                            range = arestas.size()-1;
                    }
                    else
                        break;
                }
            }
        }
        int pesoSol = solucao->calculaPesoTotal();
        if(it == 0)
        {   
            melhorSolucao = solucao;
            pesoMelhorSol = pesoSol;
            //solucao->saidaAgmDot();
        }
        else if(pesoSol < pesoMelhorSol){
            melhorSolucao = solucao;
            pesoMelhorSol = pesoSol;
            //solucao->saidaAgmDot();
        }
        //cout << "Resultado: " << pesoSol << " Arestas: " << cont-1 << endl;
        arrumaGrau();
        it++;
        end=clock();
        cout << "It: " << it << " Temp: " <<((float)(end-start))/1000 << "s" << endl;
        cout << "Sol= " << pesoSol << " MSol: " << pesoMelhorSol << endl << endl;  
    }
    end=clock();

    cout << "Melhor solucao: " << melhorSolucao->calculaPesoTotal() << endl;
    cout << "Tempo de execucao: " <<((float)(end-start))/1000 << "s\n" << endl;   
   
    if(alfa < 0.06f)
        tempo[0] = ((float)(end-start))/1000;
    else if(alfa < 0.11)
        tempo[1] = ((float)(end-start))/1000;
    else if(alfa < 0.16)
        tempo[2] = ((float)(end-start))/1000;
    else if(alfa < 0.31)
        tempo[3] = ((float)(end-start))/1000;
    else if(alfa < 0.51)
        tempo[4] = ((float)(end-start))/1000;

    melhorSolucao->saidaAgmDot();
    return melhorSolucao->calculaPesoTotal();
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

/* 
int Grafo::gulosoRandomizado(float alfa, int numInter, float* tempo, int seed){
    clock_t start, end;//criacao de variaveis de tempo
    start = clock();//salva o tempo inicial
    vector<Arestas*> arestasOrdenadas;//cria vetor de arestas para ordenar
    arestasOrdenadas.reserve((ordem*(ordem-1))/2);//reserva o espaço de memoria para o vetor

    for (auto i = this->arestasGrafo.begin(); i != this->arestasGrafo.end();i++)//copia lista de vertices
        arestasOrdenadas.push_back(*i);//faz a copia das arestas do grafo
    quickSort(&arestasOrdenadas, 0, (((ordem*(ordem-1))/2)-1)); //ordena pelo quicksort

    Agm* solucao = new Agm();//declara a agm soluçao
    Agm* melhorSolucao = new Agm();//declara a agm soluçao


    int k,it = 0;//contador de indice
    while (it<numInter) {   
        //cout << "Iteracao: " << it+1 << endl;
        int conexo[ordem];
        for (int i = 0; i < ordem; i++) {// ao contrario
            conexo[i] = -1;
        }
        int cont = 1;

        vector<Arestas*> arestas;
        //arestas.reserve((ordem*(ordem-1))/2);

        //for (auto i = arestasOrdenadas.begin(); i != arestasOrdenadas.end();i++)//copia lista de vertices
        //    arestas.push_back(*i);

        int faixa = arestas[0]->getPeso()*(1+alfa);//obtendo o valor final possivel pra ser escolhido
        faixa ++;

        int range = 0;
        for (int i = range; i < arestasOrdenadas.size(); i++){
            if(arestas[i]->getPeso()<=faixa){
                range = i;
                arestas.push_back(arestasOrdenadas[i]);
            }
            else
                break;
        }
        
        solucao = new Agm();
        while(cont < this->ordem && arestas.size() > 0){ 
            //cout << "Cont: " << cont << " Range: "<< range;
            srand(it*seed);
            k=rand()%(arestas.size());
            //cout << " Rand: " << k << " Peso: " << arestas[k]->getPeso() << " Faixa: " << faixa << endl;
            Arestas* aux = arestas[k];
            Vertices* v1 = aux->getV1();
            Vertices* v2 = aux->getV2();
            if(v1->getGrau() < 3 && v2->getGrau() < 3){   
                //cout << "if";
                if(conexo[v1->getId()] == -1 && conexo[v2->getId()] == -1 ){
                    //cout << "1";
                    solucao->insereAresta(v1->getId(), v2->getId(), 0, aux);
                    v1->addGrau();
                    v2->addGrau();
                    conexo[v1->getId()] = cont;
                    conexo[v2->getId()] = cont;
                    cont ++;
                }
                else if(conexo[v1->getId()] == -1){
                    //cout << "2";
                    solucao->insereAresta(v1->getId(), v2->getId(), 2, aux);
                    v1->addGrau();
                    v2->addGrau();
                    conexo[v1->getId()] = conexo[v2->getId()];
                    cont ++;
                }
                else if(conexo[v2->getId()] == -1){
                    //cout << "3";
                    solucao->insereAresta(v1->getId(), v2->getId(), 1, aux);
                    v1->addGrau();
                    v2->addGrau();
                    conexo[v2->getId()] = conexo[v1->getId()];
                    cont ++;
                }
                else if(conexo[v1->getId()] != conexo[v2->getId()]){
                    //cout << "4";
                    solucao->insereAresta(v1->getId(), v2->getId(), 3, aux);
                    v1->addGrau();
                    v2->addGrau();
                    int pesoAux = conexo[v2->getId()];
                    for(int i = 0; i < ordem; i++){
                        if(conexo[i] == pesoAux)
                            conexo[i] = conexo[v1->getId()];
                    }
                    cont ++;
                }
                //cout << "out" << endl;
            }
            //cout << "size: " << arestas.size() << endl;
            auto removedor = arestas.begin() + k;
            arestas.erase(removedor);
            //cout << "removeu" << endl;

            int auxF = arestas[0]->getPeso()*(1+alfa);
            auxF ++;
            if(faixa < auxF) {
                //cout << "faixa: " << faixa << "auxF: " << auxF << endl;
                faixa = auxF;
                for (int i = range; i < arestasOrdenadas.size(); i++){
                    if(arestas[i]->getPeso()<=faixa){
                        range = i;
                        arestas.push_back(arestasOrdenadas[i]);
                    }
                    else
                        break;
                }
            }
        }
        int pesoSol = solucao->calculaPesoTotal();
        if(it == 0)
        {   
            melhorSolucao = solucao;
            //solucao->saidaAgmDot();
        }
        else if(pesoSol < melhorSolucao->calculaPesoTotal()){
            melhorSolucao = solucao;
            //solucao->saidaAgmDot();
        }
        //cout << "Resultado: " << pesoSol << " Arestas: " << cont-1 << endl;
        arrumaGrau();
        it++;
    }
    end=clock();

    cout << "Melhor solucao: " << melhorSolucao->calculaPesoTotal() << endl;
    cout << "Tempo de execucao: " <<((float)(end-start))/1000 << "s\n" << endl;   
   
    if(alfa < 0.06f)
        tempo[0] = ((float)(end-start))/1000;
    else if(alfa < 0.11)
        tempo[1] = ((float)(end-start))/1000;
    else if(alfa < 0.16)
        tempo[2] = ((float)(end-start))/1000;
    else if(alfa < 0.31)
        tempo[3] = ((float)(end-start))/1000;
    else if(alfa < 0.51)
        tempo[4] = ((float)(end-start))/1000;

    melhorSolucao->saidaAgmDot();
    return melhorSolucao->calculaPesoTotal();
}
 */