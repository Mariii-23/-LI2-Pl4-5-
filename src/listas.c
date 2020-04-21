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
    LISTA l = malloc(sizeof( struct lista )); //LISTA l = malloc(sizeof( NLista));
    l->valor = NULL;
    l->next = NULL;
    return l;
}

/**
\brief Função que devolve 1 se a lista dada estiver vazia.
*/
int lista_esta_vazia(LISTA L)
{
    int resul = 0;
    if (L == NULL || L->next == NULL) resul = 1;
    return resul;
}

/**
\brief Função que insere um valor na cabeça da lista.
*/
LISTA insere_cabeca(LISTA L, void *valor_dado)
{
    LISTA aux = criar_lista();
    if ( !(L->valor) && !(lista_esta_vazia(L) ) )
    {
        aux->valor = valor_dado;
        aux->next = NULL;
        L = aux;
    }
    else
    {
        aux->valor = valor_dado;
        aux->next = L;
        L = aux;
    }
    return L;
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
\brief Função que liberta o espaco de memoria ocupado pela lista.
*/
void limpa_lista(LISTA L)
{
    while( !lista_esta_vazia(L) ) remove_cabeca(L);
}

/**
\brief Função que dá o número de elementos de uma lista.
*/
int length_lista(LISTA L)
{
   // printf("erro");
    int i=0;
    LISTA aux = L;
    for( aux = L; !lista_esta_vazia(aux) ; aux->valor)  i++;
    return i;
}