/**
@file listas.h
Definição do módulo com operações sobre listas.
*/

#ifndef ___LISTAS___
#define ___LISTAS___
#define BUF_SIZE 1024

#include "dados.h"

/**
\brief Tipo de dados para listas.
*/
typedef struct lista {
  /** Valor do elemento da lista. */
  void *valor;
  /** Apontador para o próximo elemento da lista. */
  struct lista *next;
} *LISTA, NLista;

/**
\brief Função que liberta o espaco de memoria ocupado pela lista.
*/
void free_lista (LISTA lista) ;

/**
\brief Função que cria uma lista vazia.
*/
LISTA criar_lista();

/**
\brief Função que devolve 1 se a lista dada estiver vazia.
*/
int lista_esta_vazia(LISTA L);

/**
\brief Função que insere um valor na cabeça da lista.
*/
LISTA insere_cabeca(LISTA L, void *valor_dado);

/**
\brief Função que devolve a cabeça de uma lista dada.
*/
void *devolve_cabeca(LISTA L);

/**
\brief Função que devolve a cauda de uma lista dada.
*/
LISTA proximo(LISTA L);

/**
\brief Função que remove a cabeça de uma lista da lista, devolvendo a sua cauda.
*/
LISTA remove_cabeca(LISTA L);

/**
\brief Função auxiliar que insere a coordenada na lista se esta for uma possível coordenada a ser efetuada.
*/
LISTA adiciona_lista(LISTA lista, ESTADO *estado, COORDENADA coord);

/**
\brief Função principal que returna uma LISTA de coordenadas possíveis a serem efetuadas.
*/
LISTA cria_lista_coords_possiveis(ESTADO *estado);

#endif