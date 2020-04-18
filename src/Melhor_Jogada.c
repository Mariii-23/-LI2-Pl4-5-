#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "Interface.h"
#include "dados.h"
#include "listas.h"

/// FUNCAO AUXILIARES ///

/**
\brief Função que cria uma cópia do ESTADO.
*/
ESTADO *cria_estado_copia(ESTADO *estado)
{
    ESTADO *estado_copia = (ESTADO *) calloc(1, sizeof(ESTADO));
    int i,j;
    for(i=0 ; i<8; i++)
    {
        for(j=0; j<8; j++) estado_copia->tab[i][j] = estado->tab[i][j];
    }
    estado_copia->num_jogadas = estado->num_jogadas;
    estado_copia->jogador_atual = estado->jogador_atual;
    estado_copia->num_comando = estado->num_comando;
    estado_copia->ultima_jogada.coluna = estado->ultima_jogada.coluna;  
    estado_copia->ultima_jogada.linha = estado->ultima_jogada.linha;
    
    for(i=0; i<estado->num_jogadas; i++)
    {
        estado_copia->jogadas[i].jogador1 = estado->jogadas[i].jogador1;
        estado_copia->jogadas[i].jogador2 = estado->jogadas[i].jogador2;
    }
    if (estado->jogador_atual==2)  estado_copia->jogadas[i].jogador1 = estado->jogadas[i].jogador1;

    return estado_copia;
}


/**
\brief Função que devolve o menor valor de dois.
*/
int min(int a, int b)
{
    int resul = a;
    if (a>b) resul = b;
    return resul;
}

/**
\brief Função que devolve o maior alor de dois.
*/
int max(int a, int b)
{
    int resul = a;
    if (a<b) resul = b;
    return resul;
}

/**
\brief Função que verifica se uma COORDENADA é válida.
*/
int verifica_coord(COORDENADA coord)
{
    int x = coord.linha;
    int y = coord.coluna;
    return ( x>=0 && x<=7 &&  y>=0 && y<=7 );
}

/// LISTA DE COORDENADAS POSSÍVEIS A SEREM EXECUTADAS ///

/**
\brief Função auxiliar que insere a coordenada na lista se esta for uma possível coordenada a ser efetuada.
*/
LISTA adiciona_lista(LISTA lista, ESTADO *estado, COORDENADA coord)
{
    if ( verifica_coord(coord)   &&    estado->tab[ coord.linha ][ coord.coluna ] == BRANCA ); 
    {
        lista = insere_cabeca(lista, &coord);
    }  
    return lista;
}

/**
\brief Função principal que returna uma LISTA de coordenadas possíveis a serem efetuadas.
*/
LISTA cria_lista_coords_possiveis(ESTADO *estado)
{
    LISTA lista = criar_lista(); 

    COORDENADA coord = estado->ultima_jogada;

    COORDENADA coord1 = { coord.linha + 1 , coord.coluna + 1 };
    lista = adiciona_lista(lista, estado, coord1);
    COORDENADA coord2 = { coord.linha + 1 , coord.coluna };
    lista = adiciona_lista(lista, estado, coord2);
    COORDENADA coord3 = { coord.linha + 1 , coord.coluna - 1 };
    lista = adiciona_lista(lista, estado, coord3);
    COORDENADA coord5 = { coord.linha - 1 , coord.coluna - 1 };
    lista = adiciona_lista(lista, estado, coord5);
    COORDENADA coord6 = { coord.linha - 1, coord.coluna };
    lista = adiciona_lista(lista, estado, coord6);
    COORDENADA coord7 = { coord.linha - 1 , coord.coluna + 1 };
    lista = adiciona_lista(lista, estado, coord7);
    COORDENADA coord8 = { coord.linha , coord.coluna + 1 };
    lista = adiciona_lista(lista, estado, coord8);
    COORDENADA coord4 = { coord.linha , coord.coluna - 1 };
    lista = adiciona_lista(lista, estado, coord4);
    return lista;
}

