#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "Interface.h"
#include "dados.h"

typedef struct {
  /** O tabuleiro */
  CASA matriz[8][8];
  int player_atual;
  COORDENADA last_coord;
} ESTADO_simples;

typedef COORDENADA COORDENADAS[8];

typedef struct {
  int valor;
  COORDENADAS lista;
} Lista_coord;


int min(int a, int b)
{
    int resul = a;
    if (a>b) resul = b;
    return resul;
}
int max(int a, int b)
{
    int resul = a;
    if (a<b) resul = b;
    return resul;
}



////////////////////////////////////
//// Cria lista das jogadas ////////
/////////////////////////////////////

void adiciona_lista(Lista_coord *lista, ESTADO_simples estado, COORDENADA coord)
{
    if (estado.matriz[ coord.linha ][ coord.coluna ] == BRANCA ) 
    {
        lista->lista[ lista->valor ] = coord;
        lista->valor++;
    }  
}


Lista_coord *cria_lista_coords_possiveis(ESTADO_simples estado)
{
    Lista_coord *lista = (Lista_coord *) calloc(1, sizeof(Lista_coord));
    COORDENADA coord = estado.last_coord;

    COORDENADA coord1 = { coord.linha + 1 , coord.coluna + 1 };
    adiciona_lista(lista, estado, coord1);
    COORDENADA coord2 = { coord.linha + 1 , coord.coluna };
    adiciona_lista(lista, estado, coord2);
    COORDENADA coord3 = { coord.linha + 1 , coord.coluna - 1 };
    adiciona_lista(lista, estado, coord3);
    COORDENADA coord5 = { coord.linha - 1 , coord.coluna - 1 };
    adiciona_lista(lista, estado, coord5);
    COORDENADA coord6 = { coord.linha - 1, coord.coluna };
    adiciona_lista(lista, estado, coord6);
    COORDENADA coord7 = { coord.linha - 1 , coord.coluna + 1 };
    adiciona_lista(lista, estado, coord7);
    COORDENADA coord8 = { coord.linha , coord.coluna + 1 };
    adiciona_lista(lista, estado, coord8);
    COORDENADA coord4 = { coord.linha , coord.coluna - 1 };
    adiciona_lista(lista, estado, coord4);
    return lista;
}



///////////////////////////////////////
//// ATRIBUIR VALOR A UMA JOGADA //////
///////////////////////////////////////

int verificar_casa_ocupada(ESTADO_simples estado, COORDENADA coord)
{
    int x, y, resul = 1;
    x = coord.linha;
    y = coord.coluna; 
    if (x>=0 && x<=7 && y>=0 && y<=7 )
    {
        if (estado.matriz[x][y] == VAZIO ) resul = 0;
    }
    return resul;
}

/**
\brief Função principal que verifica se todas as casas vizinhas se encontram ocupadas.
*/
int verificar_casas_ocupadas(ESTADO_simples estado)
{
    COORDENADA coord = estado.last_coord;
    int resul;
    COORDENADA coord1 = { coord.linha + 1 , coord.coluna + 1 };
    COORDENADA coord2 = { coord.linha + 1 , coord.coluna };
    COORDENADA coord3 = { coord.linha + 1 , coord.coluna - 1 };
    COORDENADA coord5 = { coord.linha - 1 , coord.coluna - 1 };
    COORDENADA coord6 = { coord.linha - 1, coord.coluna };
    COORDENADA coord7 = { coord.linha - 1 , coord.coluna + 1 };
    COORDENADA coord8 = { coord.linha , coord.coluna + 1 };
    COORDENADA coord4 = { coord.linha , coord.coluna - 1 };
    resul = ( verificar_casa_ocupada( estado , coord1 ) && verificar_casa_ocupada( estado , coord2 ) &&
              verificar_casa_ocupada( estado , coord3 ) && verificar_casa_ocupada( estado , coord4 ) &&
              verificar_casa_ocupada( estado , coord5 ) && verificar_casa_ocupada( estado , coord6 ) &&
              verificar_casa_ocupada( estado , coord7 ) && verificar_casa_ocupada( estado , coord8 )   );
    return resul;
}

/// funcao q verifica se ganhou em casa, atribuindo pontos ///
int ganhou_em_casa(ESTADO_simples estado,int player)
{
    int resul;
    int x = estado.last_coord.linha;
    int y = estado.last_coord.coluna;
    int ganhou = ( (x == 0 && y == 0) || (x == 7 && y == 7));

    if (ganhou && !player) ganhou = -1;
    else resul = ganhou;
    return resul; 
}

/// funcao que verifica se ganhou obrigando o outro a jogar para a casa do adversario ///
int encurralado_casa(ESTADO_simples estado, int player)
{
    int resul = 0;
    int ganhou_casa = ganhou_em_casa(estado,player);
    int valor = verificar_casas_ocupadas(estado);
    if  (ganhou_em_casa!=0 && valor ) resul = 2 * ganhou_casa;
    return resul;
}

/// funcao que verifica se ganhou encurralando o outro jogador ///
int encurralado_jogo(ESTADO_simples estado, int player)
{
    int resul = 0;
    int valor = verificar_casas_ocupadas(estado);
    if (player) resul = 3 * valor;
    else resul = -3 * valor;
    return resul;
}

/// funcao que verifica se ganhou encurralado, atribuindo pontos ///
int ganhou_encurralado(ESTADO_simples estado,int player)
{
    int resul = 0;
    int valor = encurralado_jogo(estado, player);
    if (valor != 0 ) resul = valor;
    else resul = encurralado_casa(estado,player);
    return resul;
}


/// AVALIAR JOGADA ///
// nos=player true  
int avaliar_jogada(ESTADO_simples estado,int player)
{
    int resul = ganhou_encurralado(estado, player);
    if (resul == 0) resul = ganhou_em_casa(estado, player);
    return resul;
}



/////////////////////////////////////////////////////
//////  ALGORITMO QUE AVALIA A MELJOR JOGADA ////////
////////////////////////////////////////////////////

int minimax(COORDENADA coord, ESTADO_simples estado, int alpha, int betha, int player_atual)
{
    int i;
    ///verifica se o jogo acabou //
    int ganhou = avaliar_jogada(estado, player_atual);
    if (ganhou !=0) return ganhou;

    Lista_coord *lista = cria_lista_coords_possiveis(estado);
    int maxValor=NULL, valor=NULL, minValor=NULL;

    // se formos nos a jogar
    if (player_atual)
    {
        for (i = 0; i < lista->valor; i++)
        {
            valor = minimax(lista->lista[i], **atualkizar estado***, alpha, betha, false );
            maxValor = max(alpha, valor);
            if betha <= alpha break;
            return maxValor;
        }
    }
    else
    {
        for (i = 0; i < lista->valor; i++)
        {
            valor = minimax(lista->lista[i], **atualkizar estado***, alpha, betha, true );
            minValor = min(minValor, valor);
            betha = min(betha, valor);
            if (betha <= alpha) break;
            return minValor;
        }  
    }  
}