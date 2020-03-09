#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "tipos.h"


int main()
{
   // desenha_estado( estado_Inicial());
    ESTADO *estado;
    estado = inicializador_estado();

    interpretador(estado);
    return 0;
}