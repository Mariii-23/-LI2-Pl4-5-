#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"


//DESENHA CADA CASA
void desenha_Casa(CASA tabi[8][8], int linha, int coluna)
{
    if (linha==0 && coluna==7 )      printf("2"); 
    else
    {   
        if (linha==7 && coluna==0 )  printf("1");
        else
        {
            switch (tabi[linha][coluna])
            {
                case VAZIO : printf("."); break;
                case BRANCA : printf("#"); break;
                case PRETA : printf("*"); break;
                default: break;
            } 
        } 
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
void mostrar_tabuleiro(ESTADO estado1)
{
    int i=0;

    putchar('\n');
    for (i=0; i<8; i++)
    {
        desenha_Linha( estado1.tab, i);
    }
    putchar('\n');

}

int interpretador(ESTADO *estado) {
    char linha[BUF_SIZE];
    char col[2], lin[2];

    mostrar_tabuleiro( *estado );

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;

    if(strlen(linha) == 1 && sscanf(linha, "%[Q]", Q) == 1){
    	return 0;
    }

    if(strlen(linha) == 3 && sscanf(linha, "%[l]%[e]%[r]", l, e, r) == 3){
    FILE *fp;
    fp = fopen("jogo.txt", "r");
    if (fp == NULL) {
        printf("O ficheiro 'jogo.txt' não abriu.\n")
    	}

    comando_ler(fp);
    fclose(fp);
    }

        if(strlen(linha) == 2 && sscanf(linha, "%[g]%[r]", g, r) == 2){
    FILE *fp;
    fp = fopen("jogo.txt", "w");
    if (fp == NULL) {
        printf("O ficheiro 'jogo.txt' não abriu.\n")
    	}

    comando_gr(*estado, fp);
    fclose(fp);
    }

    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) 
    {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        jogar(estado, coord);
        mostrar_tabuleiro(*estado);
    }
    return 1;
}

/**
\brief Executa o comando ler, lendo o que está no ficheiro que recebe.
*/
void comando_ler(FILE fp) {
	int a;
    do {
    a = fscanf(fp)
    if (feof(fp)) {
        break;
    }
    printf("%c",c)
    } while (1)
}

/**
\brief Guarda no ficheiro cada casa do jogo.
*/
void guarda_Casa(CASA tabi[8][8], int linha, int coluna, FILE fp)
{
    if (linha==0 && coluna==7 )      fprintf(fp,"2"); 
    else
    {   
        if (linha==7 && coluna==0 )  fprintf(fp,"1");
        else
        {
            switch (tabi[linha][coluna])
            {
                case VAZIO : fprintf(fp, "."); break;
                case BRANCA : fprintf(fp, "#"); break;
                case PRETA : fprintf(fp, "*"); break;
                default: break;
            } 
        } 
    }
}

/**
\brief Guarda no ficheiro cada linha do jogo, recorrendo à função guarda_casa.
*/
void guarda_Linha(CASA tabi[8][8], int linha, FILE fp)
{
    int i;
    for(i=0; i<8; i++)
    {
        guarda_Casa( tabi, linha, i, fp);
    }
    fprintf(fp, "\n");
}

/**
\brief Guarda no ficheiro o tabuleiro do jogo, recorrendo à função guarda_linha.
*/
void guarda_tabuleiro(ESTADO estado1, FILE fp)
{
    int i=0;

    putchar('\n');
    for (i=0; i<8; i++)
    {
        guarda_Linha( estado1.tab, i, fp);
    }
    fprintf(fp, "\n");
}

/**
\brief Executa o comendo gr para guardar o tabuleiro do jogo no ficheiro.
*/
void comando_gr(ESTADO estado, FILE fp) {
    guarda_tabuleiro(*estado, fp)
}

void jogador_vencedor(ESTADO estado) {
    int j, jog_atual = estado.jogador_atual;
    if (jog_atual == 1) j = 2;
    else j = 1;

    printf ("O Player %d é o vencedor! Parabéns!", j);
}



void prompt(ESTADO estado) {
    printf("  abcdefgh");



    printf("\n Player_%d Jogada_%d -> ", estado.jogador_atual, estado.num_jogadas);
}