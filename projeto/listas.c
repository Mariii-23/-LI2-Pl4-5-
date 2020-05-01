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
\brief Função que liberta o espaco de memoria ocupado pela lista.
*/
void free_lista (LISTA lista) 
{
    LISTA aux;
    while (lista != NULL)
    {
        aux = lista;
        lista = lista->next;
        free(aux);
    }  
}

/**
\brief Função que cria uma lista vazia.
*/
LISTA criar_lista()
{
    return NULL;
}

/**
\brief Função que devolve 1 se a lista dada estiver vazia.
*/
int lista_esta_vazia(LISTA L)
{
    return L == NULL;
}

/**
\brief Função que insere um valor na cabeça da lista.
*/
LISTA insere_cabeca(LISTA L, void *valor_dado)
{
    //LISTA aux = criar_lista();
    LISTA aux = malloc(sizeof( NLista ));
    aux->valor = valor_dado;
    aux->next = L;
    L = aux;
    return L;
}

/**
\brief Função que devolve a cabeça de uma lista dada.
*/
void *devolve_cabeca(LISTA L)
{
    //return &(*(L->valor));
    return (L->valor);
}

/**
\brief Função que devolve a cauda de uma lista dada.
*/
LISTA proximo(LISTA L)
{
    return (L->next);
}

/**
\brief Função que remove a cabeça de uma lista da lista, devolvendo a sua cauda.
*/
LISTA remove_cabeca(LISTA L)
{
    //LISTA aux = L;
    L = L->next;
    //free(aux);
    return L;
}

/// LISTA DE COORDENADAS POSSÍVEIS A SEREM EXECUTADAS ///

/**
\brief Função auxiliar que insere a coordenada na lista se esta for uma possível coordenada a ser efetuada.
*/
LISTA adiciona_lista(LISTA lista, ESTADO *estado, COORDENADA coord)
{
    COORDENADA *coord_ = (COORDENADA*)malloc(sizeof (COORDENADA)) ;

    coord_->linha = coord.linha;
    coord_->coluna = coord.coluna;

    if ( verifica_coord( coord)   &&  estado->tab[ coord.linha ][ coord.coluna ] != BRANCA )
    {    
        lista = insere_cabeca(lista, coord_); 
    }
    return lista;
}

/**
\brief Função principal que returna uma LISTA de coordenadas possíveis a serem efetuadas.
*/
LISTA cria_lista_coords_possiveis(ESTADO *estado)
{
    LISTA lista = criar_lista(); 

    COORDENADA coord = estado->ultima_jogada;

    COORDENADA coord1 = { coord.coluna + 1 , coord.linha + 1 };
    lista = adiciona_lista(lista, estado, coord1);
    COORDENADA coord2 = { coord.coluna + 1 , coord.linha };
    lista = adiciona_lista(lista, estado, coord2);
    COORDENADA coord3 = { coord.coluna + 1 , coord.linha - 1 };
    lista = adiciona_lista(lista, estado, coord3);
    COORDENADA coord5 = { coord.coluna - 1 , coord.linha - 1 };
    lista = adiciona_lista(lista, estado, coord5);
    COORDENADA coord6 = { coord.coluna - 1, coord.linha };
    lista = adiciona_lista(lista, estado, coord6);
    COORDENADA coord7 = { coord.coluna - 1 , coord.linha + 1 };
    lista = adiciona_lista(lista, estado, coord7);
    COORDENADA coord8 = { coord.coluna , coord.linha + 1 };
    lista = adiciona_lista(lista, estado, coord8);
    COORDENADA coord4 = { coord.coluna , coord.linha - 1 };
    lista = adiciona_lista(lista, estado, coord4);
    return lista;
}
