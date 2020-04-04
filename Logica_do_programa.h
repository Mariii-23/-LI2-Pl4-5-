/**
@file Logica_do_programa.h
Definição da função jogar responsável por alterar o estado do jogo.
*/

#ifndef ___LOGICA_DO_PROGRAMA___
#define ___LOGICA_DO_PROGRAMA___
#include "dados.h"
#include "Interface.h"


void mostra_pos(ESTADO *estado, int n_jogadas );
void atualiza_estado(ESTADO *estado, COORDENADA coord_mudar);
int jogar(ESTADO *estado, COORDENADA coord);
void atualiza_estado_pos(ESTADO *estado,int n_pos);

#endif
