
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "Interface.h"
#include "dados.h"
#include "listas.h"

typedef struct {
  /** O tabuleiro */
  CASA matriz[8][8];
  int player_atual;
  int nosso_player;
  COORDENADA last_coord;
} ESTADO_simples;

typedef COORDENADA COORDENADAS[32];

typedef struct {
  int valor;
  COORDENADAS lista;
} Lista_coord;

typedef struct {
  int valor;
  COORDENADA coord;
} Melhor_jogada;

#define pontos_casa_ocupada  5;

int min(int a, int b)
{
    int resul = a;
    if (a>b) resul = b;
    return resul;
}
int max(int a, int b)
{
    int resul = a;
    if (a<b) resul = b;
    return resul;
}


////////////////////////////////////
//// Estado para estado simples ////////
/////////////////////////////////////

ESTADO_simples *troca_estado_estado_simples(ESTADO *estado)
{
    ESTADO_simples *e = (ESTADO_simples *)malloc(sizeof(ESTADO_simples));
    e->last_coord = estado->ultima_jogada;
    for(int i=0; i<=7; i++)
    {
        for (int j=0; j<=7; j++)  e->matriz[i][j] = estado->tab[i][j];
    }
    e->nosso_player = estado->jogador_atual;
    e->player_atual = estado->jogador_atual;
    return e;
}


///// cria lista das coords atraves de LISTA

void adiciona_lista_(Lista_coord *lista, ESTADO_simples *estado, COORDENADA coord)
{
    if (estado->matriz[ coord.linha ][ coord.coluna ] == BRANCA ) 
    {
        /// nao tenho a certeza se +é assim  q a coord é inserida
        insere_cabeca(lista, &coord);
    }  
}


LISTA *cria_lista_coords_possiveis_(ESTADO_simples *estado)
{
    LISTA *lista = criar_lista();
    COORDENADA coord = estado->last_coord;

    COORDENADA coord1 = { coord.linha + 1 , coord.coluna + 1 };
    adiciona_lista_(lista, estado, coord1);
    COORDENADA coord2 = { coord.linha + 1 , coord.coluna };
    adiciona_lista_(lista, estado, coord2);
    COORDENADA coord3 = { coord.linha + 1 , coord.coluna - 1 };
    adiciona_lista_(lista, estado, coord3);
    COORDENADA coord5 = { coord.linha - 1 , coord.coluna - 1 };
    adiciona_lista_(lista, estado, coord5);
    COORDENADA coord6 = { coord.linha - 1, coord.coluna };
    adiciona_lista_(lista, estado, coord6);
    COORDENADA coord7 = { coord.linha - 1 , coord.coluna + 1 };
    adiciona_lista_(lista, estado, coord7);
    COORDENADA coord8 = { coord.linha , coord.coluna + 1 };
    adiciona_lista_(lista, estado, coord8);
    COORDENADA coord4 = { coord.linha , coord.coluna - 1 };
    adiciona_lista_(lista, estado, coord4);
    return lista;
}




////////////////////////////////////
//// Cria lista das jogadas ////////
/////////////////////////////////////

void adiciona_lista(Lista_coord *lista, ESTADO_simples *estado, COORDENADA coord)
{
    if (estado->matriz[ coord.linha ][ coord.coluna ] == BRANCA ) 
    {
        lista->lista[ lista->valor ] = coord;
        lista->valor++;
    }  
}


Lista_coord *cria_lista_coords_possiveis(ESTADO_simples *estado)
{
    Lista_coord *lista = (Lista_coord *) calloc(1, sizeof(Lista_coord));
    COORDENADA coord = estado->last_coord;

    COORDENADA coord1 = { coord.linha + 1 , coord.coluna + 1 };
    adiciona_lista(lista, estado, coord1);
    COORDENADA coord2 = { coord.linha + 1 , coord.coluna };
    adiciona_lista(lista, estado, coord2);
    COORDENADA coord3 = { coord.linha + 1 , coord.coluna - 1 };
    adiciona_lista(lista, estado, coord3);
    COORDENADA coord5 = { coord.linha - 1 , coord.coluna - 1 };
    adiciona_lista(lista, estado, coord5);
    COORDENADA coord6 = { coord.linha - 1, coord.coluna };
    adiciona_lista(lista, estado, coord6);
    COORDENADA coord7 = { coord.linha - 1 , coord.coluna + 1 };
    adiciona_lista(lista, estado, coord7);
    COORDENADA coord8 = { coord.linha , coord.coluna + 1 };
    adiciona_lista(lista, estado, coord8);
    COORDENADA coord4 = { coord.linha , coord.coluna - 1 };
    adiciona_lista(lista, estado, coord4);
    return lista;
}

