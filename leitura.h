#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>
#include <math.h> 
#include "Grafo.h"
#include "Arestas.h"
#include "Agm.h"

using namespace std;

string arqEntrada;//vai abrir e fechar o arquivo para ler o txt
string arqSaida;//registra em saida o nome do arquivo de saida
bool opc_Direc;// direcionado ou nao 
bool opc_Peso_Aresta;//peso nas arestas ou nao
bool opc_Peso_Nos;//peso nos nos ou nao
Grafo* grafo; // grafo

int menu(){
    int selecao;
    cout << endl;
    cout << "----" << endl;
    cout << "----" << endl;
    cout << "[1] Fecho transitivo direto de um vertice." << endl;
    cout << "[2] Fecho transitivo indireto de um vertice." << endl;
    cout << "[3] Caminho Minimo entre dois vertices - Dijkstra" << endl;
    cout << "[4] Caminho Minimo entre dois vertices - Floyd" << endl;
    cout << "[5] Arvore Geradora Minima de Prim" << endl;
    cout << "[6] Arvore Geradora Minima de Kruskal" << endl;
    cout << "[7] Imprimir caminhamento em Profundidade" << endl;
    cout << "[8] Imprimir ordenacao topologica" << endl;
    cout << "[9] Algoritmo Guloso"<<endl;
    cout << "[10] Algoritmo Guloso Randomizado"<<endl;
    cout << "[11] Algoritmo Guloso Randomizado Reativo"<<endl;
    cout << "[0] Sair" << endl;
    cout << "----" << endl;
    cout << "Opcao escolhida: "; 
    cin >> selecao;
    return selecao;
}

void saidaListDot(list<int> lista, string tipoMetodo){
    ofstream arq(arqSaida, ios::app);
    arq << "//Grafo do caminho minimo do vertice " << *lista.begin() << " ate o vertice " << lista.back(); 
    arq << " gerado pelo algoritimo de " << tipoMetodo << ":" << endl << endl;
    string tipoGrafo;
    string seta;
    if(opc_Direc){
        tipoGrafo = "digraph ";
        seta = " -> ";
    }
    else{
        tipoGrafo = "graph ";
        seta = " -- ";
    }
    int *vert = new int[lista.size()];
    int j = 0;
    for(auto i = lista.begin(); i != lista.end(); i++){
        vert[j] = *i;
        j++;
    }

    arq << tipoGrafo << tipoMetodo << "{" << endl;  // Exemplo: "digraph Floyd{"
    for(int i = 0; i < (lista.size()-1); i++){
        Arestas* aux = grafo->existeAresta(vert[i],vert[i+1]);
        arq << "    " << vert[i] << seta << vert[i+1] << " [label= " << aux->getPeso() << "];"<< endl;
    }
    arq << "}"<< endl << endl << endl;
    delete vert;
}

void saidaAgmDot(Agm* agm, string caminho, int id){
    ofstream arq(arqSaida, ios::app);
    if(id > -1)
        arq << "//Arvore Geradora Minima gerado pelo algoritimo de " << caminho << " com indice " << id << ":" << endl << endl;
    else
        arq << "//Arvore Geradora Minima gerado pelo algoritimo de " << caminho << ":" << endl <<endl;
    
    if(opc_Direc == true){
        arq << "digraph "<< caminho << "{" <<endl;

        for (auto i = agm->arestasAgm.begin(); i != agm->arestasAgm.end(); i++){
            Arestas* aux = *i;
            // Direcionado e com peso nas arestas
            if(opc_Peso_Aresta == true){
                arq << "    " << aux->getId() << " -> " << aux->getId_alvo() << " [label = " << aux->getPeso() << "]" <<endl;
            }
            // Direcionado e sem peso nas arestas
            if(opc_Peso_Aresta == false){
                arq << "    " << aux->getId() << " -> " << aux->getId_alvo() << endl;
            }
        }
    }else{
        arq << "graph "<< caminho << "{" <<endl;

        for (auto i = agm->arestasAgm.begin(); i != agm->arestasAgm.end(); i++){
            Arestas* aux = *i;
            // Ndirecionado e com peso nas arestas
            if(opc_Peso_Aresta == true){
                arq << "    " << aux->getId() << " -- " << aux->getId_alvo() << " [label = " << aux->getPeso() << "]" <<endl;
            }
            // Ndirecionado e sem peso nas arestas
            if(opc_Peso_Aresta == false){
                arq << "    " << aux->getId() << " -- " << aux->getId_alvo() << endl;
            }
        }
            
    }
    arq  << "}" << endl << endl << endl;
    
}

