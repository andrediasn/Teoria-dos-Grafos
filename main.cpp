#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
#include "Grafo.h"
#include "leitura.h"


int main (int argc, char * argv[])
{
    /* if (argc != 6) 
    {
        std::cout << "ERROR: Expecting: ./<program_name> <instancia> <graulimitador> <weighted_edge> <weighted_node> " << std::endl; //mensagem de erro
        return 1;//retorne
    } */
   Grafo* grafo = leitura(argc,argv);

   return 0;
}
