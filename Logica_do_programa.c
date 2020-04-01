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
void troca_posicoes(ESTADO *estado, COORDENADA pos_final)
{
    altera_estado_peca(estado, estado->ultima_jogada, BRANCA);
    altera_estado_peca(estado, pos_final, PRETA);
}

/**
\brief Função que altera o estado das JOGADAS, adicionando a ultima coordenada dada.
*/
void atualiza_JOGADAS(ESTADO *estado, COORDENADA coord)
{
    if (estado->jogador_atual == 1)   estado->jogadas[ estado->num_jogadas ].jogador1 = coord; 
    else                              estado->jogadas[ (estado->num_jogadas ) + 1 ].jogador2 = coord; 
}

void atualiza_Num_Jogadas(ESTADO *estado)
{
    int jog = estado->jogador_atual;
    if (jog == 1)  estado->num_jogadas += 1;
}

/**
\brief Função que atualiza o estado a cada jogada.
*/
void atualiza_estado(ESTADO *estado, COORDENADA coord_mudar) 
{
    troca_posicoes(estado, coord_mudar);
    estado->ultima_jogada = coord_mudar;
    atualiza_JOGADAS(estado, coord_mudar);
    if (estado->jogador_atual == 1)  estado->jogador_atual = 2;
    else                             estado->jogador_atual = 1;
    atualiza_Num_Jogadas(estado);
    estado->num_comando +=1 ;
}

/**
\brief Função que altera o estado do jogo cosoante a jogada efetuada.
*/
int jogar(ESTADO *estado, COORDENADA coord)
{
    int resul=0;
    int pode_jogar = verifica_jogada(estado, coord);
    
    if (pode_jogar)
    {
        atualiza_estado(estado, coord);
    }
    else
    {
        printf("\nJogada inválida.\n");
    }
    resul = 1;

    return resul;
}
