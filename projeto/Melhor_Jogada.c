#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "Interface.h"
#include "dados.h"
#include "listas.h"

/// ESTRATEGIA MINMAX ///

/**
\brief Função que executa o MinMax, retornando o valor de uma determinada jogada.
*/
int MinMax(ESTADO *estado,COORDENADA *coord, int alpha, int betha, int player_atual, int nosso_jogador)
{
    printf("\n\ninicio minmax\n");
    ESTADO *estado_copia = cria_estado_copia(estado);

    /* atualiza estado copia */
    int x = (*coord).linha;
    int y = (*coord).coluna;
    COORDENADA coord_ = {x , y};

    printf("coord ");
    printf("    %d  %d\n", coord_.linha, coord_.coluna);

    atualiza_estado(estado_copia, coord_);

    printf("atualiza de estado\n");

    /* verifica se o jogo acabou */
    int ganhou = avaliar_jogada(estado_copia, player_atual, nosso_jogador);
    if (ganhou !=0) return ganhou;

    LISTA Lista_coords =  cria_lista_coords_possiveis(estado);
    
    LISTA aux;

    int maxValor, valor, minValor;
    
    printf("dentro do minmax");

    /* se formos nos a jogar */
    if (player_atual)
    {   
        for (aux = Lista_coords; !(lista_esta_vazia(aux ) ) ; aux = aux->next )
        {
            valor = MinMax(estado_copia, aux->valor, alpha, betha, 0, nosso_jogador);
            maxValor = max(alpha, valor);
            if (betha <= alpha) break;
            free(estado_copia);
            return maxValor;
        }
    }
    else
    {
        for (aux = Lista_coords; !(lista_esta_vazia(aux ) ) ; aux = aux->next )
        {
            valor = MinMax(estado_copia ,aux->valor,alpha, betha, 1, nosso_jogador ); ///true
            minValor = min(minValor, valor);
            betha = min(betha, valor);
            if (betha <= alpha) break;
            free(estado_copia);
            return minValor;  
        }
    } 
}


/**
\brief Função que inicia o MinMax, retornando a melhor COORDENADA a ser efetuada.
*/
COORDENADA *Iniciar_MinMax(ESTADO *estado)
{
    ESTADO *estado_copia = cria_estado_copia(estado);

    LISTA Lista_coords =  cria_lista_coords_possiveis(estado);

    //printf("arroz");

    /* valor da melhor jogada possivel */
    int best_Move;
    /* coord melhor jogada possivel */
    COORDENADA *best_Coord ;
    /* if ( length_lista(Lista_coords) == 1 ) 
    {
        printf("eita");
        best_Coord = devolve_cabeca(Lista_coords);
    }
    else
    {*/
    /* dados auxiliares */
    LISTA aux = Lista_coords;
    int atual;

    best_Move = MinMax(estado_copia, aux->valor, -9999, 9999  , 0, estado->jogador_atual);
    printf("bestmove alterada\n");

    printf("\n\nArroo\n\n");
    best_Coord = devolve_cabeca(aux);

    for (aux=proximo(aux) ; !(lista_esta_vazia(aux ) ) ; aux = proximo(aux) )     //aux = aux->next )
    {
        atual = MinMax(estado_copia, aux->valor, -9999, 9999  , 0, estado->jogador_atual);
        printf("\n\n%d\n\n",atual);
        if (best_Coord == NULL || atual > best_Move)
        {
            best_Move = atual;
            best_Coord = devolve_cabeca(aux); //ou nao.... aqui esta o erro.. como o aux passa para aux->next..o endereco dacoor é mexido
        }
    }
   // }
    /* deveria se libertar a memoria do estado copia !!!!!!!!!!!!!!!!!! */
    free(estado_copia);
    return best_Coord ;
}

