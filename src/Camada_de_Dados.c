#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Logica_do_programa.h"
#include "Interface.h"
#include "dados.h"

/// ESTADO INICIAL ///
/**
\brief Função que define cada casa do jogo quando este é iniciado.
*/
void casas_inicial(ESTADO *estado)
{
    int i, j;
    for(i=7; i>=0; i--)
    {
        for(j=0; j<=7; j++)
        {
            if (i==4 && j==4)
            {
                estado->tab[i][j] = '*';
            }
            else 
            {
                if (i==7 && j==7)
                {
                    estado->tab[i][j] = '2';
                } 
                else
                {
                    if(i==0 && j==0)
                    {
                        estado->tab[i][j] = '1';
                    }
                    else
                    {
                        estado->tab[i][j] = '.';
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
    ESTADO *estado = (ESTADO *) calloc(1, sizeof(ESTADO));
    casas_inicial(estado);
    estado->num_jogadas = 1;
    estado->jogador_atual = 1;
    estado->num_comando = 1;
    estado->ultima_jogada.coluna = 4;  
    estado->ultima_jogada.linha = 4;  
    return estado;
}

/// FUNCOES AUXILIARES ///
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
int verifica_jogada(ESTADO *estado, COORDENADA pos_final)
{
    int x = pos_final.linha;
    int y = pos_final.coluna;
    CASA peca = estado->tab[x][y];
    int vaziaa = peca != '#';  /* Exatamente igual: peca == '.' || peca == '2' || peca == '1'  */
    
    return ( vaziaa  && verifica_se_e_vizinho(estado->ultima_jogada, pos_final )  );
}

/// VERIFICA SE ALGUEM GANHOU ///

/**
\brief Função que verifica se a casa está disponível para se mover para lá.
*/
int verifica_casa_ocupada(ESTADO *estado, COORDENADA coord)
{
    int x, y, resul = 1;
    x = coord.linha;
    y = coord.coluna; 

    if (x>=0 && x<=7 && y>=0 && y<=7 )
    {
        if (estado->tab[x][y] == VAZIO ) resul = 0;
    }
    /* printf("%d\n", resul); */
    return resul;
}

/**
\brief Função principal que verifica se todas as casas vizinhas se encontram ocupadas.
*/
int verificar_casas_ocupadas(ESTADO *estado)
{
    COORDENADA coord = estado->ultima_jogada;
    int resul;
    COORDENADA coord1 = { coord.coluna + 1 , coord.linha + 1 };
    COORDENADA coord2 = { coord.coluna + 1 , coord.linha };
    COORDENADA coord3 = { coord.coluna + 1 , coord.linha - 1 };
    COORDENADA coord5 = { coord.coluna - 1 , coord.linha - 1 };
    COORDENADA coord6 = { coord.coluna - 1, coord.linha };
    COORDENADA coord7 = { coord.coluna - 1 , coord.linha + 1 };
    COORDENADA coord8 = { coord.coluna , coord.linha + 1 };
    COORDENADA coord4 = { coord.coluna , coord.linha - 1 };
    resul = ( verifica_casa_ocupada( estado , coord1 ) && verifica_casa_ocupada( estado , coord2 ) &&
              verifica_casa_ocupada( estado , coord3 ) && verifica_casa_ocupada( estado , coord4 ) &&
              verifica_casa_ocupada( estado , coord5 ) && verifica_casa_ocupada( estado , coord6 ) &&
              verifica_casa_ocupada( estado , coord7 ) && verifica_casa_ocupada( estado , coord8 )   );
    /*printf("r: %d\n", resul);
    printf("%d\n", verifica_casa_ocupada( estado , coord1 ));
    printf("%d\n", verifica_casa_ocupada( estado , coord2 ));
    printf("%d\n", verifica_casa_ocupada( estado , coord3 ));
    printf("%d\n", verifica_casa_ocupada( estado , coord4 ));
    printf("%d\n", verifica_casa_ocupada( estado , coord5 ));
    printf("%d\n", verifica_casa_ocupada( estado , coord6 ));
    printf("%d\n", verifica_casa_ocupada( estado , coord7 ));
    printf("%d\n", verifica_casa_ocupada( estado , coord8 ));*/
    return resul;
}

/**
\brief Função que verifica se a peça preta se encontra na casa 1 ou 2.
*/
int verifica_vencedor(ESTADO *estado) 
{
    COORDENADA coord = estado->ultima_jogada;
    int r = ( coord.linha == 0  && coord.coluna == 0) ||
            ( coord.linha == 7  && coord.coluna == 7) ;
    return r;
}

/**
\brief Função principal que verifica se existe vencedor.
*/
int verifica_Vitoria(ESTADO *estado)
{
     return ( verifica_vencedor(estado) || verificar_casas_ocupadas(estado) );
}