void selecionar(int selecao, Grafo* graph, string saida ){
    switch (selecao) {

        //Fecho transitivo direto de um vertice (1)
        case 1:{
            int IdFecho;
            cout << endl << "Informe o id do Vertice que deseja o fecho transitivo direto: ";
            cin >> IdFecho;
            if(graph->existeVertice(IdFecho))
                list<int> apenasImpressao = graph->fechoDireto(IdFecho);
            else
                cout << "Id do vertice não encontrado." << endl;
            break;
        }
        //Fecho transitivo indireto de um vertice (2)
        case 2:{
            int IdFechoInd;
            cout << endl << "Informe o id do Vertice que deseja o fecho transitivo indireto: ";
            cin >> IdFechoInd;
            if(graph->existeVertice(IdFechoInd))
                list<int> apenasImpressao = graph->fechoIndireto(IdFechoInd);
            else
                cout << "Id do vertice não encontrado." << endl;
            break;
        }

        //Caminho mínimo entre dois vértices usando Dijkstra (3)
        case 3:{
            if(opc_Peso_Aresta){
                int no1, no2;
                cout << endl << "Informe o id do Vertice inicial: ";
                cin >> no1;
                cout << "Informe o id do Vertice alvo: ";
                cin >> no2;
                if(graph->existeVertice(no1) && graph->existeVertice(no2)){
                    list<int> apenasImpressao = graph->caminhoMinimoDijkstra(no1, no2);
                    if(apenasImpressao.size() > 0){
                        saidaListDot(apenasImpressao, "Dijkstra");
                        cout << "Grafo gerado." << endl;
                    }
                } else
                    cout << "Id do vertice não encontrado." << endl;
            } else
                cout << "O grafo nao esta ponderado. Nao eh possivel executar o algoritimo." << endl;
            break;
        }

        //Caminho mínimo entre dois vértices usando Floyd (4)
        case 4:{
            if(opc_Peso_Aresta){
                int no1, no2;
                cout << "Informe o id do Vertice inicial: ";
                cin >> no1;
                cout << "Informe o id do Vertice alvo: ";
                cin >> no2;
                if(graph->existeVertice(no1) && graph->existeVertice(no2))
                    graph->caminhoMinimoFloyd(no1, no2);
                else
                    cout << "Id do vertice não encontrado." << endl;
            } else
                cout << "O grafo nao esta ponderado. Nao eh possivel executar o algoritimo." << endl; 
            break;
        }

        //AGM - Prim; (5)
        case 5:{
            if(!opc_Direc && graph->conexo()){
                int resposta;
                cout << endl << "Informe o id do Vertice inicial da AGM Prim: ";
                cin >> resposta;
                if(graph->existeVertice(resposta)){
                    Agm* agm = graph->arvoreGeradoraMinimaPrim(resposta);
                    saidaAgmDot(agm,"Prim", resposta);
                    cout << endl << "Grafo gerado." << endl;
                } else
                    cout << "Id do vertice não encontrado." << endl;
            } else if(opc_Direc)
                cout << "O grafo esta direcionado. Nao eh possivel executar o algoritimo." << endl;
            else
                cout << "O grafo nao eh conexo. Nao eh possivel executar o algoritimo." << endl;
            break;
        }  
        //AGM - Kruskal; (6)
        case 6:{
            if(!opc_Direc && opc_Peso_Aresta && graph->conexo()){
                Agm* agm = graph->arvoreGeradoraMinimaKruskal();
                saidaAgmDot(agm,"Kruskal", -1);
                cout << endl << "Grafo gerado." << endl;
            } else if(opc_Direc)
                cout << "O grafo esta direcionado. Nao eh possivel executar o algoritimo." << endl;
            else if(!opc_Peso_Aresta)
                cout << "O grafo nao possui peso nas arestas. Nao eh possivel executar o algoritimo." << endl;
            else
                cout << "O grafo nao eh conexo. Nao eh possivel executar o algoritimo." << endl;
            break;
        }

        //Busca em Profundidade; (7)
        case 7:{
            int idNoBusca;
            cout << endl << "Informe o id do Vertice para a Busca em Profundidade: ";
            cin >> idNoBusca;
            if(graph->existeVertice(idNoBusca)){
                Agm* agm = graph->caminhoEmProfundidade(idNoBusca);
                saidaAgmDot(agm,"BuscaProfundidade", idNoBusca);
                cout << "Grafo gerado." << endl;
            }
            else
                cout << "Id do vertice não encontrado." << endl;
            break;
        }
        //Ordenação Topologica; (8)
        case 8:{
            if(opc_Direc)
                graph->ordenacaoTopologica();
            else 
                cout << "O grafo nao esta direcionado. Nao eh possivel executar o algoritimo." << endl;
            break;
        }
         //Algoritmo Guloso; (9)
        case 9:{
            break;
        }
         //Algoritmo Guloso Randomizado; (10)
        case 10:{
            break;
        }
         //Algoritmo Guloso Randomizado Reativo; (11)
        case 11:{
            break;
        }
        //caso 0 sai do programa
        case 0:{
            cout << "Bye bye!" << endl;
            break;
        }
        //opcao invalida
        default:
        {
            cout << " Erro!!! Opcao invalida!!" << endl;
        }

    }
}


