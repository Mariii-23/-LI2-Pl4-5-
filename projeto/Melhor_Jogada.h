/**
@file Melhor_jogada.h
Definição do módulo com funções para determinar a melhor jogada a ser executada.
*/

#ifndef ___MELHOR_JOGADA___
#define ___MELHOR_JOGADA___

/**
\brief Tipos de dados usados.
*/
#include "dados.h"
/**
\brief Tipos de dados usados sobre listas.
*/
#include "listas.h"

/**
\brief Função que atualiza o jogador.
*/
int muda_jogador(int player);

/**
\brief Função que executa o MinMax, retornando o valor de uma determinada jogada.
*/
int MinMax(ESTADO *estado,COORDENADA *coord, int alpha, int betha, int nosso_jogador, int n_avaliar);

/**
\brief Função que inicia o MinMax, retornando a melhor COORDENADA a ser efetuada.
*/
COORDENADA *Iniciar_MinMax(ESTADO *estado);

/**
\brief Função que devolve a melhor coordenada a ser efetuada pelo boot ou uma coordenada inválida se a jogada for inválida.
*/
COORDENADA jogada_boot(ESTADO *estado);

/**
\brief Função que devolve uma coordenada aleatória possível a ser jogada.
*/
COORDENADA da_coordenada(ESTADO *estado);

/**
\brief Função que devolve a coordenada, possível a ser jogada que se encontre a menor distância da casa do jogador.
*/
COORDENADA da_coordenada_distancia(ESTADO *estado);

/**
\brief Função que devolve a coordenada, possível a ser jogada que se encontre a menor distância da casa do jogador.
*/
COORDENADA obtem_coord_atraves_da_distancia(ESTADO *estado);

#endif