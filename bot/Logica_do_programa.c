#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Interface.h"
#include "dados.h"

/// FUNÇÃO QUE MOSTRA O POS ///
void mostra_pos(ESTADO *estado, int n_jogadas ){
    int i, j;
    CASA tabuleiro[8][8];
    int cont=0, num;
    COORDENADA coord1 ;
    COORDENADA coord2 ;
    /*Cria um novo tabuleiro vazio. */
    for(i=7; i>=0; i--){
        for(j=0; j<=7; j++)
        {
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
        tabuleiro[coord1.linha][coord1.coluna] = '#';
        tabuleiro[coord2.linha][coord2.coluna] = '#';
    }
        tabuleiro[coord2.linha][coord2.coluna] = '*';
    /* Imprimir o novo tabuleiro. */
    mostra_tabuleiro(tabuleiro,stdout);
}


/// ATUALIZA O ESTADO ///

/**
\brief Função que altera o estado da peça.
*/
void altera_estado_peca(ESTADO *estado, COORDENADA coordenada, CASA mudar)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    estado->tab[x][y] = mudar;
}

/**
\brief Função que altera o estado da casa onde estava, para a qual se pretendia mover.
*/
void troca_posicoes(ESTADO *estado, COORDENADA pos_final)
{
    altera_estado_peca(estado, estado->ultima_jogada, BRANCA);
    altera_estado_peca(estado, pos_final, PRETA);
}

/**
\brief Função que altera o estado das JOGADAS, adicionando a ultima coordenada dada.
*/
void atualiza_JOGADAS(ESTADO *estado,COORDENADA coord_mudar)
{
    if (estado->jogador_atual == 2)   estado->jogadas[ estado->num_jogadas - 1].jogador2 = coord_mudar; 
    else                              estado->jogadas[ estado->num_jogadas - 1].jogador1 = coord_mudar;
}

/**
\brief Função que atualiza o num_jogadas do estado.
*/
void atualiza_Num_Jogadas(ESTADO *estado)
{
    int jog = estado->jogador_atual;
    if (jog == 1)  estado->num_jogadas += 1;
}

/**
\brief Função que atualiza o estado a cada jogada.
*/
void atualiza_estado(ESTADO *estado, COORDENADA coord_mudar) 
{
    troca_posicoes(estado, coord_mudar);
    atualiza_JOGADAS(estado,coord_mudar);
    if (estado->jogador_atual == 1)  estado->jogador_atual = 2;
    else                             estado->jogador_atual = 1;
    atualiza_Num_Jogadas(estado);
    estado->num_comando +=1 ;
    estado->ultima_jogada = coord_mudar;
}

/**
\brief Função que altera o estado do jogo cosoante a jogada efetuada.
*/
int jogar(ESTADO *estado, COORDENADA coord)
{
    int resul=0;
    int pode_jogar = verifica_jogada(estado, coord);
    
    if (pode_jogar)
    {
        atualiza_estado(estado, coord);
    }
    else
    {
        printf("\nJogada inválida.\n");
        estado->num_comando++;
    }
    resul = 1;

    return resul;
}

/// COMANDO LER ///
/// ATUALIZA EM FUNCAO DO COMANDO LER ///

/**
\brief Função que guarda as jogadas do estado.
*/
void guarda_Jogadas_2(ESTADO *estado, COORDENADA coord1, COORDENADA coord2, int  n_jogada)
{
    estado->jogadas[ n_jogada ].jogador1 = coord1;
    estado->jogadas[ n_jogada ].jogador2 = coord2;
}

/**
\brief Função que guarda as jogadas do estado.
*/
void guarda_Jogadas_1(ESTADO *estado, COORDENADA coord1, int  n_jogada)
{
    estado->jogadas[ n_jogada ].jogador1 = coord1;
}

/**
\brief Função que atualiza o estado lido através do comando ler.
*/
void atualiza_estado_comando_ler(ESTADO *estado)
{
    /*
    if ( estado->num_comando % 2 )  
    {
        estado->jogador_atual = 2;
        estado->ultima_jogada = estado->jogadas[ estado->num_jogadas +1 ].jogador1;
        estado->num_jogadas = (estado->num_comando / 2) + 1;
    }
    else                           
    {
        estado->jogador_atual = 1; 
        estado->ultima_jogada = estado->jogadas[ estado->num_jogadas ].jogador2;
        estado->num_jogadas = estado->num_comando / 2 ;
    }
    if (estado->jogador_atual == 1) estado->num_jogadas++; */


    if ( estado->num_comando % 2 )  
    {
        estado->jogador_atual = 2;
        estado->ultima_jogada = estado->jogadas[ estado->num_jogadas - 1 ].jogador1;
        //estado->num_jogadas = (estado->num_comando / 2) + 1;
    }
    else                           
    {
        estado->jogador_atual = 1; 
        estado->ultima_jogada = estado->jogadas[ estado->num_jogadas - 2 ].jogador2;
        //estado->num_jogadas = estado->num_comando / 2 ;
    }
}

/// ATUALIZA ESTADO EM FUNCAO DO POS ///

/**
\brief Função que atualiza o tabuleiro do estado em função do comando pos dado.
*/
void atualiza_tabuleiro_pos(ESTADO *estado, int n_jogadas)
{
    int num;
    COORDENADA coord1 , coord2 ;
    estado->tab[4][4] = BRANCA;
    for (num = 0 ; num < n_jogadas ; num++)
    {
        coord1 = estado->jogadas[num].jogador1;
        coord2 = estado->jogadas[num].jogador2;
        estado->tab[ coord1.linha ][ coord1.coluna ] = BRANCA;
        estado->tab[ coord2.linha ][ coord2.coluna ] = BRANCA;
    }
    estado->tab[ coord2.linha ][ coord2.coluna ] = PRETA;
    estado->tab[0][0] = UM;
}

/**
\brief Função que atualiza o estado em função do comando pos dado.
*/
void atualiza_estado_pos(ESTADO *estado,int n_pos)
{
    int linha;

    JOGADAS jogadas;
    for (linha=0; linha < estado->num_jogadas ; linha++)
    {
        jogadas[linha].jogador1 = estado->jogadas[linha].jogador1;
        jogadas[linha].jogador2 = estado->jogadas[linha].jogador2;
    }

    int num_comando = estado->num_comando;

    /* Inicializa o tabuleiro do estado */
    casas_inicial(estado);
    /* Atualiza o jogador_atual do estado */
    estado->jogador_atual = 1;

    /* Atualiza a lista das jogadas do estado */  /*Provavelmente desnecesario*/
    for (linha=0; linha < n_pos; linha++)
    {
        estado->jogadas[linha].jogador1 = jogadas[linha].jogador1;
        estado->jogadas[linha].jogador2 = jogadas[linha].jogador2;
    }
    
    /* Atualiza  o tabuleiro do estado */
    atualiza_tabuleiro_pos(estado,n_pos);
    /* Atualiza a ultima coordenad do estado */
    estado->ultima_jogada = estado->jogadas[ n_pos-1 ].jogador2;
    /* Atualiza o num_jogadas do estado */
    estado->num_jogadas = n_pos+1;
}