///////////////////////////////////////
//// ATUALIZA ESATDO_SIMPLES /// //////
///////////////////////////////////////

/**
\brief Função que altera o estado da peça.
*/
void alterar_estado_peca(ESTADO_simples *estado, COORDENADA coordenada, CASA mudar)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    estado->matriz[x][y] = mudar;
}

/**
\brief Função que altera o estado da casa onde estava, para a qual se pretendia mover.
*/
void trocar_posicoes(ESTADO_simples *estado, COORDENADA pos_final)
{
    alterar_estado_peca(estado, estado->last_coord, BRANCA);
    alterar_estado_peca(estado, pos_final, PRETA);
}

void atualiza_estado_simples(ESTADO_simples *estado, COORDENADA coord)
{
    trocar_posicoes(estado, coord);
    estado->last_coord = coord;
    if (estado->player_atual == 1)  estado->player_atual = 2;
    else                             estado->player_atual = 1;
}


///////////////////////////////////////
//// ATRIBUIR VALOR A UMA JOGADA //////
///////////////////////////////////////

int verificar_casa_ocupada(ESTADO_simples *estado, COORDENADA coord)
{
    int x, y, resul = 1;
    x = coord.linha;
    y = coord.coluna; 
    if (x>=0 && x<=7 && y>=0 && y<=7 )
    {
        if (estado->matriz[x][y] == VAZIO ) resul = 0;
    }
    return resul;
}

/**
\brief Função principal que verifica se todas as casas vizinhas se encontram ocupadas.
*/
int verificar_casas_ocupadas_(ESTADO_simples *estado)
{
    COORDENADA coord = estado->last_coord;
    int resul;
    COORDENADA coord1 = { coord.coluna + 1 , coord.linha + 1 };
    COORDENADA coord2 = { coord.coluna + 1 , coord.linha };
    COORDENADA coord3 = { coord.coluna + 1 , coord.linha - 1 };
    COORDENADA coord5 = { coord.coluna - 1 , coord.linha - 1 };
    COORDENADA coord6 = { coord.coluna - 1, coord.linha };
    COORDENADA coord7 = { coord.coluna - 1 , coord.linha + 1 };
    COORDENADA coord8 = { coord.coluna , coord.linha + 1 };
    COORDENADA coord4 = { coord.coluna , coord.linha - 1 };
    resul = ( verificar_casa_ocupada( estado , coord1 ) && verificar_casa_ocupada( estado , coord2 ) &&
              verificar_casa_ocupada( estado , coord3 ) && verificar_casa_ocupada( estado , coord4 ) &&
              verificar_casa_ocupada( estado , coord5 ) && verificar_casa_ocupada( estado , coord6 ) &&
              verificar_casa_ocupada( estado , coord7 ) && verificar_casa_ocupada( estado , coord8 )   );
    return resul;
}

int pontos_casas_ocupadas(ESTADO_simples *estado)
{
    
    COORDENADA coord = estado->last_coord;
    int resul;
    COORDENADA coord1 = { coord.coluna + 1 , coord.linha + 1 };
    COORDENADA coord2 = { coord.coluna + 1 , coord.linha };
    COORDENADA coord3 = { coord.coluna + 1 , coord.linha - 1 };
    COORDENADA coord5 = { coord.coluna - 1 , coord.linha - 1 };
    COORDENADA coord6 = { coord.coluna - 1, coord.linha };
    COORDENADA coord7 = { coord.coluna - 1 , coord.linha + 1 };
    COORDENADA coord8 = { coord.coluna , coord.linha + 1 };
    COORDENADA coord4 = { coord.coluna , coord.linha - 1 };
    resul = ( verificar_casa_ocupada( estado , coord1 ) + verificar_casa_ocupada( estado , coord2 ) +
              verificar_casa_ocupada( estado , coord3 ) + verificar_casa_ocupada( estado , coord4 ) +
              verificar_casa_ocupada( estado , coord5 ) + verificar_casa_ocupada( estado , coord6 ) +
              verificar_casa_ocupada( estado , coord7 ) + verificar_casa_ocupada( estado , coord8 )   );
    return resul;
}

