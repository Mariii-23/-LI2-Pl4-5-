#ifndef ___DADOS_H___
#define  ___DADOS_H___
#define BUF_SIZE 1024

/**
\brief Tipo de dados para os erros
*/
typedef enum {
  OK, 
  COORDENADA_INVALIDA, 
  JOGADA_INVALIDA, 
  ERRO_LER_TAB,
  ERRO_ABRIR_FICHEIRO,
} ERROS;

/**
\brief Tipo de dados para a casa
*/
typedef enum {
  UM = '1',
  DOIS = '2',
  VAZIO = '.',
  BRANCA = '#',
  PRETA = '*'
} CASA;

/**
\brief Tipo de dados para as coordenadas
*/
typedef struct {
    int coluna;
    int linha;
} COORDENADA;

/**
\brief Tipo de dados para a jogada
*/
typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;

/**
\brief Tipo de dados para as jogadas
*/
typedef JOGADA JOGADAS[32];

/**
\brief Tipo de dados para o estado
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