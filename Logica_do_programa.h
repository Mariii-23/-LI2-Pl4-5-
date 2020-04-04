/**
@file Logica_do_programa.h
Definição da função jogar responsável por alterar o estado do jogo.
*/

#ifndef ___LOGICA_DO_PROGRAMA___
#define ___LOGICA_DO_PROGRAMA___
#include "dados.h"
#include "Interface.h"

void guarda_Jogadas_2(ESTADO *estado, COORDENADA coord1, COORDENADA coord2, int  n_jogada);
void guarda_Jogadas_1(ESTADO *estado, COORDENADA coord1, int  n_jogada);
void atualiza_estado_comando_ler(ESTADO *estado);
void mostra_pos(ESTADO *estado, int n_jogadas );
void atualiza_estado(ESTADO *estado, COORDENADA coord_mudar);
int jogar(ESTADO *estado, COORDENADA coord);
void atualiza_estado_pos(ESTADO *estado,int n_pos);

#endif
