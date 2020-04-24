/**
@file Interface.h
Definição do intrepretador do jogo.
*/

#ifndef ___INTERFACE___
#define ___INTERFACE___
#include "dados.h"

void mostra_tabuleiro(CASA tab[8][8],FILE *stream);
void jogador_vencedor(ESTADO *estado, FILE *stream);
void guarda_tabuleiro(ESTADO *estado, FILE *stream);
void prompt(ESTADO *estado, FILE *stream);
int interpretador(ESTADO *estado);

#endif
