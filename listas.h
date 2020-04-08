#ifndef ___MELHOR_JOGADA___
#define ___MELHOR_JOGADA___
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

#endif