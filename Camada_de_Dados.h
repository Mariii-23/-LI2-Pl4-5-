#ifndef ___CAMADA_DE_DADOS___
#define ___CAMADA_DE_DADOS___
#define BUF_SIZE 1024
#include "dados.h"

ESTADO *inicializador_estado();

COORDENADA encontra_peca_preta(ESTADO estado);
CASA estado_casa(ESTADO estado, COORDENADA coordenada);
int verifica_se_e_vizinho(COORDENADA coord_inicial, COORDENADA coord_final);
int verifica_jogada(ESTADO *estado,COORDENADA pos_inicial, COORDENADA pos_final);
int verifica_Vitoria(ESTADO *estado, COORDENADA coord);


#endif
