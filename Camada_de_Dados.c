#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"

//DEFINE O ESTADO INICIAL
void casas_inicial(CASA tabi[8][8])
{
    int i, j;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if (i==3 && j==4)
            {
                tabi[i][j] = PRETA;
            }
            else
            {
                tabi[i][j] = VAZIO;
            }       
        }
    }  
}

//ESTADO INICIAL
ESTADO estado_Inicial()
{
    ESTADO estado;
    casas_inicial( estado.tab);
   // estado.jogadas = NULL;
    estado.num_jogadas = 0;
    estado.jogador_atual = 0;

    return estado;
}

//DESENHA CADA CASA
void desenha_Casa(CASA tabi[8][8], int linha, int coluna)
{
    switch (tabi[linha][coluna])
    {
        case VAZIO : printf("."); break;
        case BRANCA : printf("#"); break;
        case PRETA : printf("*"); break;
        default: break;
    }
}

//DESENHA CADA LINHA
void desenha_Linha(CASA tabi[8][8], int linha)
{
    int i;
    for(i=0; i<8; i++)
    {
        desenha_Casa( tabi, linha, i);
    }
    putchar('\n');
}

//DESENHA ESTADO DO JOGO
void desenha_estado(ESTADO estado1)
{
    int i=0;

    putchar('\n');
    for (i=0; i<8; i++)
    {
        desenha_Linha( estado1.tab, i);
    }
    putchar('\n');

}

//FUNCAO QUE DEVLOVE O ESTADO DE UMA PECA CONSOANTE AS COORDENADAS
CASA estado_casa(ESTADO estado, COORDENADA coordenada)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    CASA peca = estado.tab[x][y];
    return peca;
}

//FUNCAO QUE ALTERA O ESTADO DA PECA
void altera_estado_peca(ESTADO estado, COORDENADA coordenada, CASA mudar)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    estado.tab[x][y] = mudar;
}

//FUNCAO QUE ALTERA O ESTADO DAS CASAS DA POSICAO DE ONDE ESTAVA PARA O QUAL SE PRETENDIA MOVER
void troca_posicoes(ESTADO estado, COORDENADA pos_inicial, COORDENADA pos_final)
{
    altera_estado_peca(estado, pos_inicial , BRANCA);
    altera_estado_peca(estado, pos_final, PRETA);
}

//FUNCAO QUE VERIFICA SE A JOGADA É POSSIVEL
int verifica_jogada(ESTADO estado, COORDENADA pos_final)
{
    int resul = 1;
    int x = pos_final.linha;
    int y = pos_final.coluna;
    CASA peca = estado.tab[x][y];
    if (peca == BRANCA)
    {
        resul = 0;
    }
    return resul;
}



void jogar()
{
    ESTADO estado;
    estado = estado_Inicial();
    desenha_estado( estado );
}