//// quando ninguem ganha //////
// ver se é preciso
int avaliar_estado_jogo(ESTADO_simples *estado)
{
    //falta ver se somos nos a jogar ou nao
    int pontos_vizinhos_ocupados = pontos_casas_ocupadas(estado);
    // ver a distancia a nossa casa;
    int pontos_distancia_casa;  //incompleto
    return pontos_vizinhos_ocupados + pontos_distancia_casa;
}



///////////////QUando alguem ganha /////////////////


/// funcao q verifica se ganhou em casa, atribuindo pontos ///
int ganhou_em_casa(ESTADO_simples *estado,int player)
{
    int resul=0;
    int x = estado->last_coord.linha;
    int y = estado->last_coord.coluna;
    if (estado->player_atual==1 && x == 0 && y == 0) resul = 1;
    else
    {
        if (estado->player_atual==2 && x == 7 && y == 7) resul = 1;
        else 
        {
            if ((x == 0 && y == 0) || (x == 7 && y == 7)) resul = -1;
        }
    }
    return resul; 
}

/// funcao que verifica se ganhou obrigando o outro a jogar para a casa do adversario ///
int encurralado_casa(ESTADO_simples *estado, int player)
{
    int resul = 0;
    int ganhou_casa = ganhou_em_casa(estado,player);
    int valor = verificar_casas_ocupadas_(estado);
    if  (ganhou_em_casa!=0 && valor ) resul = 2 * ganhou_casa;
    return resul;
}

/// funcao que verifica se ganhou encurralando o outro jogador ///
int encurralado_jogo(ESTADO_simples *estado, int player)
{
    int resul = 0;
    int valor = verificar_casas_ocupadas_(estado);
    if (player) resul = 3 * valor;
    else resul = -3 * valor;
    return resul;
}

/// funcao que verifica se ganhou encurralado, atribuindo pontos ///
int ganhou_encurralado(ESTADO_simples *estado,int player)
{
    int resul = 0;
    int valor = encurralado_jogo(estado, player);
    if (valor != 0 ) resul = valor;
    else resul = encurralado_casa(estado,player);
    return resul;
}


/// AVALIAR JOGADA ///
// nos=player true  
int avaliar_jogada(ESTADO_simples *estado,int player)
{
    int resul = ganhou_encurralado(estado, player);
    if (resul == 0) resul = ganhou_em_casa(estado, player);
    return resul;
}



/////////////////////////////////////////////////////
//////  ALGORITMO QUE AVALIA A MELJOR JOGADA ////////
////////////////////////////////////////////////////

int minimax(COORDENADA coord, ESTADO_simples *estado, int alpha, int betha, int player_atual)
{
    int i;
    ///verifica se o jogo acabou //
    int ganhou = avaliar_jogada(estado, player_atual);
    if (ganhou !=0) return ganhou;

    Lista_coord *lista = cria_lista_coords_possiveis(estado);
    int maxValor, valor, minValor;

    // se formos nos a jogar
    if (player_atual)
    {
        for (i = 0; i < lista->valor; i++)
        {
            atualiza_estado_simples(estado, lista->lista[i] );
            valor = minimax(lista->lista[i], estado , alpha, betha, 0 ); //false
            maxValor = max(alpha, valor);
            if (betha <= alpha) break;
            return maxValor;
        }
    }
    else
    {
        for (i = 0; i < lista->valor; i++)
        {
            atualiza_estado_simples(estado, lista->lista[i] );
            valor = minimax(lista->lista[i], estado, alpha, betha, 1 ); ///true
            minValor = min(minValor, valor);
            betha = min(betha, valor);
            if (betha <= alpha) break;
            return minValor;
        }  
    }  
}


