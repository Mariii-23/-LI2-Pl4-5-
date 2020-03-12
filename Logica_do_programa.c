#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"

//FUNCAO QUE ALTERA O ESTADO DA PECA
void altera_estado_peca(ESTADO *estado, COORDENADA coordenada, CASA mudar)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    estado->tab[x][y] = mudar;
}

//FUNCAO QUE ALTERA O ESTADO DAS CASAS DA POSICAO DE ONDE ESTAVA PARA O QUAL SE PRETENDIA MOVER
void troca_posicoes(ESTADO *estado, COORDENADA pos_inicial, COORDENADA pos_final)
{
    altera_estado_peca(estado, pos_inicial , BRANCA);
    altera_estado_peca(estado, pos_final, PRETA);
}

int jogar(ESTADO *estado, COORDENADA coord)
{
    int resul=0;
    COORDENADA coord_anterior;
    coord_anterior = encontra_peca_preta(*estado);

    int verificar;
    verificar = verifica_jogada(estado, coord_anterior, coord);
    resul = verificar;

    if (verificar)
    {
        troca_posicoes(estado, coord_anterior, coord);
    }
    else
    {
        printf("\nJogada inválida.\n");
    }
    return resul;
}