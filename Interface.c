#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "dados.h"

/// Funcao que mostra um determinado tabuleiro //
void mostra_tabuleiro(CASA tab[8][8],FILE *stream)
{
    int linha, coluna;
    CASA casa;
    fprintf(stream, "  abcdefgh\n");
    for (linha = 7; linha >= 0; linha--)
    {
        fprintf(stream, "%d ", linha+1);
        for (coluna = 0; coluna < 8; coluna++)
        {
           // fprintf(stream,CASA,tab[i][j]);
            casa = tab[linha][coluna];
            fputc(casa, stream);
        }
        fprintf(stream, "\n");
    }
    fprintf(stream, "\n");
}

/// JOGADOR VENCEDOR ///
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

/// TABULEIRO : IMPRIME OU GUARDA ///

/**
\brief Prompt do jogo.
*/
void prompt(ESTADO *estado, FILE *stream) {  
    fprintf(stream, "# %d Player_%d Jogada_%d -> ", estado->num_comando, estado->jogador_atual, estado->num_jogadas);
}

/**
\brief Guarda no ficheiro cada linha do jogo, recorrendo à função guarda_casa.
*/
void guarda_Linha(ESTADO *estado, int linha, FILE *stream)
{
    int coluna;
    CASA casa;
    for(coluna=0; coluna<=7; coluna++)
    {
        casa = estado->tab[linha][coluna];
        fputc(casa, stream);
    }
    fprintf(stream, "\n"); //apagar depois
}

/**
\brief Guarda no ficheiro o tabuleiro do jogo, recorrendo à função guarda_linha.
*/
void guarda_tabuleiro(ESTADO *estado, FILE *stream)
{
    int linha;
    if (stream == stdout) fprintf(stream,"\n  abcdefgh\n");
    
    for (linha=7; linha>=0; linha--)
    {
        if (stream == stdout) fprintf(stream, "%d ",linha+1);
        guarda_Linha( estado, linha, stream);
    }
    fprintf(stream, "\n");
}

/// !!!____COMANDOS___!!! ////

void ler_linha(ESTADO *estado, char linha[], int l)
{   
    char casa;
    for(int coluna = 0; coluna < 8; coluna++) 
    { 
        casa = linha[ coluna ];
        estado->tab[ l ][ coluna ] = casa;
        if ( casa == BRANCA ) estado->num_comando++;
    }
} 

/**
\brief Executa o comando ler, lendo o que está no ficheiro que recebe.
*/
void comando_ler(FILE *fp,ESTADO *estado)
{
    COORDENADA coord1 = {-1,-1}, coord2 = {-1,-1};
    char x1, x2, y1, y2;
    char linha[BUF_SIZE];
    int l , n_jogadas;
    int n_comando_inicial = estado->num_comando;

    estado->num_comando = 1;

    
    for( int l = 7; l >= 0; l--)
    {
        fscanf(fp, "%s", linha);
        ler_linha(estado, linha, l);
    } 

    n_jogadas = (estado->num_comando ) / 2 ;

    for (l = 0; l != (n_jogadas-1) && fscanf( fp, "%*s %c%c %c%c %*s", &x1, &y1, &x2, &y2) == 4 ; l++)
    {
        coord1.linha = x1 - 'a';
        coord1.coluna = y1 - '1';
        coord1.linha = x2 - 'a';
        coord1.coluna = y2 - '1';
        guarda_Jogadas_2(estado, coord1, coord2, l);
    }
    if (fscanf( fp, "%*s %c%c %*s", &x1, &y1) == 2)  
    {
        coord1.linha = x1 - 'a';
        coord1.coluna = y1 - '1';
        guarda_Jogadas_1(estado, coord1, l);
    }
    atualiza_estado_comando_ler(estado);
    estado->num_comando = n_comando_inicial+1;

}


void comando_pos(ESTADO *estado, int n_jogadas ){
    mostra_pos(estado,n_jogadas );
    estado->num_comando++;
    prompt(estado, stdout);
}


