#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "dados.h"

/**
\brief Guarda no ficheiro cada casa do jogo.
*/
void guarda_Casa(CASA tabi[8][8], int linha, int coluna, FILE *fp)
{
    switch (tabi[linha][coluna])
    {
        case VAZIO : fprintf(fp, "."); break;
        case BRANCA : fprintf(fp, "#"); break;
        case PRETA : fprintf(fp, "*"); break;
        case UM : fprintf(fp, "1"); break;
        case DOIS : fprintf(fp, "2"); break;
        default: break;
    } 
} 

/**
\brief Guarda no ficheiro cada linha do jogo, recorrendo à função guarda_casa.
*/
void guarda_Linha(CASA tabi[8][8], int linha, FILE *fp)
{
    int i;
    for(i=8; i>0; i--)
    {
        guarda_Casa( tabi, linha, i, fp);
    }
    fprintf(fp, "\n");
}

/**
\brief Guarda no ficheiro o tabuleiro do jogo, recorrendo à função guarda_linha.
*/
void guarda_tabuleiro(ESTADO estado1, FILE *fp)
{
    int i;

    fprintf(fp,"\n abcdefgh");
    for (i=8; i>0; i--)
    {
        fprintf(fp,"%d ", i);
        guarda_Linha( estado1.tab, i, fp);
    }
    fprintf(fp, "\n");
}

/// COMANDOS ////

/**
\brief Executa o comando ler, lendo o que está no ficheiro que recebe.
*/
void comando_ler(FILE *fp) {
	char a;
    do 
    {
        fscanf(fp, "%c", a);
        if (feof(fp)) {
            break;
        }
        printf("%c",a);
    } while (1);
}

/**
\brief Executa o comendo gr para guardar o tabuleiro do jogo no ficheiro.
*/
void comando_gr(ESTADO estado, FILE *fp) {
    guarda_tabuleiro(estado, fp);
}

/// INTERPRETADOR ///

/**
\brief Intrepretador do jogo.
*/
int interpretador(ESTADO *estado) {
    char linha[BUF_SIZE];
    char col[2], lin[2];

/*Imprime o tabuleiro de acordo com o estado do jogo */
    mostrar_tabuleiro( *estado );

/* Termina o jogo por algum motivo */
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;

/* Lê o comando Q, que retorna 0, o que faz com que a main pare o ciclo e o jogo fecha. */
    if(strlen(linha) == 1 && sscanf(linha, "%[Q]") == 1){
    	return 0;
    }

/* Abre o ficheiro em modo reading caso exista, caso contrário apresenta o erro. */
    if(strlen(linha) == 3 && sscanf(linha, "%[l]%[e]%[r]") == 3){
    FILE *fp;
    fp = fopen("jogo.txt", "r");
    if (fp == NULL) {
        printf("O ficheiro 'jogo.txt' não abriu.\n");
    	}
/* Lê o tabuleiro que está no ficheiro e imprime. */
    comando_ler(fp);
/* Fecha o ficheiro */
    fclose(fp);
    }

/* Abre o ficheiro em modo writing(se o ficheiro não existir, cria-o), e guarda o tabuleiro */
    if(strlen(linha) == 2 && sscanf(linha, "%[g]%[r]") == 2){
        FILE *fp;
        fp = fopen("jogo.txt", "w");
        if (fp == NULL) 
            {
                printf("O ficheiro 'jogo.txt' não abriu.\n");
    	    }

/* Grava o tabuleiro no ficheiro. */
        comando_gr(*estado, fp);
/* Fecha novamente o documento */
        fclose(fp);
    }

    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) 
    {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        jogar(estado, coord);
        guarda_tabuleiro(estado, *fp);
    }
    return 1;
}


/// FIM DO JOGO ///

/**
\brief Função que determina o vencedor do jogo.
*/
void jogador_vencedor(ESTADO estado) {
    int j, jog_atual = estado.jogador_atual;
    if (jog_atual == 1) j = 2;
    else j = 1;

    printf ("O Player %d é o vencedor! Parabéns!", j);
}


/**
\brief Prompt do jogo.
*/
void prompt(ESTADO estado) {  
    guarda_tabuleiro(estado, fp);
    fprintf(fp, "# %d Player_%d Jogada_%d -> ", estado.num_comando, estado.jogador_atual, estado.num_jogadas);
}