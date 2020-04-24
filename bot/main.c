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

    char filename_jog1[BUF_SIZE] ;
    char filename_jog2[BUF_SIZE] ;

    int i = 1, j=0;
    /*
    if (argc == 2)
    {   
        char linha[BUF_SIZE] = argv[argc];
        while ( (linha[i] != 'n') )
        {
            filename_jog1[ i-1 ] = linha[i];
            i++;
        }

        while ( linha[i] != '\0' )
        {
            filename_jog2[ j ] = linha[i];
            i++;
            j++;    
        }
    }*/

    if(argc == 3) 
    {
        char filename_jog1[BUF_SIZE] = argv[1];
        char filename_jog2[BUF_SIZE] = argv[2];
    }

    ler(estado, filename_jog1);

    /* jogada boot */
    atualiza_jogada_boot( estado );

    /*gravar ficheiro */
     gr(estado, filename_jog2);

    return resul;
}