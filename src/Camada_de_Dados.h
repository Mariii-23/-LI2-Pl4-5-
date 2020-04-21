#ifndef ___CAMADA_DE_DADOS___
#define ___CAMADA_DE_DADOS___
#define BUF_SIZE 1024
#include "dados.h"

void casas_inicial(ESTADO *estado);
ESTADO *inicializador_estado();


CASA estado_casa(ESTADO estado, COORDENADA coordenada);
int verifica_se_e_vizinho(COORDENADA coord_inicial, COORDENADA coord_final);
int verifica_jogada(ESTADO *estado, COORDENADA pos_final);
int verifica_Vitoria(ESTADO *estado);
int verificar_casas_ocupadas(ESTADO *estado);
int verifica_casa_ocupada(ESTADO *estado, COORDENADA coord);
int verifica_coord(COORDENADA coord);
int min(int a, int b);
int max(int a, int b);


#endif
