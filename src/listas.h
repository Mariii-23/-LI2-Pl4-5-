#ifndef ___LISTAS___
#define ___LISTAS___
#define BUF_SIZE 1024

#include "dados.h"

typedef struct lista {
  void *valor;
  struct lista *next;
} *LISTA, NLista;

typedef struct lista_melhor {
    void *valor;
    void *coord;
    struct lista *next;
} Lista_melhor;

LISTA criar_lista();
LISTA insere_cabeca(LISTA L, void *valor);
void *devolve_cabeca(LISTA L);
LISTA proximo(LISTA L);
LISTA remove_cabeca(LISTA L);
int lista_esta_vazia(LISTA L);

#endif