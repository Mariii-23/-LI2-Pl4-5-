/**
@file dados.h
Definição dos dados do jogo.
*/

#ifndef ___DADOS_H___
#define  ___DADOS_H___
/**
\brief Definido BUF_SIZE a 1024
*/
#define BUF_SIZE 1024

/**
\brief Definido n_casas_ocupadas com valor 15
*/
#define n_casas_ocupadas 15 //  30

/**
\brief Definido n_vitoria_casa com valor 80
*/
#define n_vitoria_casa 80     // 100

/**
\brief Definido n_vitoria_encurralado com valor 120
*/
#define n_vitoria_encurralado 120  // 200

/**
\brief Definido n_vitoria_casaEencurralado a com valor 150
*/
#define n_vitoria_casaEencurralado 150 //  250

/**
\brief Tipo de dados para os erros
*/
typedef enum {
    /** Sem erro */
    OK, 
    /** COORDENADA_INVALIDA  */
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
