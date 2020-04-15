#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Camada_de_Dados.h"
#include "Logica_do_programa.h"
#include "Interface.h"
#include "dados.h"
#include "listas.h" // apagar depois

/// LISTAS ///

/**
\brief Função que cria uma lista vazia.
*/
LISTA criar_lista()
{
    LISTA lista = malloc(sizeof( struct lista ));
    return lista;
}

/**
\brief Função que insere um valor na cabeça da lista.
*/
LISTA insere_cabeca(LISTA L, void *valor_dado)
{
    LISTA aux = criar_lista();
    if (!L)
    {
        aux->valor = valor_dado;
        aux->next = NULL;
    }
    else
    {
        aux->valor = valor_dado;
        aux->next = L;
    }
    return aux;
}

/**
\brief Função que devolve a cabeça de uma lista dada.
*/
void *devolve_cabeca(LISTA L)
{
    return &(L->valor);
}

/**
\brief Função que devolve a cauda de uma lista dada.
*/
LISTA proximo(LISTA L)
{
    return (L->next);
}

/**
\brief Função que remove a cabeça de uma lista dad (libertando o espaço ocupado), devolvendo a sua cauda.
*/
LISTA remove_cabeca(LISTA L)
{
    LISTA aux;
    aux = L;
    L = L->next;
    free (aux);
    return L;
}

/**
\brief Função que devolve 1 se a lista dada estiver vazia.
*/
int lista_esta_vazia(LISTA L)
{
    int resul = 0;
    if (L == NULL) resul = 1;
    return resul;
}