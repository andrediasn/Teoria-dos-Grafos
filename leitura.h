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
    cout << "[1] Algoritmo Guloso"<<endl;
    cout << "[2] Algoritmo Guloso Randomizado"<<endl;
    cout << "[3] Algoritmo Guloso Randomizado Reativo"<<endl;
    cout << "[0] Sair" << endl;
    cout << "----" << endl;
    cout << "Opcao escolhida: "; 
    cin >> selecao;
    return selecao;
}

void selecionar(int selecao, Grafo* graph, string instancia ){
    switch (selecao) {

         //Algoritmo Guloso;
        case 1:{
            graph->Guloso(instancia);
            break;
        }
         //Algoritmo Guloso Randomizado;
        case 2:{
            for(int i=0; i<10; i++) { // apagar isso antes q o stenio viado veja
                cout << " => Execucao: " << i+1 << endl;
                int alfa1,alfa2,alfa3,alfa4,alfa5;
                float *tempo = new float[5];
                int max = 500;
                int seed = i+10;
                //cout << "jogue aqui a sua semente: ";
                //cin >> seed;
                // alfas 0.05 0.1 0.15 0.3 0.5
                //melhor resultado 0.05 
                cout << "Executando alfa 0.05" << endl;
                alfa1 = graph->gulosoRandomizado(0.05, max, tempo, seed+1);
                //melhor resultado 0.10
                cout << "Executando alfa 0.1" << endl;
                alfa2 = graph->gulosoRandomizado(0.1, max, tempo, seed+2);
                //melhor resultado 0.15 
                cout << "Executando alfa 0.15" << endl;
                alfa3 = graph->gulosoRandomizado(0.15, max, tempo, seed+3);
                //melhor resultado 0.30 
                cout << "Executando alfa 0.3" << endl;
                alfa4 = graph->gulosoRandomizado(0.30, max, tempo, seed+4);
                //melhor resultado 0.50
                cout << "Executando alfa 0.5" << endl;
                alfa5 = graph->gulosoRandomizado(0.50, max, tempo, seed-5);

                ofstream arq("Resultado/resultGulosoRand.txt", ios::app);
                arq << instancia << ";"<< alfa1 << ";" << tempo[0] << ";"; 
                arq << alfa2 << ";" << tempo[1] << ";"; 
                arq << alfa3 << ";" << tempo[2] << ";"; 
                arq << alfa4 << ";" << tempo[3] << ";";
                arq << alfa5 << ";" << tempo[4] << endl;
                arq.close();
            }
            break;
        }
         //Algoritmo Guloso Randomizado Reativo;
        case 3:{
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
    while(c < ordem){//repete ate que o contador seja um numero antes da ordem
        string fim, strX, strY;//declarando strings
        getline(arquivo,fim,' ');//testa se chegou em EOF
        getline(arquivo,strX,' ');//pega o valor de X
        coord[c][0] = stof(strX);//armazena o valor na matriz com o id do vertice C
        getline(arquivo,strY,'\n');//pega o valor de Y
        coord[c][1] = stof(strY);//armazena o valor na matriz com o id do vertice C
        c++;
    }
    arquivo.close();

    grafo = new Grafo(ordem, coord, opc_Direc, opc_Peso_Aresta, opc_Peso_Nos);//constroi o grafo baseado no que foi passado no executavel
    int idNo;//variavel para salvar o id do no
    int idNoAlvo;//variavel para salvar o id do no alvo das arestas
    float Peso;// armazena o peso das arestas
    int selecao = 1;//selecao do menu

    if(opc_Peso_Nos == 0 && opc_Peso_Aresta == 1 && opc_Direc == 0)// se o grafo nao é direcionado mas tem peso somente nas arestas
    {
        for (int i=0;i<ordem;i++){
            for(int j=i+1;j<ordem;j++){
                grafo->insereAresta(i,j,false);
            }
        }
    }
    
    char instancia[arqEntrada.length()-14];
    for(int i=0; i < arqEntrada.length()-4; i++)
        instancia[i] = arqEntrada[i+10];

    while(selecao != 0){
       // system("clear");
        selecao = menu();
        
        selecionar(selecao, grafo, instancia);
    }
    return grafo;
    
}