/**
\brief Função que devolve a melhor coordenada a ser efetuada pelo boot ou uma coordenada inválida se a jogada for inválida.
*/
COORDENADA jogada_boot(ESTADO *estado)
{
    COORDENADA *coord;
    COORDENADA coord_resul = { -1 , -1 };
    int ganhou = verifica_Vitoria(estado);
    if (!ganhou) 
    {
        printf("\nestou aqui inicio\n");

        coord = Iniciar_MinMax(estado);

        printf("sai dali yupii \n");
        int x = (*coord).linha;
        int y = (*coord).coluna;
        COORDENADA coord_test = {x,y};

        printf("coord feita final\n");
        printf("coord ");
        printf("    %d  %d\n", coord_test.linha, coord_test.coluna);
        
        if ( x>=0 && x<=7 &&  y>=0 && y<=7 )
        {
            if (verifica_jogada(estado, coord_test)) coord_resul = coord_test;
        }
        else fprintf(stdout, "A coordenada obtida é invalida\n");
    }
    else fprintf(stdout, "O jogo terminou\n");

    /// caso a coordenada seja inválida posso chamar a funcao que da a coord em funcao da distancia
    /// assim o codigo mesmo q falhe irá dar algum resultado

    return coord_resul;
}


/// da coordenada aleatoria ///

/**
\brief Função que devolve uma coordenada aleatória possível a ser jogada.
*/
COORDENADA da_coordenada(ESTADO *estado)
{
    COORDENADA coord = estado->ultima_jogada;

    COORDENADA coord1 = { coord.linha + 1 , coord.coluna + 1 };
    if (verifica_coord(coord1) && verifica_jogada(estado ,coord1)) return coord1;
    COORDENADA coord2 = { coord.linha + 1 , coord.coluna };
    if (verifica_coord(coord2) && verifica_jogada(estado ,coord2)) return coord2;
    COORDENADA coord3 = { coord.linha + 1 , coord.coluna - 1 };
    if (verifica_coord(coord3) && verifica_jogada(estado ,coord3)) return coord3;
    COORDENADA coord5 = { coord.linha - 1 , coord.coluna - 1 };
    if (verifica_coord(coord5) && verifica_jogada(estado ,coord5)) return coord5;
    COORDENADA coord6 = { coord.linha - 1, coord.coluna };
    if (verifica_coord(coord6) && verifica_jogada(estado ,coord6)) return coord6;
    COORDENADA coord7 = { coord.linha - 1 , coord.coluna + 1 };
    if (verifica_coord(coord7) && verifica_jogada(estado ,coord7)) return coord7;
    COORDENADA coord8 = { coord.linha , coord.coluna + 1 };
    if (verifica_coord(coord8) && verifica_jogada(estado ,coord8)) return coord8;
    COORDENADA coord4 = { coord.linha , coord.coluna - 1 };
    if (verifica_coord(coord4) && verifica_jogada(estado ,coord4)) return coord4;

}

/// COORDENADA ATRAVÉS DA MENOR DISTÃNCIA /// 

/**
\brief Função que devolve uma coordenada aleatória possível a ser jogada.
*/
float distancia_coord(COORDENADA coord, int player)
{
    COORDENADA coord_casa;
    if (player==1) 
    {
        coord_casa.coluna = 0;
        coord_casa.linha = 0;
    }
    else
    {
        coord_casa.coluna = 7;
        coord_casa.linha = 7;
    }
    int x = abs( coord_casa.coluna - coord.coluna ),
        y = abs( coord_casa.linha - coord.linha );
    float resul = ( x*x + y*y );
    /*float resul = x+y;*/
    return ( resul );
}