/// Comando movs ///
/**
\brief Executa o comando movs para gravar os movimentos.
*/
void comando_movs(ESTADO *estado, FILE *stream)
{
    int cont=0, num;
    int n_jogadas = estado->num_jogadas;
    int j = estado->jogador_atual;
    COORDENADA coord1 = estado->jogadas[cont].jogador1;
    COORDENADA coord2 = estado->jogadas[cont].jogador2;

    for (num = 1 ; num < n_jogadas ; num++ , cont++)
    {
        coord1 = estado->jogadas[cont].jogador1;
        coord2 = estado->jogadas[cont].jogador2;
        if (num <10)  fprintf(stream, "0%d: %c%d %c%d\n", num, coord1.coluna + 'a', coord1.linha + 1, coord2.coluna + 'a', coord2.linha + 1 );
        else          fprintf(stream, "%d: %c%d %c%d\n", num, coord1.coluna + 'a', coord1.linha + 1, coord2.coluna  + 'a', coord2.linha + 1 );
    }
    coord1 = estado->jogadas[cont].jogador1;
    coord2 = estado->jogadas[cont].jogador2;
    if (j == 2 )
    {
        if (num <10)  fprintf(stream, "0%d: %c%d\n", num, coord1.coluna + 'a', coord1.linha + 1);
        else          fprintf(stream, "%d: %c%d\n", num, coord1.coluna + 'a', coord1.linha + 1); 
    }
}

/// COMANDO GRAVAR ///
/**
\brief Executa o comendo gr para guardar o tabuleiro do jogo no ficheiro.
*/
void comando_gr(ESTADO *estado, FILE *stream) {
    guarda_tabuleiro(estado, stream);
    comando_movs(estado, stream);
}

/// INTERPRETADOR ///

/**
\brief Intrepretador do jogo.
*/
int interpretador(ESTADO *estado) {
    char linha[BUF_SIZE];
    char filename[BUF_SIZE] = "jogo.txt" ;
    char col[2], lin[2];
    int n_pos=0;
  //  filename = "jogo.txt";
    int ganhou = 0;

    guarda_tabuleiro(estado, stdout);
    prompt(estado, stdout);

    while( ganhou != 1)
    { 
        fgets(linha,BUF_SIZE,stdin);

        if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) 
        {
            COORDENADA coord = {*col - 'a', *lin - '1'};
            if (n_pos>0) 
            {
                atualiza_estado_pos(estado,n_pos);
                n_pos = 0;
            }

            jogar(estado, coord);
            guarda_tabuleiro(estado, stdout);
            prompt(estado, stdout);
        }

        ganhou = verifica_Vitoria( estado);

        if ( ganhou ) 
        {
            guarda_tabuleiro( estado, stdout);
            prompt(estado, stdout);
            jogador_vencedor( estado, stdout);
        }
  
/* Lê o comando Q, que retorna 0, o que faz com que a main pare o ciclo e o jogo fecha. */
        if(strcmp( linha, "Q\n" ) == 0 ) return 0;

/* Abre o ficheiro em modo writing(se o ficheiro não existir, cria-o), e guarda o tabuleiro */
        if(sscanf(linha, "gr %s",filename) == 1)
        {
            FILE *fp;
            fp = fopen(filename, "w");

            if (fp == NULL) printf("O ficheiro não abriu.\n");
/* Grava o tabuleiro no ficheiro. */
            comando_gr(estado, fp);
            estado->num_comando++;
            guarda_tabuleiro(estado, stdout);
            prompt(estado, stdout);
/* Fecha novamente o documento */
            fclose(fp);
            estado->num_comando++;  // ??????????????????????????
        }

/* Abre o ficheiro em modo reading caso exista, caso contrário apresenta o erro. */
        if(sscanf(linha, "ler %s",filename) == 1)
        {
            FILE *fp;
            fp = fopen(filename, "r");
            if (fp == NULL)  printf("O ficheiro não abriu.\n");
            else 
            {
/* Lê o tabuleiro que está no ficheiro e imprime. */
                comando_ler(fp, estado);

                guarda_tabuleiro(estado,stdout);
                prompt(estado, stdout);
              //  prompt(estado, stdout);
/* Fecha o ficheiro */
                fclose(fp);
            }
        }

        if(strcmp( linha, "movs\n" ) == 0)
        {
            comando_movs(estado,stdout);
            estado->num_comando++;
            guarda_tabuleiro(estado,stdout);
            prompt(estado, stdout);
        }


        if(sscanf(linha, "pos %d",&n_pos) == 1)
        {
            if (n_pos < estado->num_jogadas && n_pos>0 )   comando_pos(estado, n_pos);
            else 
            {
                n_pos = 0;
                fprintf(stdout, "Erro! A posição não existe!\n"); 
                estado->num_comando++;
                prompt(estado, stdout);
            }
        }

    }
    return ganhou;
}

/// FIM DO JOGO ///
