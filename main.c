#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Interface.h"
#include "Logica_do_programa.h"
#include "dados.h"

int main()
{
   // desenha_estado( estado_Inicial());
    ESTADO *estado;
    estado = inicializador_estado();

    interpretador(estado);
    return 0;
}
