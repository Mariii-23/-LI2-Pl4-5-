#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Camada_de_Dados.h"
#include "Interface.h"
#include "Logica_do_programa.h"
#include "Melhor_Jogada.h"
#include "listas.h"
#include "dados.h"

void atualiza_jogada_boot(ESTADO *estado){
    COORDENADA coord = da_coordenada_distancia(estado);
        //COORDENADA coord = da_coordenada(estado);

        /*deveria dar este */
        //COORDENADA coord = obtem_coord_atraves_da_distancia( estado );
        if( verifica_coord(coord) && verifica_jogada(estado, coord))         
            jogar(estado, coord);
        else
        {
            coord = da_coordenada(estado);
        
            if( verifica_coord(coord) && verifica_jogada(estado, coord))
                  jogar(estado, coord);
            else  fprintf(stdout,"O comando jogar falhou.\n");
        }
}


int main(int argc, char *argv[])
{    
    int resul = 0;

    ESTADO *estado;
    estado = inicializador_estado();

    if(argc == 3) 
    {
    
        /* le o ficheiro */
        ler(estado, argv[1]);

        /* jogada boot */
        atualiza_jogada_boot( estado );

        /*gravar ficheiro */
        gr(estado, argv[2]);
    }

    return resul;
}