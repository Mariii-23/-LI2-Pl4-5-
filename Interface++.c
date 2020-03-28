#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "dados.h"

/**
\brief Função que determina o vencedor do jogo.
*/
void jogador_vencedor(ESTADO *estado) {
    int j, jog_atual = estado->jogador_atual;
    if (jog_atual == 1) j = 2;
    else j = 1;

    printf ("O Player %d é o vencedor! Parabéns!", j);
}

/**
\brief Imprime cada casa do jogo.
*/
void imprime_Casa(CASA tabi[8][8], int linha, int coluna)
{
    switch (tabi[linha][coluna])
    {
        case '.' : printf("."); break;
        case '#' : printf("#"); break;
        case '*' : printf("*"); break;
        case '1' : printf("1"); break;
        case '2' : printf("2"); break;
        default: break;
    } 
} 

/**
\brief Imprime cada linha do jogo, recorrendo à função imprime_casa.
*/
void imprime_Linha(CASA tabi[8][8], int linha)
{
    int i;
    for(i=0; i<=7; i++)
    {
        imprime_Casa( tabi, linha, i);
    }
    printf("\n");
}

/**
\brief Imprime o tabuleiro do jogo, recorrendo à função guarda_linha.
*/
void imprime_tabuleiro(ESTADO *estado)
{
    int i, linha=8;
    printf("\n  abcdefgh\n");
    for (i=7; i>=0; i--,linha--)
    {
        printf("%d ",linha);
        imprime_Linha( estado->tab, i);
    }
    printf("\n");
    printf("# %d Player_%d Jogada_%d -> ", estado->num_comando, estado->jogador_atual, estado->num_jogadas);
 //   printf("\n%d  %d\n", estado->ultima_jogada.linha, estado->ultima_jogada.coluna);

}

/**
\brief Guarda no ficheiro cada casa do jogo.
*/
void guarda_Casa(CASA tabi[8][8],int linha, int coluna, FILE *fp)
{
    switch (tabi[linha][coluna])
    {
        case '.' : fprintf(fp, "."); break;
        case '#' : fprintf(fp, "#"); break;
        case '*' : fprintf(fp, "*"); break;
        case '1' : fprintf(fp, "1"); break;
        case '2' : fprintf(fp, "2"); break;
        default: break;
    } 
} 

/**
\brief Guarda no ficheiro cada linha do jogo, recorrendo à função guarda_casa.
*/
void guarda_Linha(CASA tabi[8][8],int linha, FILE *fp)
{
    int i;
    for(i=0; i<=7; i++)
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

    for (i=7; i>=0; i++)
    {
        guarda_Linha( estado1.tab, i, fp);
    }
    fprintf(fp, "\n");
}

/// COMANDOS ////
/**
\brief Prompt do jogo.
*/
void prompt(ESTADO estado, FILE *fp) {  
    guarda_tabuleiro(estado, fp);
    fprintf(fp, "# %d Player_%d Jogada_%d -> ", estado.num_comando, estado.jogador_atual, estado.num_jogadas);
}
/**


\brief Executa o comando ler, lendo o que está no ficheiro que recebe.
*/
void comando_ler(FILE *fp) {
	char *a = NULL;
    do 
    {
        fscanf(fp, "%c", a);
        if (feof(fp)) {
            break;
        }
        printf("%c",a[0]);
    } while (1);
}

/**
\brief Executa o comendo gr para guardar o tabuleiro do jogo no ficheiro.
*/
void comando_gr(ESTADO *estado, FILE *fp) {
    prompt(*estado, fp);
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

    imprime_tabuleiro(estado);

/* Abre o ficheiro em modo writing(se o ficheiro não existir, cria-o), e guarda o tabuleiro */

  //  if(sscanf(linha, "gr %s",filename) == 1){
    FILE *fp;

    fp = fopen(filename, "w");
    if (fp == NULL) {
            printf("O ficheiro não abriu.\n");
        }

/* Grava o tabuleiro no ficheiro. */
    comando_gr(estado, fp);
   //     !!!!!!!!!!!!!!!!!!!!
        //imprime_tabuleiro(estado);


/* Fecha novamente o documento */
    fclose(fp);
    

/* Abre o ficheiro em modo reading caso exista, caso contrário apresenta o erro. */
   // if(sscanf(linha, "ler %s",filename) == 1){
      
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("O ficheiro não abriu.\n");
	}
/* Lê o tabuleiro que está no ficheiro e imprime. */
    comando_ler(fp);
/* Fecha o ficheiro */
    fclose(fp);
    


    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) 
    {
       // FILE *fp;
      //  fp = fopen("jogo.txt", "w");

        COORDENADA coord = {*col - 'a', *lin - '1'};

        jogar(estado, coord);
      //  if   (jogar(estado, coord));
       // {
    //    comando_gr(estado, fp);
            //prompt(*estado, fp);
     //   }
     //   fclose(fp);

    }


/* Termina o jogo por algum motivo */
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;

/* Lê o comando Q, que retorna 0, o que faz com que a main pare o ciclo e o jogo fecha. */
    if(strlen(linha) == 1 && sscanf(linha, "Q") == 1){
    	return 0;
    }

    return 1;
}


/// FIM DO JOGO ///