/**
\brief Função que devolve a coordenada, possível a ser jogada que se encontre a menor distância da casa do jogador.
*/
// funcao horrivel !!!!!!!!!!!!!!!!!!!!!!!!//
COORDENADA da_coordenada_distancia(ESTADO *estado)
{
    COORDENADA coord = estado->ultima_jogada;
    COORDENADA coord_result = coord;
    int dist_best = distancia_coord(coord, estado->jogador_atual);
    float i;

    COORDENADA coord1 = { coord.coluna + 1 , coord.linha + 1 };
    if (verifica_coord(coord1) && estado->tab[ coord1.linha ][ coord1.coluna ] != BRANCA) 
    {
        i = distancia_coord( coord1, estado->jogador_atual);
        if(  i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord1;
        }
    }
    
    COORDENADA coord2 = { coord.coluna + 1 , coord.linha };
    if (verifica_coord(coord2) && estado->tab[ coord2.linha ][ coord2.coluna ] != BRANCA)
    {
        i = distancia_coord( coord2, estado->jogador_atual);
        if( i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord2;
        }
    }

    COORDENADA coord3 = { coord.coluna + 1 , coord.linha - 1 };
    if (verifica_coord(coord3) && estado->tab[ coord3.linha ][ coord3.coluna ] != BRANCA) 
    {
        i = distancia_coord( coord3, estado->jogador_atual);
        if( i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord3;
        }
    }

    COORDENADA coord5 = { coord.coluna - 1 , coord.linha - 1 };
    if (verifica_coord(coord5) && estado->tab[ coord5.linha ][ coord5.coluna ] != BRANCA)
    {
        i = distancia_coord( coord5, estado->jogador_atual);
        if(  i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord5;
        }
    }

    COORDENADA coord6 = { coord.coluna - 1, coord.linha };
    if (verifica_coord(coord6) && estado->tab[ coord6.linha ][ coord6.coluna ] != BRANCA)
    {
        i = distancia_coord( coord6, estado->jogador_atual);
        if(  i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord6;
        }
    } 

    COORDENADA coord7 = { coord.coluna - 1 , coord.linha + 1 };
    if (verifica_coord(coord7) && estado->tab[ coord7.linha ][ coord7.coluna ] != BRANCA)
    {
        i = distancia_coord( coord7, estado->jogador_atual);
        if( i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord7;
        }
    } 

    COORDENADA coord8 = { coord.coluna , coord.linha + 1 };
    if (verifica_coord(coord8) && estado->tab[ coord8.linha ][ coord8.coluna ] != BRANCA)
    {
        i = distancia_coord( coord8, estado->jogador_atual);
        if(i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord8;
        }
    }

    COORDENADA coord4 = { coord.coluna , coord.linha - 1 };
    if (verifica_coord(coord4) && estado->tab[ coord4.linha ][ coord4.coluna ] != BRANCA ) 
    {
        i = distancia_coord( coord4, estado->jogador_atual);
        if( i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord4;
        }
    }  
    
    /* (coord_result.coluna == coord.coluna && coord_result.linha == coord.linha ) ||*/
    
    /*
    LISTA lista_coords = cria_lista_coords_possiveis(estado);
    COORDENADA *coord_;
    COORDENADA aux;
    while (!lista_esta_vazia(lista_coords))
    {
        coord_ = devolve_cabeca(lista_coords);
        aux.linha = ((*coord_).linha) ;
        aux.coluna = ((*coord_).coluna);

        if (verifica_coord(aux) && estado->tab[ aux.linha ][ aux.coluna ] != BRANCA ) 
        {
            i = distancia_coord( aux , estado->jogador_atual);
            if( i<=dist_best ) 
            {
                dist_best = i;
                coord_result = aux;
            }
        } 
        lista_coords = remove_cabeca(lista_coords); 
    } */

    return coord_result;
}


COORDENADA obtem_coord_atraves_da_distancia(ESTADO *estado)
{
    COORDENADA coord = estado->ultima_jogada,
               coord_result = coord,
               aux;
               
    COORDENADA *coord_ = (COORDENADA*)malloc(sizeof (COORDENADA)) ;
    LISTA lista_coords = cria_lista_coords_possiveis(estado);

    int dist_best = distancia_coord(coord, estado->jogador_atual);
    float i; 
    
    /* (coord_result.coluna == coord.coluna && coord_result.linha == coord.linha ) ||*/  
    while ( !lista_esta_vazia(lista_coords) )
    {
        coord_ = devolve_cabeca(lista_coords);

        aux.linha = ((*coord_).linha) ;
        aux.coluna = ((*coord_).coluna);

        if (verifica_coord(aux) && estado->tab[ aux.linha ][ aux.coluna ] != BRANCA ) 
        {
            i = distancia_coord( aux , estado->jogador_atual);
            if( i <= dist_best ) 
            {
                dist_best = i;
                coord_result = aux;
            }
        } 
        lista_coords = remove_cabeca(lista_coords); 
    } 
    free( coord_ );
    //free_lista ( lista_coords );
    free( lista_coords );
    return coord_result;
}