Grafo* leitura(int argc, char * argv[]){

    arqEntrada = argv[1]; 
    arqSaida = argv[2]; 
    bool arqTipo = false;//possui exponencial??
    if(arqEntrada[0] == 'd' ||  arqEntrada[0] == 'u')
        arqTipo = true;
    opc_Direc=false; //transformando pra bool
    opc_Peso_Aresta=true; //transformando pra bool
    opc_Peso_Nos=false; //transformando pra bool
   
    ifstream arquivo(arqEntrada);//vai abrir o arquivo (para utilizar desse arquivo usaremos a variavel arquivo)

    if(!arquivo.is_open())//se o arquivo de alguma forma nao for aberto....
    {
        cout<< "Erro ao abrir aquivo, saindo do programa " << arqEntrada << endl;//emite um erro de abrir arquivo, e passa o local que pediu para abrir
        exit(1);//nao retorna nada e volta pra main
    }
    
    //leitura da ordem
    string lixo, strOrdem;
    getline(arquivo,lixo,'\n');
    getline(arquivo,lixo,'\n');
    getline(arquivo,lixo,'\n');
    getline(arquivo,lixo,':');
    getline(arquivo,lixo,' ');
    getline(arquivo,strOrdem,'\n');
    int ordem = stoi(strOrdem);

    float **coord; // Declarando Matriz de coordenadas x e y de cada vertice
    coord = new float *[ordem-1];
    for(int i = 0; i < ordem; i++)
        coord[i] = new float[2];

    getline(arquivo,lixo,'\n');
    getline(arquivo,lixo,'\n');

    int c = 0; //contador para numero do vertice que estamos
    if(!arqTipo){
        while(c < ordem){//repete ate que o contador seja um numero antes da ordem
            string fim, strX, strY;//declarando strings
            getline(arquivo,fim,' ');//testa se chegou em EOF
            if(fim=="EOF"){//se chegou
                cout<< "sai sem barra n"<< endl;
                break;//sai
            }
            if(fim=="EOF\n"){//verificaçao de como vai sair
                cout<< "sai com barra n"<< endl;
                break;
            }
            getline(arquivo,strX,' ');//pega o valor de X
            coord[c][0] = stof(strX);//armazena o valor na matriz com o id do vertice C
            
            getline(arquivo,strY,'\n');//pega o valor de Y
            coord[c][1] = stof(strY);//armazena o valor na matriz com o id do vertice C

            c++;
        }
    }
    else {//se possui exponencial
        while(c < ordem){//repete ate que o contador seja um numero antes da ordem
            string fim, strX, strY;//declarando strings
            getline(arquivo,fim,' ');// pegando as linhas ate o espaço
            if(fim=="EOF"){//se fim for EOF sai
                cout<< "sai sem barra n"<< endl;
                break;
            }
            if(fim=="EOF\n"){// se fim for EOF com barra n sai tambem
                cout<< "sai com barra n"<< endl;
                break;
            }
            getline(arquivo,strX,'e');//anda ate o "e"
            coord[c][0] = stof(strX);//armazena o valor em strX
            getline(arquivo,lixo,'0');//joga fora ate o primeiro 0
            getline(arquivo,strX,' ');//armazena o valor do expoente ate o espaço
            int pot = stoi(strX);//pot recebe string convertida pra inteiro
            coord[c][0] = coord[c][0]*pow(10,pot);//faz a potencia do valor armazenado
            
            getline(arquivo,strY,'e');//analogamente ao de cima
            coord[c][1] = stof(strY);
            getline(arquivo,lixo,'0');
            getline(arquivo,strY,'\n');
            pot = stoi(strY);
            coord[c][1] = coord[c][1]*pow(10,pot);

            c++;//inclui 1 no C
        }
    }

    grafo = new Grafo(ordem, coord, opc_Direc, opc_Peso_Aresta, opc_Peso_Nos);//constroi o grafo baseado no que foi passado no executavel
    int idNo;//variavel para salvar o id do no
    int idNoAlvo;//variavel para salvar o id do no alvo das arestas
    float Peso;// armazena o peso das arestas
    int selecao = 1;//selecao do menu

    /*if(opc_Peso_Nos == 0 && opc_Peso_Aresta == 0 && opc_Direc == 0)//se o grafo nao for direcionado e nao tiver peso
    {
        while(arquivo>>idNo>>idNoAlvo)//le ate a ultima linha do arquivo
        {
            grafo->insereAresta(idNo,idNoAlvo);//insere aresta com ids dos vertices
        }
    }
    else if(opc_Peso_Nos == 0 && opc_Peso_Aresta == 0 && opc_Direc == 1)//se o grafo nao tem peso mas é direcionado
    {   
        while(arquivo>>idNo>>idNoAlvo) //enquanto tiver linha pra ler
        {
            grafo->insereAresta(idNo,idNoAlvo,true);//insere aresta direcionada
        }
    }*/
    if(opc_Peso_Nos == 0 && opc_Peso_Aresta == 1 && opc_Direc == 0)// se o grafo nao é direcionado mas tem peso somente nas arestas
    {
        for (int i=1;i<=ordem;i++){
            for(int j=i+1;j<=ordem;j++){
                grafo->insereAresta(i,j,false);
            }
        }
        cout<< grafo->getOrdem() << " ordem do grafo" <<endl;
        
        /* for(auto i = grafo->nosGrafo.begin(); i != grafo->nosGrafo.end(); i++){
            Vertices* impressao = *i;
            cout << "no: " << impressao->getId() << " X: "<< impressao->getX() << " Y: "<< impressao->getY()<< endl;
        } */
    }
    /*else if(opc_Peso_Nos == 0 && opc_Peso_Aresta == 1 && opc_Direc == 1)// se o grafo é direcionado e tem peso nas arestas
    {
        while (arquivo>>idNo>>idNoAlvo>>Peso)//enquanto tiver linha pra ler
        {
            grafo->insereAresta(idNo,idNoAlvo,true);//insere aresta direcionada com peso nas arestas
        }
        
    }
    else if(opc_Peso_Nos == 1 && opc_Peso_Aresta == 0 && opc_Direc == 0)//o grafo nao é direcionado mas tem peso somente nos vertices
    {
        float PesoVertice1, PesoVerticeAlvo;
        while (arquivo>>idNo>>PesoVertice1>>idNoAlvo>>PesoVerticeAlvo)
        {
            Vertices* no1 = grafo->procurarNo(idNo);//cria um auxiliar para setar o peso dos vertices
            Vertices* no2 = grafo->procurarNo(idNoAlvo);//cria um auxiliar para o vertice 2
            no1->setPeso(PesoVertice1);
            no2->setPeso(PesoVerticeAlvo);
            grafo->insereAresta(idNo,idNoAlvo);
        }
        
        
    }
    else if(opc_Peso_Nos == 1 && opc_Peso_Aresta == 0 && opc_Direc == 1)//o grafo é direcionado e com peso nos vertices
    {
         float PesoVertice1, PesoVerticeAlvo;
        while (arquivo>>idNo>>PesoVertice1>>idNoAlvo>>PesoVerticeAlvo)
        {
            Vertices* no1 = grafo->procurarNo(idNo);//cria um auxiliar para setar o peso dos vertices
            Vertices* no2 = grafo->procurarNo(idNoAlvo);//cria um auxiliar para o vertice 2
            no1->setPeso(PesoVertice1);
            no2->setPeso(PesoVerticeAlvo);
            grafo->insereAresta(idNo,idNoAlvo,true);
        }
    }
    else if(opc_Peso_Nos == 1 && opc_Peso_Aresta == 1 && opc_Direc == 0)// o grafo nao é direcionado mas tem peso nos vertices e arestas
    {
         float PesoVertice1, PesoVerticeAlvo;
        while (arquivo>>idNo>>PesoVertice1>>idNoAlvo>>PesoVerticeAlvo>>Peso)
        {
            Vertices* no1 = grafo->procurarNo(idNo);//cria um auxiliar para setar o peso dos vertices
            Vertices* no2 = grafo->procurarNo(idNoAlvo);//cria um auxiliar para o vertice 2
            no1->setPeso(PesoVertice1);
            no2->setPeso(PesoVerticeAlvo);
            grafo->insereAresta(idNo,idNoAlvo,Peso);
        }
    }
    else if(opc_Peso_Nos == 1 && opc_Peso_Aresta == 1 && opc_Direc == 1)// o grafo é direcionado e com peso nas arestas e vertices
    {
        float PesoVertice1, PesoVerticeAlvo;
        while (arquivo>>idNo>>PesoVertice1>>idNoAlvo>>PesoVerticeAlvo>>Peso)
        {
            Vertices* no1 = grafo->procurarNo(idNo);//cria um auxiliar para setar o peso dos vertices
            Vertices* no2 = grafo->procurarNo(idNoAlvo);//cria um auxiliar para o vertice 2
            no1->setPeso(PesoVertice1);
            no2->setPeso(PesoVerticeAlvo);
            grafo->insereAresta(idNo,idNoAlvo,true);
        }
    }*/

    arquivo.close();

    while(selecao != 0){
       // system("clear");
        selecao = menu();
        
        selecionar(selecao, grafo, argv[2]);
    }
    return grafo;
    
}



