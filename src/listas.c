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
LISTA criar_lista(){
  LISTA l = malloc(sizeof( NLista ));
  l->next = NULL;
//  printf("Funcionou criar_lista\n");
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
int devolve_cabeca(LISTA L)
{
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
\brief Função que remove a cabeça de uma lista da lista (libertando o espaço ocupado), devolvendo a sua cauda.
*/
LISTA remove_cabeca(LISTA L)
{
    LISTA aux = L;
    L = L->next;
    free( aux->valor );
    free(aux);
    return L;
}

/**
\brief Função que liberta o espaco de memória ocupado pela lista.
*/
void free_lista(LISTA L)
{
    while( !lista_esta_vazia(L) ) remove_cabeca(L);
}

/**
\brief Função que dá o número de elementos de uma lista.
*/
int length_lista(LISTA L)
{
    int i=0;
    LISTA aux = L;
    for( aux = L; !lista_esta_vazia(aux) ; aux = aux->next)  i++;
    return i;
}


/// LISTA DE COORDENADAS POSSÍVEIS A SEREM EXECUTADAS ///
/**
\brief Função auxiliar que converte uma coordenada num inteiro.
*/
int from_coordenada(COORDENADA *coord){
  int result = 0;
  result = coord->linha * 10 + coord->coluna;
  printf("Funcionou from_coordenada\n");
  return result;
}

/**
\brief Função auxiliar que insere a coordenada na lista se esta for uma possível coordenada a ser efetuada.
*/
LISTA adiciona_lista(LISTA lista, ESTADO *estado, COORDENADA coord){
    COORDENADA *coord_ = (COORDENADA*)malloc(sizeof (COORDENADA)) ;
    coord_->linha = coord.linha;
    coord_->coluna = coord.coluna;

    if ( verifica_coord(coord)   &&  estado->tab[ coord.linha ][ coord.coluna ] == '.' ){
      lista = insere_cabeca(lista, from_coordenada(coord_));
    printf("Funcionou adiciona_lista\n");
  }
    return lista;
  }


/**
\brief Função principal que returna uma LISTA de coordenadas possíveis a serem efetuadas.
*/
LISTA cria_lista_coords_possiveis(ESTADO *estado){
    LISTA lista = criar_lista(); 
    COORDENADA coord = estado->ultima_jogada; //onde está o '*'.

    COORDENADA coord1 = {coord.linha + 1 , coord.coluna + 1 }; //supeior direito
    lista = adiciona_lista(lista, estado, coord1);
    COORDENADA coord2 = { coord.linha + 1 , coord.coluna }; //superior
    lista = adiciona_lista(lista, estado, coord2);
    COORDENADA coord3 = { coord.linha + 1 , coord.coluna - 1 }; //supeior esquerdo
    lista = adiciona_lista(lista, estado, coord3);
    COORDENADA coord5 = { coord.linha - 1 , coord.coluna - 1 }; //inferior esquerdo
    lista = adiciona_lista(lista, estado, coord5);
    COORDENADA coord6 = { coord.linha - 1, coord.coluna }; //inferior
    lista = adiciona_lista(lista, estado, coord6);
    COORDENADA coord7 = { coord.linha - 1 , coord.coluna + 1 }; //inferior direito
    lista = adiciona_lista(lista, estado, coord7);
    COORDENADA coord8 = { coord.linha , coord.coluna + 1 }; //direito
    lista = adiciona_lista(lista, estado, coord8);
    COORDENADA coord4 = { coord.linha , coord.coluna - 1 }; //esquerdo
    lista = adiciona_lista(lista, estado, coord4);
    return lista;
}

