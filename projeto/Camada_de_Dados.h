#ifndef ___CAMADA_DE_DADOS___
#define ___CAMADA_DE_DADOS___
#define BUF_SIZE 1024
#include "dados.h"

void casas_inicial(ESTADO *estado);
ESTADO *inicializador_estado();

ESTADO *cria_estado_copia(ESTADO *estado);

CASA estado_casa(ESTADO estado, COORDENADA coordenada);
int verifica_se_e_vizinho(COORDENADA coord_inicial, COORDENADA coord_final);
int verifica_jogada(ESTADO *estado, COORDENADA pos_final);
int verifica_Vitoria(ESTADO *estado);
int verificar_casas_ocupadas(ESTADO *estado);
int verifica_casa_ocupada(ESTADO *estado, COORDENADA coord);
int verifica_coord(COORDENADA coord);

int min(int a, int b);
int max(int a, int b);
int ganhou_em_casa(ESTADO *estado, int nosso_player);
int encurralado_casa(ESTADO *estado, int nosso_player);
int encurralado_jogo(ESTADO *estado, int player);
int ganhou_encurralado(ESTADO *estado, int nosso_player);
int avaliar_jogada(ESTADO *estado, int nosso_player);


#endif
