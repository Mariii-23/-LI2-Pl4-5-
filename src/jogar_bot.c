#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "Interface.h"
#include "dados.h"
#include "listas.h"

/**
\brief Função auxiliar que insere a coordenada na lista se esta for uma possível coordenada a ser efetuada.
*/
LISTA adiciona_lista_(LISTA lista, ESTADO *estado, COORDENADA coord)
{
    COORDENADA *coord_ ;
    coord_->linha = coord.linha;
    coord_->coluna = coord.coluna;

    if ( verifica_coord(coord)   &&    estado->tab[ coord.linha ][ coord.coluna ] == BRANCA ); 
    {
        lista = insere_cabeca(lista, coord_);
    }  
    return lista;
}

/**
\brief Função principal que returna uma LISTA de coordenadas possíveis a serem efetuadas.
*/
LISTA cria_lista_coords_possiveis_(ESTADO *estado)
{
    LISTA lista = criar_lista(); 

    COORDENADA coord = estado->ultima_jogada;

    COORDENADA coord1 = { coord.linha + 1 , coord.coluna + 1 };
    lista = adiciona_lista_(lista, estado, coord1);
    COORDENADA coord2 = { coord.linha + 1 , coord.coluna };
    lista = adiciona_lista_(lista, estado, coord2);
    COORDENADA coord3 = { coord.linha + 1 , coord.coluna - 1 };
    lista = adiciona_lista_(lista, estado, coord3);
    COORDENADA coord5 = { coord.linha - 1 , coord.coluna - 1 };
    lista = adiciona_lista_(lista, estado, coord5);
    COORDENADA coord6 = { coord.linha - 1, coord.coluna };
    lista = adiciona_lista_(lista, estado, coord6);
    COORDENADA coord7 = { coord.linha - 1 , coord.coluna + 1 };
    lista = adiciona_lista_(lista, estado, coord7);
    COORDENADA coord8 = { coord.linha , coord.coluna + 1 };
    lista = adiciona_lista_(lista, estado, coord8);
    COORDENADA coord4 = { coord.linha , coord.coluna - 1 };
    lista = adiciona_lista_(lista, estado, coord4);
    return lista;
}

int distancia_coord(ESTADO estado,COORDENADA coord, int player)
{
    COORDENADA coord_casa;
    if (player==1) 
    {
        coord_casa.coluna = 0;
        coord_casa.linha = 0;
    }
    else
    {
        coord_casa.coluna = 7;
        coord_casa.linha = 7;
    }
    int x = abs( coord_casa.coluna - coord.coluna ),
        y = abs( coord_casa.linha - coord.linha );
    return ( sqrt( x*x + y*y ) );
}


COORDENADA comando_jogar(ESTADO *estado)
{
    int player = estado->jogador_atual;
    COORDENADA coord = estado->ultima_jogada; 
    
    
}