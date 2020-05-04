/**
@file Interface.h
Definição do intrepretador do jogo.
*/

#ifndef ___INTERFACE___
#define ___INTERFACE___

/**
\brief Tipos de dados usados.
*/
#include "dados.h"

/**
\brief Função que determina o vencedor do jogo.
*/
void jogador_vencedor(ESTADO *estado, FILE *stream);

/**
\brief Função que que "imprime" no ecrã ou num ficheiro as peças de um determinado tabuleiro.
*/
void mostra_tabuleiro(CASA tab[8][8],FILE *stream);

/**
\brief Prompt do jogo.
*/
void prompt(ESTADO *estado, FILE *stream);

/**
\brief Guarda no ficheiro cada linha do jogo, recorrendo à função guarda_casa.
*/
void guarda_Linha(ESTADO *estado, int linha, FILE *stream);

/**
\brief Guarda no ficheiro o tabuleiro do jogo, recorrendo à função guarda_linha.
*/
void guarda_tabuleiro(ESTADO *estado, FILE *stream);

/**
\brief Executa o comando pos para retroceder o jogo.
*/
void comando_pos(ESTADO *estado, int n_jogadas );

/**
\brief Executa o comando movs para gravar os movimentos.
*/
void comando_movs(ESTADO *estado, FILE *stream);

/**
\brief Função principal que imprime os movimentos dos jogadores.
*/
void movs(ESTADO *estado);

/**
\brief Executa o comendo gr para guardar o tabuleiro do jogo no ficheiro.
*/
void comando_gr(ESTADO *estado, FILE *stream);

/**
\brief Função principal que guarda o tabuleiro de jogo e os movimentos dos jogadores.
*/
void gr(ESTADO *estado, char *filename);

/**
\brief Função que atualiza o tabuleiro de um estado atravé de um ficheiro.
*/
void ler_linha(ESTADO *estado, char linha[], int l);

/**
\brief Executa o comando ler, lendo o que está no ficheiro que recebe.
*/
void comando_ler(FILE *fp,ESTADO *estado);

/**
\brief Executa o comando ler, lendo o que está no ficheiro que recebe.
*/
void ler(ESTADO *estado, char *filename);

/**
\brief Intrepretador do jogo.
*/
int interpretador(ESTADO *estado);

#endif
