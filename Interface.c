#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
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
    //printf("batata");
    for (linha=7; linha>=0; linha--)
    {
        if (stream == stdout) fprintf(stream, "%d ",linha+1);
        guarda_Linha( estado, linha, stream);
    }
   // printf("feijao");
    fprintf(stream, "\n");
    if (stream == stdout ) prompt(estado, stream);
   // printf("arroz");
}

/// !!!____COMANDOS___!!! ////

/// COMANDO LER ///

/**
\brief Guarda as jogadas
*/
void guarda_Jogadas_2(ESTADO *estado, COORDENADA coord1, COORDENADA coord2, int  n_jogada)
{
    estado->jogadas[ n_jogada ].jogador1 = coord1;
    if ( coord2.linha != -1 && coord2.coluna != -1  )
        estado->jogadas[ n_jogada ].jogador2 = coord2;
}

void guarda_Jogadas_1(ESTADO *estado, COORDENADA coord1, int  n_jogada)
{
    estado->jogadas[ n_jogada ].jogador1 = coord1;
}

/**
\brief Funcao auxilidar do comando ler, que atualiza a ultima coordenada e o jogador atual em funcao do resto.
*/
void ler_atualiza_estado_restante(ESTADO *estado)
{
    if ( estado->num_comando % 2 ) 
        {
            estado->ultima_jogada = estado->jogadas[ estado->num_jogadas ].jogador1;
            estado->jogador_atual = 2;
        }
        else
        {
            estado->ultima_jogada = estado->jogadas[ estado->num_jogadas - 1 ].jogador2;
            estado->jogador_atual = 1; 
        }
}


void ler_linha(ESTADO *estado, char linha[], int l)
{   
    char casa;
    for(int c = 0; c < 8; c++) 
    { 
        casa = linha[c];
        fprintf(stdout, "%c", casa);
        estado->tab[l][c]=casa;
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

    // por o estado todo a zero
    //estado = inicializador_estado();

    estado->num_comando = 1;
    estado->jogador_atual = 1;
    for( int l = 7; l >= 0; l--)
        {
            fscanf(fp, "%s", linha);
            ler_linha(estado, linha, l);
            fprintf(stdout,"\n");
        } 

    n_jogadas = estado->num_comando / 2 + 1;
    estado->num_jogadas = n_jogadas;

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
        // usar 2 funcoes...ou juntar?!
        //guarda_Jogadas_2(estado, coord1, coord2, l);
        guarda_Jogadas_1(estado, coord1, l);
    }

    ler_atualiza_estado_restante(estado);
}


void comando_teste_pos(ESTADO *estado, int n_jogadas ){
    int i, j;
    int tabuleiro[8][8];
    int cont=0, num;
    COORDENADA coord1 = estado->jogadas[cont].jogador1;
    COORDENADA coord2 = estado->jogadas[cont].jogador2;
    /*Cria um novo tabuleiro vazio. */
    for(i=7; i>=0; i--){
        for(j=0; j<=7; j++){
            if (i==4 && j==4){
                tabuleiro[i][j] = '#';
            }
            else {
                if (i==7 && j==7){
                    tabuleiro[i][j] = '2';
                } 
                else{
                    if(i==0 && j==0){
                        tabuleiro[i][j] = '1';
                    }
                    else{
                        tabuleiro[i][j] = '.';
                    } 
                }
            }
        }
    }
    for (num = 1 ; num <= n_jogadas ; num++ , cont++)
    {
        coord1 = estado->jogadas[cont].jogador1;
        coord2 = estado->jogadas[cont].jogador2;
        tabuleiro[coord1.coluna][coord1.linha] = '#';
        tabuleiro[coord2.coluna][coord2.linha] = '#';
        tabuleiro[i][j] = '#';
    }
        coord2 = estado->jogadas[cont - 1].jogador2; // penso q isto seja desnecessario
        tabuleiro[coord2.coluna][coord2.linha] = '*';

    /*Imprimir o novo tabuleiro. */
    printf("abcdefgh");
    for (i = 0; i < 8; i++)
    {
        printf("%d", i);
        for (j = 0; j < 8; j++)
        {
            printf("%c", tabuleiro[i][j]);
        }
    }
}


/*
void comando_pos(ESTADO *estado, int n_jogadas )
{
    int i,l ;
    CASA tabi[8][8];
    for (i=0; i<8 ; i++)
    {
        for(l=0; l<8; l++) tabi[i][l] = estado->tab[i][l];
    }
    JOGADAS jogadas;
    for (i=0; i < estado->num_jogadas ; i++); 
    {
        jogadas[i].jogador1 = estado->jogadas[i].jogador1;
        jogadas[i].jogador2 = estado->jogadas[i].jogador2;
    }
    int num_jogadas = estado->num_jogadas;
    int jogador_atual = estado->jogador_atual;
    int num_comando = estado->num_comando;

    estado = inicializador_estado();
    COORDENADA coord;
    for(i=0; i< n_jogadas ; i++)
    {
        coord = jogadas[i].jogador1;
        atualiza_estado(estado, coord);
        coord = jogadas[i].jogador2;
        atualiza_estado(estado,coord);
    }
} 
*/

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
    int dados=0;
  //  filename = "jogo.txt";
    int ganhou = 0;

    guarda_tabuleiro(estado, stdout);

    while( ganhou != 1)
    { 
        fgets(linha,BUF_SIZE,stdin);

        if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) 
        {
            COORDENADA coord = {*col - 'a', *lin - '1'};
            jogar(estado, coord);
            guarda_tabuleiro(estado, stdout);
        }

        ganhou = verifica_Vitoria( estado);

        if ( ganhou ) 
        {
            guarda_tabuleiro( estado, stdout);
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
            guarda_tabuleiro(estado, stdout);
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
/* Fecha o ficheiro */
                fclose(fp);
            }
        }

        if(strcmp( linha, "movs\n" ) == 0)
        {
            comando_movs(estado,stdout);
            estado->num_comando++;
            guarda_tabuleiro(estado,stdout);
        }


        if(sscanf(linha, "pos %d",&dados) == 1)
        {
            if (dados < estado->num_jogadas)   comando_teste_pos(estado, dados);
            else printf("Erro! A posição não existe!");
        }

    }
    return ganhou;
}

/// FIM DO JOGO ///
