#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "Melhor_Jogada.h"
#include "dados.h"

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
\brief Função que que imprime apenas as pecas de um determinado tabuleiro .
*/
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
            casa = tab[linha][coluna];
            fputc(casa, stream);
        }
        fprintf(stream, "\n");
    }
    fprintf(stream, "\n");
}


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
    fprintf(stream, "\n"); /*apagar depois*/
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

/// COMANDO POS ///
/**
\brief Executa o comando pos para retroceder o jogo.
*/
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
    else
    {
        if(stream!=stdout)
        {
            if (num <10)  fprintf(stream, "0%d: %c%d %c%d\n", num, coord1.coluna + 'a', coord1.linha + 1, coord2.coluna + 'a', coord2.linha + 1 );
            else          fprintf(stream, "%d: %c%d %c%d\n", num, coord1.coluna + 'a', coord1.linha + 1, coord2.coluna  + 'a', coord2.linha + 1 );
        }
    }
    
}

void movs(ESTADO *estado)
{
    comando_movs(estado,stdout);
    estado->num_comando++;
    guarda_tabuleiro(estado,stdout);
    prompt(estado, stdout);
}

/// COMANDO GRAVAR ///
/**
\brief Executa o comendo gr para guardar o tabuleiro do jogo no ficheiro.
*/
void comando_gr(ESTADO *estado, FILE *stream) {
    guarda_tabuleiro(estado, stream);
    comando_movs(estado, stream);
}

void gr(ESTADO *estado, char *filename)
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
    estado->num_comando++;  
}

/// COAMANDO LER ///

/**
\brief Função que atualiza o tabuleiro de um estado atravé de um ficheiro.
*/
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
    char linha[BUF_SIZE];
    int l ;
    int n_comando_inicial = estado->num_comando;
    char col1[2], lin1[2];
    char col2[2], lin2[2];
    estado->num_comando = 0;

    for( l = 7; l >= 0; l--)
    {
        fgets(linha, BUF_SIZE, fp); 
        ler_linha(estado, linha, l);
    } 
    fgets(linha,BUF_SIZE, fp);

    while ( fgets(linha,BUF_SIZE, fp) != NULL  )
    {
       if ( sscanf( linha , "%d: %[a-h]%[1-8] %[a-h]%[1-8]", &l, col1, lin1, col2, lin2) == 5)
       {   
            coord1.linha = *lin1 - '1' ;      coord1.coluna = *col1 - 'a';
            coord2.linha = *lin2 - '1' ;      coord2.coluna = *col2 - 'a';
            guarda_Jogadas_2(estado, coord1, coord2, l-1);
            estado->num_comando = 2*l;
        }
        else
        {
            sscanf( linha, "%d: %[a-h]%[1-8]",&l, col1, lin1);
            coord1.linha = *lin1 - '1' ;
            coord1.coluna = *col1 - 'a';
            guarda_Jogadas_1(estado, coord1, l-1);
            estado->num_comando = 2*l - 1;
        }
    }
    estado->num_jogadas = l;
    atualiza_estado_comando_ler(estado);
    estado->num_comando = n_comando_inicial+1;
}

void ler(ESTADO *estado, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)  
    {
        printf("O ficheiro não abriu.\n");
        guarda_tabuleiro(estado, stdout);
        prompt(estado, stdout);
    }
    else 
    {
/* Lê o tabuleiro que está no ficheiro e imprime. */
        comando_ler(fp, estado);

        guarda_tabuleiro(estado,stdout);
        prompt(estado, stdout);
/* Fecha o ficheiro */
        fclose(fp);
    }
}

/// INTERPRETADOR ///

/**
\brief Intrepretador do jogo.
*/
int interpretador(ESTADO *estado) 
{
    char linha[BUF_SIZE];
    char filename[BUF_SIZE] = "jogo.txt" ;
    char col[2], lin[2];
    int n_pos=0;
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

        if ( ganhou )  jogador_vencedor( estado, stdout);
  
/* Lê o comando Q, que retorna 0, o que faz com que a main pare o ciclo e o jogo fecha. */
        if(strcmp( linha, "Q\n" ) == 0 || strcmp( linha, "q\n" ) == 0 ) return 0;

/* Abre o ficheiro em modo writing(se o ficheiro não existir, cria-o), e guarda o tabuleiro */
        if(sscanf(linha, "gr %s",filename) == 1)      gr(estado, filename);

/* Abre o ficheiro em modo reading caso exista, caso contrário apresenta o erro. */
        if(sscanf(linha, "ler %s",filename) == 1)     ler(estado, filename);

        if(strcmp( linha, "movs\n" ) == 0)           movs(estado);


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

        
        if(strcmp( linha, "jog\n" ) == 0)
        {
            /* Atualizar pos */
            if (n_pos>0) 
            {
                atualiza_estado_pos(estado,n_pos);
                n_pos = 0;
            }
          /*
            COORDENADA coord_comamdo_jog = jogada_boot(estado);
            int x = coord_comamdo_jog.linha,
                y = coord_comamdo_jog.coluna;

            printf(" sai do jogada boot\n");

            if( x>=0 && x<=7 &&  y>=0 && y<=7 && verifica_jogada(estado, coord_comamdo_jog))
            {
                fprintf(stdout, "A melhor coordenada a ser efetuada será %c %c.\n", coord_comamdo_jog.coluna + 'a', coord_comamdo_jog.linha + '1' );

                jogar(estado, coord_comamdo_jog);
                guarda_tabuleiro(estado, stdout);
                prompt(estado, stdout);

                ganhou = verifica_Vitoria( estado);

                if ( ganhou ) 
                {
                    jogador_vencedor( estado, stdout);
                }
            }
            else
            {
                fprintf(stdout,"O comando jogar falhou.\n");
                estado->num_comando++;
                guarda_tabuleiro(estado, stdout);
                prompt(estado, stdout);
            }*/

            COORDENADA coord = da_coordenada_distancia(estado);
            //COORDENADA coord = da_coordenada(estado);

            /*deveria dar este */
            //COORDENADA coord = obtem_coord_atraves_da_distancia( estado );
            if( verifica_coord(coord) && verifica_jogada(estado, coord))
            {            
                jogar(estado, coord);
                guarda_tabuleiro(estado, stdout);
                prompt(estado, stdout);

                ganhou = verifica_Vitoria( estado);
                if ( ganhou )  jogador_vencedor( estado, stdout);
            }
            else
            {
                coord = da_coordenada(estado);
                
                if( verifica_coord(coord) && verifica_jogada(estado, coord))
                {            
                    jogar(estado, coord);
                    guarda_tabuleiro(estado, stdout);
                    prompt(estado, stdout);

                    ganhou = verifica_Vitoria( estado);
                    if ( ganhou )  jogador_vencedor( estado, stdout);
                }
                else
                {
                    fprintf(stdout,"O comando jogar falhou.\n");
                    estado->num_comando++;
                    guarda_tabuleiro(estado, stdout);
                    prompt(estado, stdout);
                }  
            }
            /*
            {
                fprintf(stdout,"O comando jogar falhou.\n");
                estado->num_comando++;
                guarda_tabuleiro(estado, stdout);
                prompt(estado, stdout);
            }*/
        }
    }
    return ganhou;
}

/// FIM DO JOGO ///
