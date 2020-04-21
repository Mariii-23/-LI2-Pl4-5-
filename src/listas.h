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

/*
typedef COORDENADAS COORDENADA[8] 

typedef struct lista_coords {
    int valor;  // vvai represenatr quantas coordenadas
    COORDENADAS coord;
} lista_coords;*/


LISTA criar_lista();
LISTA insere_cabeca(LISTA L, void *valor);
void *devolve_cabeca(LISTA L);
LISTA proximo(LISTA L);
LISTA remove_cabeca(LISTA L);
int lista_esta_vazia(LISTA L);
int length_lista(LISTA L);
void limpa_lista(LISTA L);

#endif