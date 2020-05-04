/**
@file dados.h
Definição dos dados do jogo.
*/

#ifndef ___DADOS_H___
#define  ___DADOS_H___
#define BUF_SIZE 1024

/**
\brief Tipo de dados para os erros
*/
typedef enum {
    /** Sem erro */
    OK, 
    /** COORDENADA_INVALID  */
    COORDENADA_INVALIDA, 
    /** JOGADA INVALIDA */
    JOGADA_INVALIDA, 
    /** ERRO AO LER O TABULEIRO  */
    ERRO_LER_TAB,
    /** ERRO AO ABRIR FICHEIRO */
    ERRO_ABRIR_FICHEIRO,
} ERROS;

/**
\brief Tipo de dados para a casa.
*/
typedef enum {
  /** Casa jogador UM. */
  UM = '1',
  /** Casa jogador DOIS. */
  DOIS = '2',
  /** Casa disponível para jogar. */
  VAZIO = '.',
  /** Casa indisponível para jogar. */
  BRANCA = '#',
  /** Casa onde se encontra a peça PRETA. */
  PRETA = '*'
} CASA;

/**
\brief Tipo de dados para as coordenadas.
*/
typedef struct {
    /** Coluna do tabuleiro. */
    int coluna;
    /** Linha do tabuleiro. */
    int linha;
} COORDENADA;

/**
\brief Tipo de dados para a jogada
*/
typedef struct {
    /** Coordenadas do jogador 1. */
    COORDENADA jogador1;
    /** Coordenadas do jogador 2. */
    COORDENADA jogador2;
} JOGADA;

/**
\brief Tipo de dados para as jogadas.
*/
typedef JOGADA JOGADAS[32];

/**
\brief Tipo de dados para o estado.
*/
typedef struct {
  /** O tabuleiro */
  CASA tab[8][8];
  /** As jogadas */
  JOGADAS jogadas;
  /** O número das jogadas, usado no prompt */
  int num_jogadas;
  /** O jogador atual */
  int jogador_atual;
  /** O nº de comando, usado no prompt */
  int num_comando;
  /** A coordenada da última jogada */
  COORDENADA ultima_jogada;
} ESTADO;

#endif