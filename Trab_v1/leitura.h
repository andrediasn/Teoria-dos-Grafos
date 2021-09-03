#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
#include "Grafo.h"
#include "Arestas.h"
#include "Agm.h"

std::string arqEntrada;//vai abrir e fechar o arquivo para ler o txt
std::string arqSaida;//registra em saida o nome do arquivo de saida
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
    cout << "[0] Sair" << endl;
    cout << "----" << endl;
    cout << "Opcao escolhida: "; 
    cin >> selecao;
    return selecao;
}

void saidaListDot(list<int> lista, string tipoMetodo){
    std::ofstream arq(arqSaida, ios::app);
    arq << "//Grafo do caminho minimo do vertice " << *lista.begin() << " ate o vertice " << lista.back(); 
    arq << " gerado pelo algoritimo de " << tipoMetodo << ":" << endl << endl;
    std::string tipoGrafo;
    std::string seta;
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
        case 0:{
            cout << "Bye bye!" << endl;
            break;
        }
        default:
        {
            cout << " Erro!!! Opcao invalida!!" << endl;
        }

    }
}


Grafo* leitura(int argc, char * argv[]){

    arqEntrada = argv[1]; 
    arqSaida = argv[2]; 
    std::istringstream(argv[3])>>opc_Direc; //transformando pra bool
    std::istringstream(argv[4])>>opc_Peso_Aresta; //transformando pra bool
    std::istringstream(argv[5])>>opc_Peso_Nos; //transformando pra bool
   
    std::ifstream arquivo(arqEntrada);//vai abrir o arquivo (para utilizar desse arquivo usaremos a variavel arquivo)

    if(!arquivo.is_open())//se o arquivo de alguma forma nao for aberto....
    {
        std::cout<< "Erro ao abrir aquivo, saindo do programa " << arqEntrada << std::endl;//emite um erro de abrir arquivo, e passa o local que pediu para abrir
        exit(1);//nao retorna nada e volta pra main
    }
    

    int ordem;//declara uma variavel ordem 
    arquivo >> ordem;//adiciona a primeira linha do arquivo na ordem (ordem recebe a primeira linha do arquivo)
    grafo = new Grafo(ordem, opc_Direc, opc_Peso_Aresta, opc_Peso_Nos);//constroi o grafo baseado no que foi passado no executavel
    int idNo;//variavel para salvar o id do no
    int idNoAlvo;//variavel para salvar o id do no alvo das arestas
    float Peso;// armazena o peso das arestas
    int selecao = 1;//selecao do menu

    if(opc_Peso_Nos == 0 && opc_Peso_Aresta == 0 && opc_Direc == 0)//se o grafo nao for direcionado e nao tiver peso
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
    }
    else if(opc_Peso_Nos == 0 && opc_Peso_Aresta == 1 && opc_Direc == 0)// se o grafo nao é direcionado mas tem peso somente nas arestas
    {
        while(arquivo>>idNo>>idNoAlvo>>Peso)//enquanto tiver linha pra ler
        {
            
            grafo->insereAresta(idNo,idNoAlvo,false,Peso);//insere aresta com id e peso nas arestas
        }
    }
    else if(opc_Peso_Nos == 0 && opc_Peso_Aresta == 1 && opc_Direc == 1)// se o grafo é direcionado e tem peso nas arestas
    {
        while (arquivo>>idNo>>idNoAlvo>>Peso)//enquanto tiver linha pra ler
        {
            grafo->insereAresta(idNo,idNoAlvo,true,Peso);//insere aresta direcionada com peso nas arestas
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
            grafo->insereAresta(idNo,idNoAlvo,true,Peso);
        }
    }

    arquivo.close();

    while(selecao != 0){
       // system("clear");
        selecao = menu();
        
        selecionar(selecao, grafo, argv[2]);
    }
    return grafo;
    
}



