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

bool vazio(ifstream& arq){
    return arq.peek() == std::ifstream::traits_type::eof();
}

int bestSol(int sol[]){
    int best = sol[0];
    for(int i = 1; i < 5; i++){
        if(best > sol[i])
            best = sol[i];
    }
    return best;
}

float tempoMedio(float tempo[]){
    float soma;
    for(int i = 0; i < 5; i++){
        soma += tempo[i];
    }
    return soma/5;
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
                int sol[5];
                float *tempo = new float[5];
                int max;
                int seed;
                cout<< "Digite o numero de iteracoes: ";
                cin >> max;
                cout<< "Digite um valor inteiro para seed: ";
                cin >> seed;
                // alfas 0.05 0.1 0.15 0.3 0.5
                //melhor resultado 0.05 
                cout << endl << "Executando alfa 0.05" << endl;
                sol[0] = graph->gulosoRandomizado(0.05, max, tempo, seed);
                //melhor resultado 0.10
                cout << "Executando alfa 0.1" << endl;
                sol[1] = graph->gulosoRandomizado(0.1, max, tempo, seed+1);
                //melhor resultado 0.15 
                cout << "Executando alfa 0.15" << endl;
                sol[2] = graph->gulosoRandomizado(0.15, max, tempo, seed+2);
                //melhor resultado 0.30 
                cout << "Executando alfa 0.3" << endl;
                sol[3] = graph->gulosoRandomizado(0.30, max, tempo, seed+3);
                //melhor resultado 0.50
                cout << "Executando alfa 0.5" << endl;
                sol[4] = graph->gulosoRandomizado(0.50, max, tempo, seed+5);
                

                cout << endl << " - Melhor solucao geral: " << bestSol(sol) << endl;
                cout << " - Tempo medio: " << tempoMedio(tempo) << endl;

                string saida = "Resultado/Randomizado/" + instancia + "rand.txt";
                ofstream arq(saida, ios::app);
                ifstream v(saida);
                if(vazio(v))
                    arq << "Alfa 0,05;Tempo;Alfa 0,1;Tempo;Alfa 0,15;Tempo;Alfa 0,3;Tempo;Alfa 0,5;Tempo;Iteracoes" << endl;
                v.close();
                arq << instancia << ";"<< sol[0] << ";" << tempo[0] << ";"; 
                arq << sol[1] << ";" << tempo[1] << ";"; 
                arq << sol[2] << ";" << tempo[2] << ";"; 
                arq << sol[3] << ";" << tempo[3] << ";";
                arq << sol[4] << ";" << tempo[4] << ";";
                arq << max << endl;
                arq.close();
            break;
        }
         //Algoritmo Guloso Randomizado Reativo;
        case 3:{
            int numInteracoes,resultado;
            cout<< "Digite o numero de iteracoes(minimo 100): ";
            cin >> numInteracoes;
            float *tempo = new float[5];
            int bloco;
            cout<< "Digite tamanho do bloco(minimo e recomendavel 20): ";
            cin >> bloco;
            int seed;
            cout<< "Digite um valor para seed: ";
            cin >> seed;
            graph->gulosoRandomizadoReativo(numInteracoes, tempo, bloco, seed, instancia);
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

bool buscaTexto(string T, string P){
    int tamT = T.length();
    int tamP = P.length();
    int ocorrencias = 0;
    for(int i = 0; i <= (tamT-tamP); i++){
        int k = i;
        int j = 0;
        while(T[k] == P[j]){
            j ++;
            k ++;
            if(j==tamP){
                return true;
                ocorrencias ++;
                break;
            }
        }
    }
    return false;
}

string buscaInstancia(string T){
    if(buscaTexto(T, "pr124"))
        return "pr124";
    else if(buscaTexto(T, "pr136"))
        return "pr136";
    else if(buscaTexto(T, "pr144"))
        return "pr144";
    else if(buscaTexto(T, "d493"))
        return "d493";
    else if(buscaTexto(T, "d657"))
        return "d657";
    else if(buscaTexto(T, "d1291"))
        return "d1291";
    else if(buscaTexto(T, "d1655"))
        return "d1655";
    else if(buscaTexto(T, "d2103"))
        return "d2103";
    else if(buscaTexto(T, "rat575"))
        return "rat575";
    else if(buscaTexto(T, "u574"))
        return "u574";
    else
        return "Grupo10";
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
        grafo->ordenaArestas();
    }
    
    string instancia = buscaInstancia(arqEntrada);
    
    while(selecao != 0){
       // system("clear");
        selecao = menu();
        
        selecionar(selecao, grafo, instancia);
    }
    return grafo;
    
}



