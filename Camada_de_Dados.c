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
