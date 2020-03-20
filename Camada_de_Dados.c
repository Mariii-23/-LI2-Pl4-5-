#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Logica_do_programa.h"
#include "Interface.h"


//DEFINE O ESTADO INICIAL
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
}

//ESTADO INICIAL
ESTADO *inicializador_estado()
{
    ESTADO *estado = (ESTADO *) malloc(sizeof(ESTADO));
    casas_inicial( estado->tab);
   // estado.jogadas = NULL;
    estado->num_jogadas = 0;
    estado->jogador_atual = 1;

    return estado;
}

//Procura onde se encotra a peca preta
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

//FUNCAO QUE DEVLOVE O ESTADO DE UMA PECA CONSOANTE AS COORDENADAS DADAS
CASA estado_casa(ESTADO estado, COORDENADA coordenada)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    CASA peca = estado.tab[x][y];
    return peca;
}

//FUNCAO QUE VERIFICA SE A JOGADA É POSSIVEL
int verificar_vizinho(COORDENADA coord_inicial, COORDENADA coord_final)
{
    int x, y, x_, y_, resul=0;
    x = coord_inicial.linha;
    y = coord_inicial.coluna; 
    x_ = coord_final.linha; 
    y_ = coord_final.coluna; 
    if ( (x==x_ && ( (y+1)==y_ || (y-1)==y_ )) || 
          y==y_ && ( (x+1)==x_ || (x-1)==x_ ) )
        resul=1;
    return resul;
}

//FUNCAO QUE VERIFICA SE HA CASAS DISPONIVEIS

//Verificar casa a direita
int verifica_casa_Direita(ESTADO *estado, COORDENADA coord_inicial)
{
    int x, y, resul=0;
    x = coord_inicial.linha;
    y = coord_inicial.coluna;  

    if (x!=7 && estado.tab[x-1][y] == VAZIA )
    {
        resul = 1;
    }
    return resul;
}

//Verificar casa a esquerda
int verifica_casa_Esquerda(ESTADO *estado, COORDENADA coord_inicial)
{
    int x, y, resul=0;
    x = coord_inicial.linha;
    y = coord_inicial.coluna;  

    if (x!=0 && estado.tab[x+1][y] == VAZIA )
    {
        resul = 1;
    }
    return resul;
}

//Verificar casa a acima
int verifica_casa_Acima(ESTADO *estado, COORDENADA coord_inicial)
{
    int x, y, resul=0;
    x = coord_inicial.linha;
    y = coord_inicial.coluna;  

    if (y!=0 && estado.tab[x][y+1] == VAZIA )
    {
        resul = 1;
    }
    return resul;
}

//Verificar casa a baixa
int verifica_casa_Baixo(ESTADO *estado, COORDENADA coord_inicial)
{
    int x, y, resul=0;
    x = coord_inicial.linha;
    y = coord_inicial.coluna;  

    if (y!=7 && estado.tab[x][y-1] == VAZIA )
    {
        resul = 1;
    }
    return resul;
}

int verificar_casas_disponiveis(ESTADO *estado, COORDENADA coord_inicial)
{
    return ( verifica_casa_Direita(*estado, coord_inicial ) && verifica_casa_Esquerda(*estado, coord_inicial ) &&
             verifica_casa_Baixo(*estado, coord_inicial ) && verifica_casa_Acima(*estado, coord_inicial )   );
}

//faltam mais condicoes
int verifica_jogada(ESTADO *estado,COORDENADA pos_inicial, COORDENADA pos_final)
{
    int resul = 0;
    int x = pos_final.linha;
    int y = pos_final.coluna;
    CASA peca = estado->tab[x][y];

    if (peca == VAZIO && verificar_vizinho(pos_inicial, pos_final ))
    {
        resul = 1;
    }
    return resul;
}




int verifica_vencedor(ESTADO estado) {
    int r;
    COORDENADA c = encontra_peca_preta(estado);
    if ((c.linha = 7) && (c.coluna = 0)) || ((c.linha = 0) && (c.coluna = 7))
        r = 1;
    else 
        r = 0;

    return r;
}