/// AVALIAR UMA JOGADA ///
/**
\brief Função que verifica se ganhou em casa, atribuindo os respetivos pontos.
*/
int ganhou_em_casa(ESTADO *estado,int player, int nosso_player)
{
    int resul=0;
    int x = estado->ultima_jogada.linha;
    int y = estado->ultima_jogada.coluna;

    if (estado->jogador_atual==1 && nosso_player==1 && x == 0 && y == 0) resul = 1;
    else
    {
        if (estado->jogador_atual==2 && nosso_player==2 && x == 7 && y == 7) resul = 1;
        else 
        {
            if ((x == 0 && y == 0) || (x == 7 && y == 7)) resul = -1;
        }
    }
    return resul; 
}

/**
\brief Função que verifica se alguém ganhou, obrigando o outro jogador a jogar para a casa do adversario .
*/
int encurralado_casa(ESTADO *estado, int player, int nosso_player)
{
    int resul = 0;
    int ganhou_casa = ganhou_em_casa(estado,player, nosso_player);
    int valor = verificar_casas_ocupadas(estado);
    if  (ganhou_em_casa!=0 && valor ) resul = 2 * ganhou_casa;
    return resul;
}

/**
\brief Função que verifica se alguém ganhou encurralando o outro jogador .
*/
int encurralado_jogo(ESTADO *estado, int player)
{
    int resul = 0;
    int valor = verificar_casas_ocupadas(estado);
    if (player) resul = 3 * valor;
    else resul = -3 * valor;
    return resul;
}

/**
\brief Função que verifica se alguém ganhou encurralado, atribuindo pontos.
*/
int ganhou_encurralado(ESTADO *estado,int player, int nosso_player)
{
    int resul = 0;
    int valor = encurralado_jogo(estado, player);
    if (valor != 0 ) resul = valor;
    else resul = encurralado_casa(estado,player, nosso_player);
    return resul;
}


/// AVALIAR JOGADA ///
/**
\brief Função PRINCIPAL que avalia uma jogada. 
      (NOTA: quando o player == True ou seja 1, significa que player == nosso_player)
*/
int avaliar_jogada(ESTADO *estado,int player, int nosso_player)
{
    int resul = ganhou_encurralado(estado, player, nosso_player);
    if (resul == 0) resul = ganhou_em_casa(estado, player, nosso_player);
    return resul;
}


/// ESTRATEGIA MINMAX ///

/**
\brief Função que executa o MinMax, retornando o valor de uma determinada jogada.
*/
int MinMax(ESTADO *estado,COORDENADA *coord, int alpha, int betha, int player_atual, int nosso_jogador)
{
    printf("inicio minmax\n");
    ESTADO *estado_copia = cria_estado_copia(estado);

    printf("estado copia\n");

    /* atualiza estado copia */
    printf("prob\n");
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

    printf("passei do estado copia\n");

    LISTA Lista_coords =  cria_lista_coords_possiveis(estado);

    printf("passei da lista\n");

    //printf("arroz");

    /* valor da melhor jogada possivel */
    int best_Move;
    /* coord melhor jogada possivel */
    COORDENADA *best_Coord ;
    printf("aqui estou 1\n");

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

        printf("aqui estou2\n");

        best_Move = MinMax(estado_copia, aux->valor, -9999, 9999  , 0, estado->jogador_atual);
        printf("bestmove alterada");
        best_Coord = devolve_cabeca(aux);

        for (aux ; !(lista_esta_vazia(aux ) ) ; aux = proximo(aux) )     //aux = aux->next )
        {
            atual = MinMax(estado_copia, aux->valor, -9999, 9999  , 0, estado->jogador_atual);
            if (best_Coord == NULL || atual > best_Move)
            {
                best_Move = atual;
                best_Coord = devolve_cabeca(aux); //ou nao.... aqui esta o erro.. como o aux passa para aux->next..o endereco dacoor é mexido
            }
        }
   // }
    /* deveria se libertar a memoria do estado copia !!!!!!!!!!!!!!!!!! */

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

        if (verifica_jogada(estado, coord_test)) coord_resul = coord_test;
        else fprintf(stdout, "A coordenada obtida é invalida\n");
    }
    else fprintf(stdout, "O jogo terminou\n");
    return coord_resul;
}