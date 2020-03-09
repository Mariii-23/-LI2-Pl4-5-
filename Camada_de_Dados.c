#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"

//#define BUF_SIZE 1024


/*
// Estruturas de dados (devem ser colocadas no módulo correto da camada dos dados
typedef enum {VAZIO, BRANCA, PRETA} CASA;

typedef struct {
int coluna;
int linha;
} COORDENADA;

typedef struct {
COORDENADA jogador1;
COORDENADA jogador2;
} JOGADA;

typedef JOGADA JOGADAS[32];

typedef struct {
CASA tab[8][8];
JOGADAS jogadas;
int num_jogadas;
int jogador_atual;
} ESTADO;*/

/*
CASA casas_inicial = {
                        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO},
                        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO },
                        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO },
                        {VAZIO, VAZIO, VAZIO, VAZIO, PRETA, VAZIO, VAZIO, VAZIO },
                        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO },
                        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO },
                        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO },
                        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO }
                     };*/

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
 //   return *tabi;
}



ESTADO estado_Inicial()
{
    ESTADO estado;
    casas_inicial( estado.tab);
   // estado.jogadas = NULL;
    estado.num_jogadas = 0;
    estado.jogador_atual = 0;

    return estado;
}

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

void desenha_Linha(CASA tabi[8][8], int linha)
{
    int i;
    for(i=0; i<8; i++)
    {
        desenha_Casa( tabi, linha, i);
    }
    putchar('\n');
}

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
