#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "dados.h"

/**
\brief Função que altera o estado da peça.
*/
void altera_estado_peca(ESTADO *estado, COORDENADA coordenada, CASA mudar)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    estado->tab[x][y] = mudar;
}

/**
\brief Função que altera o estado da casa onde estava, para a qual se pretendia mover.
*/
void troca_posicoes(ESTADO *estado, COORDENADA pos_inicial, COORDENADA pos_final)
{
    altera_estado_peca(estado, pos_inicial , '*');
    altera_estado_peca(estado, pos_final, '#');
}

/**
\brief Função que altera o estado das JOGADAS, adicionando a ultima coordenada dada.
*/
void atualiza_JOGADAS(ESTADO *estado, COORDENADA coord)
{
    if (estado->jogador_atual == 1)
    {
        estado->jogadas[ estado->num_jogadas ].jogador1 = coord; 
    }
    else
    {
        estado->jogadas[ (estado->num_jogadas ) + 1 ].jogador2 = coord; 
    }
}

/**
\brief Função que atualiza o estado a cada jogada.
*/
void atualiza_estado(ESTADO *estado, COORDENADA coord_mudar) 
{
    int jogador_mudar;
    if (estado->jogador_atual == 1)
        jogador_mudar = 2;
    else
        jogador_mudar = 1;

    troca_posicoes(estado, estado->ultima_jogada, coord_mudar);
    atualiza_JOGADAS(estado, coord_mudar);
    estado->jogador_atual = jogador_mudar;
    estado->num_comando = (estado->num_comando) + 1 ;
    estado->ultima_jogada = coord_mudar;
  //  return *estado;
}

/**
\brief Função que altera o estado do jogo cosoante a jogada efetuada.
*/
int jogar(ESTADO *estado, COORDENADA coord)
{
    int resul=0;
    COORDENADA coord_anterior;
    coord_anterior = estado->ultima_jogada;  //encontra_peca_preta(*estado);

    int verificar;
    verificar = verifica_jogada(estado, coord_anterior, coord);
    resul = verificar;

    if (verificar)
    {
        atualiza_estado(estado, coord);
    }
    else
    {
        printf("\nJogada inválida.\n");
    }
    return resul;
}