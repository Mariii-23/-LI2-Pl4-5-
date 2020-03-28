#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Logica_do_programa.h"
#include "Interface.h"
#include "dados.h"


/**
\brief Função que define cada casa do jogo quando este é iniciado.
*/
void casas_inicial(CASA tabi[8][8])
{
    int i, j;
    for(i=7; i>=0; i--)
    {
        for(j=0; j<=7; j++)
        {
            if (i==4 && j==4)
            {
                tabi[i][j] = '#';
            }
            else 
            {
                if (i==7 && j==7)
                {
                    tabi[i][j] = '2';
                } 
                else
                {
                    if(i==0 && j==0)
                    {
                        tabi[i][j] = '1';
                    }
                    else
                    {
                        tabi[i][j] = '.';
                    } 
                }   
            }         
        }
    }  
}

/**
\brief Função que define o estado inicial do jogo.
*/
ESTADO *inicializador_estado()
{
    ESTADO *estado = (ESTADO *) malloc(sizeof(ESTADO));
    casas_inicial(estado->tab);
    estado->num_jogadas = 0;
    estado->jogador_atual = 1;
    estado->num_comando = 1;

    estado->ultima_jogada.coluna = 4;  
    estado->ultima_jogada.linha = 4;  

   // estado->jogadas = NULL;
    return estado;
}

/**
\brief Função que retorna a posição da peça preta no tabuleiro.
*/
COORDENADA encontra_peca_preta(ESTADO estado)
{
    int i,j;
    COORDENADA coord;

    for (i=0; i<8 ; i++)
    {
        for (j=0; j<8; j++)
        {
            if (estado.tab[i][j])
            {
                coord.linha = i;
                coord.coluna = j;
            }
        }
    }
    return coord;
}

/**
\brief Função que devolve o estado de cada peça consoante as coordenadas dadas.
*/
CASA estado_casa(ESTADO estado, COORDENADA coordenada)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    CASA peca = estado.tab[x][y];
    return peca;
}

/**
\brief Função que verifica se a jogada é possível.
*/
int verifica_se_e_vizinho(COORDENADA coord_inicial, COORDENADA coord_final)
{
    int x, y, x_, y_, resul=0;

    x = coord_inicial.linha;
    y = coord_inicial.coluna; 
    x_ = coord_final.linha; 
    y_ = coord_final.coluna; 

    if  (   (x == x_ && abs (y_ - y) == 1 ) || 
            (y == y_ && abs (x_ - x) == 1 ) ||
            ( abs(x_- x) == 1 && abs(y_ - y) == 1 ) 
        )
        resul=1;
    return resul;
}

/**
\brief Função principal que verifica se é possível executar a jogada.
*/
int verifica_jogada(ESTADO *estado,COORDENADA pos_inicial, COORDENADA pos_final)
{
    int x = pos_final.linha;
    int y = pos_final.coluna;
    CASA peca = estado->tab[x][y];
    int vaziaa = peca == '.' || peca == '2' || peca == '1' ;
    
    return ( vaziaa  && verifica_se_e_vizinho(pos_inicial, pos_final )  );
}

//FUNCAO QUE VERIFICA SE HA CASAS DISPONIVEIS AO REDOR DA PECA PRETA

/**
\brief Função que verifica se a casa da direita está disponível para se mover para lá.
*/
int verifica_casa_Direita(ESTADO *estado, COORDENADA coord)
{
    int x, y, resul=0;
    x = coord.linha;
    y = coord.coluna;  

    if (x!=7 && estado->tab[x+1][y] == VAZIO )
    {
        resul = 1;
    }
    return resul;
}

/**
\brief Função que verifica se a casa da esquerda está disponível para se mover para lá.
*/
int verifica_casa_Esquerda(ESTADO *estado, COORDENADA coord)
{
    int x, y, resul=0;
    x = coord.linha;
    y = coord.coluna;  

    if (y!=0 && estado->tab[x-1][y] == VAZIO )
    {
        resul = 1;
    }
    return resul;
}

/**
\brief Função que verifica se a casa acima está disponível para se mover para lá.
*/
int verifica_casa_Acima(ESTADO *estado, COORDENADA coord)
{
    int x, y, resul=0;
    x = coord.linha;
    y = coord.coluna;  

    if (x!=8 && estado->tab[x][y+1] == VAZIO )
    {
        resul = 1;
    }
    return resul;
}

/**
\brief Função que verifica se a casa abaixo está disponível para se mover para lá.
*/
int verifica_casa_Baixo(ESTADO *estado, COORDENADA coord)
{
    int x, y, resul=0;
    x = coord.linha;
    y = coord.coluna;  

    if (x!=0 && estado->tab[x][y-1] == VAZIO )
    {
        resul = 1;
    }
    return resul;
}

/**
\brief Função principal que verifica se a casa pretendida está disponível para se mover para lá.
*/
int verificar_casas_disponiveis(ESTADO *estado, COORDENADA coord)
{
    return ( verifica_casa_Direita(estado, coord) &&  verifica_casa_Esquerda(estado, coord) &&
             verifica_casa_Baixo(estado, coord)   &&  verifica_casa_Acima(estado, coord)   );
}

/**
\brief Função principal que verifica se todas as casas vizinhas se encontram ocupadas.
*/
int verificar_casas_ocupadas(ESTADO *estado, COORDENADA coord)
{
    return ( !verifica_casa_Direita(estado, coord) &&  !verifica_casa_Esquerda(estado, coord) &&
             !verifica_casa_Baixo(estado, coord)   &&  !verifica_casa_Acima(estado, coord)   );
}

/**
\brief Função que verifica se a peça preta se encontra na casa 1 ou 2.
*/
int verifica_vencedor(ESTADO estado) 
{
    COORDENADA coord = estado.ultima_jogada;
    int r = ( coord.linha == 0  && coord.coluna == 0) ||
            ( coord.linha == 7 && coord.coluna == 7) ;

    return r;
}

/**
\brief Função principal que verifica se existe vencedor.
*/

//ta mal
int verifica_Vitoria(ESTADO *estado,COORDENADA coord)
{
    COORDENADA peca = estado->ultima_jogada;
    return ( verifica_vencedor(*estado) || verificar_casas_ocupadas(estado, peca ) );
}
