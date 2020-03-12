
#ifndef ___CAMADA_DE_DADOS___
#define ___CAMADA_DE_DADOS___
#define BUF_SIZE 1024

typedef enum {VAZIO, BRANCA, PRETA} CASA;

typedef struct {
    int coluna;
    int linha;
} COORDENADA;

typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;

typedef JOGADA JOGADAS[32];

typedef struct {
    CASA tab[8][8];
    JOGADAS jogadas;
    int num_jogadas;
    int jogador_atual;
} ESTADO;

ESTADO *inicializador_estado();
COORDENADA encontra_peca_preta(ESTADO estado);
CASA estado_casa(ESTADO estado, COORDENADA coordenada);
int verifica_jogada(ESTADO *estado,COORDENADA pos_inicial, COORDENADA pos_final);


#endif
