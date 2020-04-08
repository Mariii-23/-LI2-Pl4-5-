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