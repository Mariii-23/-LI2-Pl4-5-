#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "dados.h"

/**
\brief Função que determina o vencedor do jogo.
*/
void jogador_vencedor(ESTADO *estado, FILE *stream) {
    int j, jog_atual = estado->jogador_atual;
    if (jog_atual == 1) j = 2;
    else j = 1;
    if ( estado->ultima_jogada.linha == 0 && estado->ultima_jogada.coluna == 0) j = 1;
    if ( estado->ultima_jogada.linha == 7 && estado->ultima_jogada.coluna == 7) j = 2;
    fprintf (stream, "\nO Player %d é o vencedor! Parabéns!\n", j);
}

/**
\brief Prompt do jogo.
*/
void prompt(ESTADO *estado, FILE *stream) {  
    fprintf(stream, "# %d Player_%d Jogada_%d -> ", estado->num_comando, estado->jogador_atual, estado->num_jogadas);
}

void guarda_Linha(ESTADO *estado, int linha, FILE *stream)
{
    int i;
    CASA casa;
    for(i=0; i<=7; i++)
    {
        casa = estado->tab[linha-1][i];
        fputc(casa, stream);
    }
    fprintf(stream, "\n");
}

/**
\brief Guarda no ficheiro o tabuleiro do jogo, recorrendo à função guarda_linha.
*/
void guarda_tabuleiro(ESTADO *estado, FILE *stream)
{
    int i;
    if (stream == stdout) fprintf(stream,"\n  abcdefgh\n");
    for (i=8; i>0; i--)
    {
        if (stream == stdout) fprintf(stream, "%d ",i);
        guarda_Linha( estado, i, stream);
    }
    if (stream == stdout ) prompt(estado, stream);
}

/// INTERPRETADOR ///

/**
\brief Intrepretador do jogo.
*/
int interpretador(ESTADO *estado) {
    char linha[BUF_SIZE];
    char filename[BUF_SIZE] = "jogo.txt" ;
    char col[2], lin[2];
  //  filename = "jogo.txt";
    int ganhou = 0;

    guarda_tabuleiro(estado, stdout);

    return ganhou;
}

/// FIM DO JOGO ///
