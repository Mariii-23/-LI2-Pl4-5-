#ifndef ___LISTAS___
#define ___LISTAS___
#define BUF_SIZE 1024

#include "dados.h"

typedef struct lista {
  void *valor;
  struct lista *next;
} *LISTA, NLista;

LISTA criar_lista();
LISTA insere_cabeca(LISTA L, void *valor);
void *devolve_cabeca(LISTA L);
LISTA proximo(LISTA L);
LISTA remove_cabeca(LISTA L);
int lista_esta_vazia(LISTA L);
void free_lista(LISTA L);
LISTA adiciona_lista(LISTA lista, ESTADO *estado, COORDENADA coord);
LISTA cria_lista_coords_possiveis(ESTADO *estado);
#endif