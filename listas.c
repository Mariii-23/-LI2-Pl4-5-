#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "Interface.h"
#include "dados.h"
#include "listas.h" // apagar depois

// Cria uma lista vazia
LISTA criar_lista()
{
    LISTA lista = (LISTA )malloc(sizeof(LISTA));
    return lista;
}

// Insere um valor na cabeça da lista
LISTA insere_cabeca(LISTA L, void *valor)
{
    LISTA aux = criar_lista();
    if (!L)
    {
        aux->valor = valor;
        aux->next = NULL;
    }
    else
    {
        aux->valor = valor;
        aux->next = L;
    }
    return aux;
}
// Devolve a cabeça da lista
void *devolve_cabeca(LISTA L)
{
    return L->valor;
}
// Devolve a cauda da lista
LISTA proximo(LISTA L)
{
    return L->next;
}
// Remove a cabeça da lista (libertando o espaço ocupado) e devolve a cauda
LISTA remove_cabeca(LISTA L)
{
    LISTA aux;
    aux = L;
    L = L->next;
    free (aux);
    return L;
}
// Devolve verdareiro se a lista é vazia
int lista_esta_vazia(LISTA L)
{
    int resul = 0;
    if (L == NULL) resul = 1;
    return resul;
}