LISTA *Iniciar_MinMax(ESTADO *estado)
{

    //ESTADO_simples *estado_simples = troca_estado_estado_simples(estado);
    //Lista_coord *lista_coords = cria_lista_coords_possiveis(estado_simples);

   // LISTA *Moves = criar_lista();
    LISTA *Lista_coords = criar_lista();
    Lista_coords = cria_lista_coords_possiveis_(estado);

    //averiguar o tipo
    JOGADAS *melhor_jogada = NULL;

    LISTA aux;

    for (aux = Lista_coords; !(lista_esta_vazia(aux ) ) ; aux = aux->next )
    {

    }

    int i ;
    int valor;

    /*
    for (i = lista_coords->valor - 1 ; i>=0 ; i--)
    {
        estado_simples = troca_estado_estado_simples(estado);
        atualiza_estado_simples(estado_simples, lista_coords->lista[i]);
        valor = minimax(estado_simples->last_coord, estado_simples, 0,0, 0 );
        insere_cabeca(lista, valor);
    }

    i = verifica_valor_maior(lista);*/
    return  Moves;
}


/*
    criar uma lista que contivesse o valor atribuido a jogada e a lista das coordenadas por onde ele passou
*/
Melhor_jogada *minimax_(COORDENADA coord, ESTADO_simples *estado, int alpha, int betha, int player_atual, Melhor_jogada *melhor_jogada)
{
    int i;
    ///verifica se o jogo acabou //
    int ganhou = avaliar_jogada(estado, player_atual);
    if (ganhou !=0) 
    {   
        melhor_jogada->valor = ganhou;
        return melhor_jogada;
    }

    Lista_coord *lista = cria_lista_coords_possiveis(estado);
    int maxValor=NULL, valor=NULL, minValor=NULL;
    Melhor_jogada *maxValor_, *valor_, *minValor_;

    // se formos nos a jogar
    if (player_atual)
    {
        for (i = 0; i < lista->valor; i++)
        {
            atualiza_estado_simples(estado, lista->lista[i] );
            valor_ = minimax_(lista->lista[i], estado , alpha, betha, 0 ,melhor_jogada); //false
            valor = valor_->valor;
            maxValor = max(alpha, valor);
            if (betha <= alpha) break;
            melhor_jogada->valor = maxValor;
            return melhor_jogada;
        }
    }
    else
    {
        for (i = 0; i < lista->valor; i++)
        {
            atualiza_estado_simples(estado, lista->lista[i] );
            valor_ = minimax_(lista->lista[i], estado, alpha, betha, 1 , melhor_jogada); ///true
            valor = valor_->valor;
            minValor_ = min(minValor, valor);
            minValor = minValor_->valor; 
            betha = min(betha, valor);
            if (betha <= alpha) break;
            melhor_jogada->valor = minValor;
            return melhor_jogada;
        }  
    }  
}

int verifica_valor_maior(LISTA *lista)
{
    void *max = devolve_cabeca(lista);
    int i , resul = 0;

    for (lista,i ; lista_esta_vazia(lista); lista  =  remove_cabeca(lista), i++)
    {
        if (max < devolve_cabeca(lista)) 
        {
            max = devolve_cabeca(lista);
            resul = i;
        }
    }
    return resul;
}

COORDENADA comando_jog(ESTADO *estado)
{
    ESTADO_simples *estado_simples = troca_estado_estado_simples(estado);
    Lista_coord *lista_coords = cria_lista_coords_possiveis(estado_simples);
    int i ;
    int valor;
    LISTA *lista = criar_lista();
    
    for (i = lista_coords->valor - 1 ; i>=0 ; i--)
    {
        estado_simples = troca_estado_estado_simples(estado);
        atualiza_estado_simples(estado_simples, lista_coords->lista[i]);
        valor = minimax(estado_simples->last_coord, estado_simples, 0,0, 0 );
        insere_cabeca(lista, valor);
    }

    i = verifica_valor_maior(lista);
    return  lista_coords->lista[i];
}