/**
@file Interface.h
Definição do intrepretador do jogo.
*/

#ifndef ___INTERFACE___
#define ___INTERFACE___
#include "dados.h"

void jogador_vencedor(ESTADO *estado);
void guarda_tabuleiro(ESTADO *estado, FILE *stream);

int interpretador(ESTADO *estado);

#endif
