#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "tipos.h"


int main()
{
    int i, j;
    CASA tabi[8][8];
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if (i==3 && j==4)
            {
                tabi[i][j] = PRETA;
            }
            else
            {
                tabi[i][j] = VAZIO;
            }       
        }
    } 
    
    for (i=0; i<8; i++)
    {
        desenha_Linha(tabi, i);
    }

    putchar('\n');
    desenha_estado( estado_Inicial());
    return 0;
}