/**
@file Logica_do_programa.h
Definição da função jogar responsável por alterar o estado do jogo.
*/

#ifndef ___LOGICA_DO_PROGRAMA___
#define ___LOGICA_DO_PROGRAMA___

#include "Camada_de_Dados.h"
#include "Interface.h"
#include "dados.h"

/**
\brief Função que imprime o tabuleiro do jogo na posição pretendida.
*/
void mostra_pos(ESTADO *estado, int n_jogadas );

/**
\brief Função que altera o estado da peça.
*/
void altera_estado_peca(ESTADO *estado, COORDENADA coordenada, CASA mudar);

/**
\brief Função que altera o estado da casa onde estava, para a qual se pretendia mover.
*/
void troca_posicoes(ESTADO *estado, COORDENADA pos_final);

/**
\brief Função que altera o estado das JOGADAS, adicionando a ultima coordenada dada.
*/
void atualiza_JOGADAS(ESTADO *estado,COORDENADA coord_mudar);

/**
\brief Função que atualiza o num_jogadas do estado.
*/
void atualiza_Num_Jogadas(ESTADO *estado);

/**
\brief Função que atualiza o estado a cada jogada.
*/
void atualiza_estado(ESTADO *estado, COORDENADA coord_mudar);

/**
\brief Função que altera o estado do jogo cosoante a jogada efetuada.
*/
int jogar(ESTADO *estado, COORDENADA coord);  

/**
\brief Função que guarda as jogadas do estado.
*/
void guarda_Jogadas_2(ESTADO *estado, COORDENADA coord1, COORDENADA coord2, int  n_jogada);

/**
\brief Função que guarda as jogadas do estado.
*/
void guarda_Jogadas_1(ESTADO *estado, COORDENADA coord1, int  n_jogada);

/**
\brief Função que atualiza o estado lido através do comando ler.
*/
void atualiza_estado_comando_ler(ESTADO *estado);


/**
\brief Função que atualiza o tabuleiro do estado em função do comando pos dado.
*/
void atualiza_tabuleiro_pos(ESTADO *estado, int n_jogadas);

/**
\brief Função que atualiza o estado em função do comando pos dado.
*/
void atualiza_estado_pos(ESTADO *estado,int n_pos);

#endif
