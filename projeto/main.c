#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Camada_de_Dados.h"
#include "Interface.h"
#include "Logica_do_programa.h"
#include "Melhor_Jogada.h"
#include "listas.h"
#include "dados.h"

int main()
{
    ESTADO *estado;
    estado = inicializador_estado();
    interpretador(estado);
    return 0;
}
