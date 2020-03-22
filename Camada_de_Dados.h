
#ifndef ___CAMADA_DE_DADOS___
#define ___CAMADA_DE_DADOS___
#define BUF_SIZE 1024


ESTADO *inicializador_estado();
COORDENADA encontra_peca_preta(ESTADO estado);
CASA estado_casa(ESTADO estado, COORDENADA coordenada);
int verifica_jogada(ESTADO *estado,COORDENADA pos_inicial, COORDENADA pos_final);


#endif
