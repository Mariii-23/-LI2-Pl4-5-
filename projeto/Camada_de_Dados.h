/**
@file Camada_de_dados.h
Definição da camada de dados do jogo.
*/

#ifndef ___CAMADA_DE_DADOS___
#define ___CAMADA_DE_DADOS___

/**
\brief Tipos de dados usados.
*/
#include "dados.h"

/**
\brief Função que define cada casa do jogo quando este é iniciado.
*/
void casas_inicial(ESTADO *estado);

/**
\brief Função que define o estado inicial do jogo.
*/
ESTADO *inicializador_estado();

/**
\brief Função que cria uma cópia do ESTADO.
*/
ESTADO *cria_estado_copia(ESTADO *estado);

/**
\brief Função que devolve o estado de cada peça consoante as coordenadas dadas.
*/
CASA estado_casa(ESTADO estado, COORDENADA coordenada);

/**
\brief Função que verifica se a jogada é possível.
*/
int verifica_se_e_vizinho(COORDENADA coord_inicial, COORDENADA coord_final);

/**
\brief Função principal que verifica se é possível executar a jogada.
*/
int verifica_jogada(ESTADO *estado, COORDENADA pos_final);

/**
\brief Função que verifica se a casa está disponível para se mover para lá.
*/
int verifica_casa_ocupada(ESTADO *estado, COORDENADA coord);

/**
\brief Função principal que verifica se todas as casas vizinhas se encontram ocupadas.
*/
int verificar_casas_ocupadas(ESTADO *estado);

/**
\brief Função que verifica se a peça preta se encontra na casa 1 ou 2.
*/
int verifica_vencedor(ESTADO *estado) ;

/**
\brief Função principal que verifica se existe vencedor.
*/
int verifica_Vitoria(ESTADO *estado);

/**
\brief Função que verifica se uma COORDENADA é válida.
*/
int verifica_coord(COORDENADA coord);

/**
\brief Função que devolve o menor valor de dois.
*/
int min(int a, int b);

/**
\brief Função que devolve o maior valor de dois.
*/
int max(int a, int b);

/**
\brief Função que verifica se ganhou em casa, atribuindo os respetivos pontos.
*/
int ganhou_em_casa(ESTADO *estado, int nosso_player);

/**
\brief Função que verifica se alguém ganhou, obrigando o outro jogador a jogar para a casa do adversário.
*/
int encurralado_casa(ESTADO *estado, int nosso_player);

/**
\brief Função que verifica se alguém ganhou encurralando o outro jogador.
*/
int encurralado_jogo(ESTADO *estado, int player);

/**
\brief Função que verifica se alguém ganhou encurralado, atribuindo pontos.
*/
int ganhou_encurralado(ESTADO *estado, int nosso_player);

/**
\brief Função principal que avalia uma jogada. 
      (NOTA: quando o player == True ou seja 1, significa que player == nosso_player)
*/
int avaliar_jogada(ESTADO *estado, int nosso_player);

/**
\brief Função principal que verifica se todas as casas vizinhas se encontram ocupadas.
*/
int contar_casas_ocupadas(ESTADO *estado);

/**
\brief Função que devolve uma coordenada aleatória possível a ser jogada.
*/
float distancia_coord(COORDENADA coord, int player);

/**
\brief Função que avalia o estado do jogo consoante os pontos.
*/
int avaliar_estado_jogo(ESTADO *estado, int nosso_player );

#endif
