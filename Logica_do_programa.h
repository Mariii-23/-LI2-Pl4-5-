/**
@file Logica_do_programa.h
Definição da função jogar responsável por alterar o estado do jogo.
*/

#ifndef ___LOGICA_DO_PROGRAMA___
#define ___LOGICA_DO_PROGRAMA___
#include "dados.h"

int jogar(ESTADO *estado, COORDENADA coord);
void atualiza_estado(ESTADO *estado, COORDENADA coord_mudar);

#endif
