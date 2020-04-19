#ifndef ___MELHOR_JOGADA___
#define ___MELHOR_JOGADA___
#define BUF_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "Interface.h"
#include "dados.h"
#include "listas.h"

COORDENADA jogada_boot(ESTADO *estado);
ESTADO *cria_estado_copia(ESTADO *estado);
int verifica_coord(COORDENADA coord);
COORDENADA da_coordenada(ESTADO *estado);


#endif