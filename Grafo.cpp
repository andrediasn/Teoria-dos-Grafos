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

void Grafo::ordenaArestas()
{
    for (auto i = this->arestasGrafo.begin(); i != this->arestasGrafo.end();i++)//copia lista de vertices
        this->arestasOrdenadas.push_back(*i);//faz a copia das arestas do grafo
    quickSort(&arestasOrdenadas, 0, (((ordem*(ordem-1))/2)-1));
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

        for (auto i = this->arestasOrdenadas.begin(); i != this->arestasOrdenadas.end();i++)//copia lista de vertices
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
   
    if(alfa < 0.06)
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
void Grafo::atualizaProb(int probAlfa[],int **resultBloco)
{
    double media[5];
    int cont[5];
    double soma = 0;
    for (int i = 0; i < 5; i++)
    {
        cout<<" p: "<<probAlfa[i];
    }
    cout<<endl;

    for(int i = 0; i < 5; i++){
        int j = 0;
        cont[i] = 0;
        media[i] = 0;
        while(resultBloco[i][j] > 0){
            media[i] += resultBloco[i][j];
            cont[i] ++;
            j++;
        }
        media[i] = media[i]/cont[i];
        media[i] = pow(media[i],5);
        media[i] = 1/media[i];
        soma += media[i];
    }
    for(int i = 0; i < 5; i++)
    {
        double aux = media[i]/soma*100;
        int vali = (int)aux;
        float var = fabs(aux - vali);
        if(var >= 0.5)
            vali++;
        probAlfa[i] = vali;
    }
}

float Grafo::escolheAlfa(int probAlfa[], int seed)
{
    srand(seed);
    int k = rand()%100;
    //cout << "rand: " << k << endl;
    if(k < probAlfa[0])
        return 0.05;
    else if(k < probAlfa[0] + probAlfa[1])
        return 0.1;
    else if(k < probAlfa[0] + probAlfa[1] + probAlfa[2])
        return 0.15;
    else if(k < probAlfa[0] + probAlfa[1] + probAlfa[2] + probAlfa[3])
        return 0.3;
    else
        return 0.5;
}

void Grafo::resetBloco(int **resultBloco, int bloco){
    for(int i=0;i<5;i++)
        for(int j=0;j<bloco;j++)
            resultBloco[i][j] = -1;
}

int Grafo::gulosoRandomizadoReativo(int numInter,float tempo[], int bloco, int seed)
{
    clock_t start, end;//criacao de variaveis de tempo
    start = clock();//salva o tempo inicial

    Agm* melhorSolucao;
    Agm* solucao;
    int k,it=0;
    vector<Arestas*> copia;
    
    int **resultBloco;
    resultBloco = new int*[5];
    for(int i=0;i<5;i++)
        resultBloco[i] = new int[bloco];
    resetBloco(resultBloco, bloco);
   
    int probAlfa[5];
    for (int i = 0; i < 5; i++)
    {
        probAlfa[i] = 20;
    }
    
    int pesoMelhorSol = 0;
    while(it<numInter)
    {
        for(int x=0; x<bloco;x++){
            cout << "Iteracao: " << it+1 << endl;
            int conexo[ordem];
            for (int i = 0; i < ordem; i++) 
            {// ao contrario
                conexo[i] = -1;
            }
            int cont = 1;
            copia.clear();
            for (auto i = this->arestasOrdenadas.begin(); i != this->arestasOrdenadas.end(); i++)
            {
                copia.push_back(*i);
            }
            if(it%bloco == 0 && it>5)
            {
                atualizaProb(probAlfa,resultBloco);
                resetBloco(resultBloco, bloco);
            }

            float alfa;
            if(x == 0)
            {
                alfa = 0.05;
            }
            else if(x == 1)
            {
                alfa = 0.1;
            }
            else if(x == 2)
            {
                alfa = 0.15;
            }
            else if(x == 3)
            {
                alfa = 0.3;
            }
            else if(x == 4)
            {
                alfa = 0.5;
            }
            else if(x > 4)
            {
                alfa = escolheAlfa(probAlfa, seed+it+x);
            }
            int faixa = copia[0]->getPeso()*(1+alfa);//obtendo o valor final possivel pra ser escolhido
            faixa ++;
            int range = 0;
            for (int i = 0; i < copia.size(); i++){
                if(copia[i]->getPeso()<=faixa)
                    range = i;
                else
                    break;
            }

            it++;
            arrumaGrau();
            solucao = new Agm();
    
            while (cont < this->ordem && copia.size() > 0)
            {
                srand(seed*it);
                k=rand()%(range+1);
                Arestas* aux = copia.at(k);
                Vertices* v1 = aux->getV1();
                Vertices* v2 = aux->getV2();
                if(v1->getGrau() < 3 && v2->getGrau() < 3)
                {   
                    //cout << "if";
                    if(conexo[v1->getId()] == -1 && conexo[v2->getId()] == -1 )
                    {
                        //cout << "1";
                        solucao->insereAresta(v1->getId(), v2->getId(), 0, aux);
                        v1->addGrau();
                        v2->addGrau();
                        conexo[v1->getId()] = cont;
                        conexo[v2->getId()] = cont;
                        cont ++;
                    }
                    else if(conexo[v1->getId()] == -1)
                    {
                        //cout << "2";
                        solucao->insereAresta(v1->getId(), v2->getId(), 2, aux);
                        v1->addGrau();
                        v2->addGrau();
                        conexo[v1->getId()] = conexo[v2->getId()];
                        cont ++;
                    }
                    else if(conexo[v2->getId()] == -1)
                    {
                        //cout << "3";
                        solucao->insereAresta(v1->getId(), v2->getId(), 1, aux);
                        v1->addGrau();
                        v2->addGrau();
                        conexo[v2->getId()] = conexo[v1->getId()];
                        cont ++;
                    }
                    else if(conexo[v1->getId()] != conexo[v2->getId()])
                    {
                        //cout << "4";
                        solucao->insereAresta(v1->getId(), v2->getId(), 3, aux);
                        v1->addGrau();
                        v2->addGrau();
                        int pesoAux = conexo[v2->getId()];
                        for(int i = 0; i < ordem; i++)
                        {
                            if(conexo[i] == pesoAux)
                                conexo[i] = conexo[v1->getId()];
                        }
                        cont ++;
                    }
                }
                auto removedor = copia.begin() + k;
                copia.erase(removedor);
                range --;
                //cout << "removeu" << endl;
                int auxF = copia[0]->getPeso()*(1+alfa);
                auxF ++;
                if(faixa < auxF) {
                    //cout << "faixa: " << faixa << "auxF: " << auxF << endl;
                    faixa = auxF;
                    for (int i = 0; i < copia.size(); i++){
                        if(copia[i]->getPeso()<=faixa){
                            range = i;
                            if(range >= copia.size())
                                range = copia.size()-1;
                        }
                        else
                            break;
                    }
                }
            }
            int pesoSol = solucao->calculaPesoTotal();
            //cout<<"Sol: "<< pesoSol << endl;
            
            if(it == 1)
            {   
                melhorSolucao = solucao;
                pesoMelhorSol = pesoSol;
            }
            else if(pesoSol < pesoMelhorSol){
                melhorSolucao = solucao; // agm
                pesoMelhorSol = pesoSol; // pesos
            }
            cout<<"Best: "<< pesoMelhorSol << endl;
            int limB = (numInter*0.75)+1;
            if(it < limB){
                if(alfa < 0.06){
                    //cout<<"escolhi alfa 0.05"<<endl;
                    for(int i=0; i<bloco; i++){
                        if(resultBloco[0][i] < 0){
                            resultBloco[0][i] = pesoSol;
                            break;
                        }
                    }
                }
                else if(alfa < 0.11){
                    //cout<<"escolhi alfa 0.10"<<endl;
                    for(int i=0; i<bloco; i++){
                        if(resultBloco[1][i] < 0){
                            resultBloco[1][i] = pesoSol;
                            break;
                        }
                    }
                }
                else if(alfa < 0.16){
                    //cout<<"escolhi alfa 0.15"<<endl;
                    for(int i=0; i<bloco; i++){
                        if(resultBloco[2][i] < 0){
                            resultBloco[2][i] = pesoSol;
                            break;
                        }
                    }
                }
                else if(alfa < 0.31){
                    //cout<<"escolhi alfa 0.30"<<endl;
                    for(int i=0; i<bloco; i++){
                        if(resultBloco[3][i] < 0){
                            resultBloco[3][i] = pesoSol;
                            break;
                        }
                    }
                }
                else if(alfa < 0.51){
                    //cout<<"escolhi alfa 0.50"<<endl;
                    for(int i=0; i<bloco; i++){
                        if(resultBloco[4][i] < 0){
                            resultBloco[4][i] = pesoSol;
                            break;
                        }
                    }
                }
            }
        }
    }

    end=clock();

    cout << "Tempo de execucao: " <<((float)(end-start))/1000 << "s\n" << endl;   
   
       //melhorSolucao->saidaAgmDot();
    return pesoMelhorSol;
}