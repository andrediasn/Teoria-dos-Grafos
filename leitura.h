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

         //Algoritmo Guloso; (9)
        case 1:{
            graph->Guloso(instancia);
            break;
        }
         //Algoritmo Guloso Randomizado; (10)
        case 2:{
            break;
        }
         //Algoritmo Guloso Randomizado Reativo; (11)
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



