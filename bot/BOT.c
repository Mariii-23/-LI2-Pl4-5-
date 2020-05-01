#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BUF_SIZE 1024
#define n_casas_ocupadas 15 //  30
#define n_vitoria_casa 80     // 100
#define n_vitoria_encurralado 120  // 200
#define n_vitoria_casaEencurralado 150 //    250

/// DADOS ///
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

typedef struct lista {
  void *valor;
  struct lista *next;
} *LISTA, NLista;



/// LISTAS ///
/**
\brief Função que liberta o espaco de memoria ocupado pela lista.
*/
void free_lista (LISTA lista) 
{
    LISTA aux;
    while (lista != NULL)
    {
        aux = lista;
        lista = lista->next;
        free(aux);
    }  
}

/**
\brief Função que cria uma lista vazia.
*/
LISTA criar_lista()
{
    return NULL;
}

/**
\brief Função que devolve 1 se a lista dada estiver vazia.
*/
int lista_esta_vazia(LISTA L)
{
    return L == NULL;
}

/**
\brief Função que insere um valor na cabeça da lista.
*/
LISTA insere_cabeca(LISTA L, void *valor_dado)
{
    LISTA aux = malloc(sizeof( NLista ));
    aux->valor = valor_dado;
    aux->next = L;
    L = aux;
    return L;
}

/**
\brief Função que devolve a cabeça de uma lista dada.
*/
void *devolve_cabeca(LISTA L)
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
    L = L->next;
    //free(aux);
    return L;
}


/// LISTA DE COORDENADAS POSSÍVEIS A SEREM EXECUTADAS ///
/**
\brief Função que verifica se uma COORDENADA é válida.
*/
int verifica_coord(COORDENADA coord)
{
    int x = coord.linha,
        y = coord.coluna;
    return ( x>=0 && x<=7 &&  y>=0 && y<=7 );
}

/**
\brief Função auxiliar que insere a coordenada na lista se esta for uma possível coordenada a ser efetuada.
*/
LISTA adiciona_lista(LISTA lista, ESTADO *estado, COORDENADA coord)
{
    COORDENADA *coord_ = (COORDENADA*)malloc(sizeof (COORDENADA)) ;

    coord_->linha = coord.linha;
    coord_->coluna = coord.coluna;

    if ( verifica_coord( coord)   &&  estado->tab[ coord.linha ][ coord.coluna ] != BRANCA )
    {    
        lista = insere_cabeca(lista, coord_); 
    }
    return lista;
}

/**
\brief Função principal que returna uma LISTA de coordenadas possíveis a serem efetuadas.
*/
LISTA cria_lista_coords_possiveis(ESTADO *estado)
{
    LISTA lista = criar_lista(); 

    COORDENADA coord = estado->ultima_jogada;

    COORDENADA coord1 = { coord.coluna + 1 , coord.linha + 1 };
    lista = adiciona_lista(lista, estado, coord1);
    COORDENADA coord2 = { coord.coluna + 1 , coord.linha };
    lista = adiciona_lista(lista, estado, coord2);
    COORDENADA coord3 = { coord.coluna + 1 , coord.linha - 1 };
    lista = adiciona_lista(lista, estado, coord3);
    COORDENADA coord5 = { coord.coluna - 1 , coord.linha - 1 };
    lista = adiciona_lista(lista, estado, coord5);
    COORDENADA coord6 = { coord.coluna - 1, coord.linha };
    lista = adiciona_lista(lista, estado, coord6);
    COORDENADA coord7 = { coord.coluna - 1 , coord.linha + 1 };
    lista = adiciona_lista(lista, estado, coord7);
    COORDENADA coord8 = { coord.coluna , coord.linha + 1 };
    lista = adiciona_lista(lista, estado, coord8);
    COORDENADA coord4 = { coord.coluna , coord.linha - 1 };
    lista = adiciona_lista(lista, estado, coord4);
    return lista;
}


/// CAMADA DE DADOS ///
/// ESTADO INICIAL ///
/**
\brief Função que define cada casa do jogo quando este é iniciado.
*/
void casas_inicial(ESTADO *estado)
{
    int i, j;
    for(i=7; i>=0; i--)
    {
        for(j=0; j<=7; j++)
        {
            if (i==4 && j==4)       estado->tab[i][j] = '*';
            else 
            {
                if (i==7 && j==7)    estado->tab[i][j] = '2';
                else
                {
                    if(i==0 && j==0)  estado->tab[i][j] = '1';
                    else    estado->tab[i][j] = '.';
                }   
            }         
        }
    }  
}

/**
\brief Função que define o estado inicial do jogo.
*/
ESTADO *inicializador_estado()
{
    ESTADO *estado = (ESTADO *) calloc(1, sizeof(ESTADO));
    casas_inicial(estado);
    estado->num_jogadas = 1;
    estado->jogador_atual = 1;
    estado->num_comando = 1;
    estado->ultima_jogada.coluna = 4;  
    estado->ultima_jogada.linha = 4;  
    return estado;
}

/// ESTADO COPIA ///
/**
\brief Função que cria uma cópia do ESTADO.
*/
ESTADO *cria_estado_copia(ESTADO *estado)
{
    ESTADO *estado_copia = (ESTADO *) calloc(1, sizeof(ESTADO));
    int i,j;
    for(i=0 ; i<8; i++)
    {
        for(j=0; j<8; j++) estado_copia->tab[i][j] = estado->tab[i][j];
    }
    estado_copia->num_jogadas = estado->num_jogadas;
    estado_copia->jogador_atual = estado->jogador_atual;
    estado_copia->num_comando = estado->num_comando;
    estado_copia->ultima_jogada.coluna = estado->ultima_jogada.coluna;  
    estado_copia->ultima_jogada.linha = estado->ultima_jogada.linha;
    
    for(i=0; i<estado->num_jogadas; i++)
    {
        estado_copia->jogadas[i].jogador1 = estado->jogadas[i].jogador1;
        estado_copia->jogadas[i].jogador2 = estado->jogadas[i].jogador2;
    }
    if (estado->jogador_atual==2)  estado_copia->jogadas[i].jogador1 = estado->jogadas[i].jogador1;

    return estado_copia;
}

/// FUNCOES AUXILIARES ///
/**
\brief Função que devolve o estado de cada peça consoante as coordenadas dadas.
*/
CASA estado_casa(ESTADO estado, COORDENADA coordenada)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    CASA peca = estado.tab[x][y];
    return peca;
}

/**
\brief Função que verifica se a jogada é possível.
*/
int verifica_se_e_vizinho(COORDENADA coord_inicial, COORDENADA coord_final)
{
    int x, y, x_, y_, resul=0;
    x = coord_inicial.linha;
    y = coord_inicial.coluna; 
    x_ = coord_final.linha; 
    y_ = coord_final.coluna; 

    if  (   (x == x_ && abs (y_ - y) == 1 ) || 
            (y == y_ && abs (x_ - x) == 1 ) ||
            ( abs(x_- x) == 1 && abs(y_ - y) == 1 ) 
        )   resul=1;
    return resul;
}

/**
\brief Função principal que verifica se é possível executar a jogada.
*/
int verifica_jogada(ESTADO *estado, COORDENADA pos_final)
{
    int x = pos_final.linha;
    int y = pos_final.coluna;
    CASA peca = estado->tab[x][y];
    int vaziaa = peca != '#';  /* Exatamente igual: peca == '.' || peca == '2' || peca == '1'  */
    return ( vaziaa  && verifica_se_e_vizinho(estado->ultima_jogada, pos_final )  );
}

/// VERIFICA SE ALGUEM GANHOU ///

/**
\brief Função que verifica se a casa está disponível para se mover para lá.
*/
int verifica_casa_ocupada(ESTADO *estado, COORDENADA coord)
{
    int x, y, resul = 1;
    x = coord.linha;
    y = coord.coluna; 

    if (x>=0 && x<=7 && y>=0 && y<=7 )    if (estado->tab[x][y] == VAZIO ) resul = 0;
    return resul;
}

/**
\brief Função principal que verifica se todas as casas vizinhas se encontram ocupadas.
*/
int verificar_casas_ocupadas(ESTADO *estado)
{
    COORDENADA coord = estado->ultima_jogada;
    int resul;
    COORDENADA coord1 = { coord.coluna + 1 , coord.linha + 1 },
               coord2 = { coord.coluna + 1 , coord.linha },
               coord3 = { coord.coluna + 1 , coord.linha - 1 },
               coord5 = { coord.coluna - 1 , coord.linha - 1 },
               coord6 = { coord.coluna - 1, coord.linha },
               coord7 = { coord.coluna - 1 , coord.linha + 1 },
               coord8 = { coord.coluna , coord.linha + 1 },
               coord4 = { coord.coluna , coord.linha - 1 };
    resul = ( verifica_casa_ocupada( estado , coord1 ) && verifica_casa_ocupada( estado , coord2 ) &&
              verifica_casa_ocupada( estado , coord3 ) && verifica_casa_ocupada( estado , coord4 ) &&
              verifica_casa_ocupada( estado , coord5 ) && verifica_casa_ocupada( estado , coord6 ) &&
              verifica_casa_ocupada( estado , coord7 ) && verifica_casa_ocupada( estado , coord8 )   );
    return resul;
}

/**
\brief Função que verifica se a peça preta se encontra na casa 1 ou 2.
*/
int verifica_vencedor(ESTADO *estado) 
{
    COORDENADA coord = estado->ultima_jogada;
    int r = ( coord.linha == 0  && coord.coluna == 0) ||
            ( coord.linha == 7  && coord.coluna == 7) ;
    return r;
}

/**
\brief Função principal que verifica se existe vencedor.
*/
int verifica_Vitoria(ESTADO *estado)
{
     return ( verifica_vencedor(estado) || verificar_casas_ocupadas(estado) );
}


/// FUNCOES AUXILIARES DO MINMAX ///

/**
\brief Função que devolve o menor valor de dois.
*/
int min(int a, int b)
{
    int resul = a;
    if (a>b) resul = b;
    return resul;
}

/**
\brief Função que devolve o maior valor de dois.
*/
int max(int a, int b)
{
    int resul = a;
    if (a<b) resul = b;
    return resul;
}

/// AVALIAR UMA JOGADA ///
/**
\brief Função que verifica se ganhou em casa, atribuindo os respetivos pontos.
*/
int ganhou_em_casa(ESTADO *estado, int nosso_player)
{
    int resul=0;
    int x = estado->ultima_jogada.linha;
    int y = estado->ultima_jogada.coluna;

    if (estado->jogador_atual==1 && nosso_player==1 && x == 0 && y == 0) resul = 1;
    else
    {
        if (estado->jogador_atual==2 && nosso_player==2 && x == 7 && y == 7) resul = 1;
        else     if ((x == 0 && y == 0) || (x == 7 && y == 7)) resul = -1;
    }
    return resul; 
}

/**
\brief Função que verifica se alguém ganhou, obrigando o outro jogador a jogar para a casa do adversario.
*/
int encurralado_casa(ESTADO *estado, int nosso_player)
{
    int resul = 0;
    int ganhou_casa = ganhou_em_casa(estado, nosso_player);
    int valor = verificar_casas_ocupadas(estado);
    if  (ganhou_casa && valor ) resul = n_vitoria_casaEencurralado * ganhou_casa;
    /*if  (&ganhou_em_casa && valor ) resul = 2 * ganhou_casa;*/
    return resul;
}

/**
\brief Função que verifica se alguém ganhou encurralando o outro jogador.
*/
int encurralado_jogo(ESTADO *estado, int player)
{
    int resul = 0;
    int valor = verificar_casas_ocupadas(estado);
    if (!player) resul = n_vitoria_encurralado * valor;
    else resul = - n_vitoria_encurralado * valor;
    return resul;
}

/**
\brief Função que verifica se alguém ganhou encurralado, atribuindo pontos.
*/
int ganhou_encurralado(ESTADO *estado, int nosso_player)
{
    int resul = 0;
    int valor = encurralado_jogo(estado,nosso_player);
    if (valor != 0 ) resul = valor;
    else resul = encurralado_casa(estado, nosso_player);
    return resul;
}


/// AVALIAR JOGADA PRINCIPAL ///
/**
\brief Função PRINCIPAL que avalia uma jogada. 
      (NOTA: quando o player == True ou seja 1, significa que player == nosso_player)
*/
int avaliar_jogada(ESTADO *estado, int nosso_player)
{
    int resul = ganhou_encurralado(estado, nosso_player);
    if (resul == 0) resul = ganhou_em_casa(estado, nosso_player);
    return resul;
}

/**
\brief Função principal que verifica se todas as casas vizinhas se encontram ocupadas.
*/
int contar_casas_ocupadas(ESTADO *estado)
{
    COORDENADA coord = estado->ultima_jogada;
    int resul;
    COORDENADA coord1 = { coord.coluna + 1 , coord.linha + 1 },
               coord2 = { coord.coluna + 1 , coord.linha },
               coord3 = { coord.coluna + 1 , coord.linha - 1 },
               coord5 = { coord.coluna - 1 , coord.linha - 1 },
               coord6 = { coord.coluna - 1, coord.linha },
               coord7 = { coord.coluna - 1 , coord.linha + 1 },
               coord8 = { coord.coluna , coord.linha + 1 },
               coord4 = { coord.coluna , coord.linha - 1 };
    resul = ( verifica_casa_ocupada( estado , coord1 ) + verifica_casa_ocupada( estado , coord2 ) +
              verifica_casa_ocupada( estado , coord3 ) + verifica_casa_ocupada( estado , coord4 ) +
              verifica_casa_ocupada( estado , coord5 ) + verifica_casa_ocupada( estado , coord6 ) +
              verifica_casa_ocupada( estado , coord7 ) + verifica_casa_ocupada( estado , coord8 )   );
    return resul;
}

/**
\brief Função que devolve uma coordenada aleatória possível a ser jogada.
*/
float distancia_coord(COORDENADA coord, int player)
{
    COORDENADA coord_casa;
    if (player==1) 
    {
        coord_casa.coluna = 0;
        coord_casa.linha = 0;
    }
    else
    {
        coord_casa.coluna = 7;
        coord_casa.linha = 7;
    }
    int x = abs( coord_casa.coluna - coord.coluna ),
        y = abs( coord_casa.linha - coord.linha );
    float resul = ( x*x + y*y );
    /*float resul = x+y;*/
    return ( resul );
}

///avalia estado jogo ///
int avaliar_estado_jogo(ESTADO *estado , int nosso_player)
{
    int result = 0;
    result = n_casas_ocupadas * contar_casas_ocupadas(estado) - ///acho q é -// n ta bem // ver valores
             distancia_coord(estado->ultima_jogada, nosso_player);

    if (nosso_player != estado->jogador_atual) result = -result;
    return result;
}

/// LOGICA DO PROGRAMA ///


/// ATUALIZA O ESTADO ///

/**
\brief Função que altera o estado da peça.
*/
void altera_estado_peca(ESTADO *estado, COORDENADA coordenada, CASA mudar)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    estado->tab[x][y] = mudar;
}

/**
\brief Função que altera o estado da casa onde estava, para a qual se pretendia mover.
*/
void troca_posicoes(ESTADO *estado, COORDENADA pos_final)
{
    altera_estado_peca(estado, estado->ultima_jogada, BRANCA);
    altera_estado_peca(estado, pos_final, PRETA);
}
/**
\brief Função que altera o estado das JOGADAS, adicionando a ultima coordenada dada.
*/
void atualiza_JOGADAS(ESTADO *estado,COORDENADA coord_mudar)
{
    if (estado->jogador_atual == 2)   estado->jogadas[ estado->num_jogadas - 1].jogador2 = coord_mudar; 
    else                              estado->jogadas[ estado->num_jogadas - 1].jogador1 = coord_mudar;
}

/**
\brief Função que atualiza o num_jogadas do estado.
*/
void atualiza_Num_Jogadas(ESTADO *estado)
{
    int jog = estado->jogador_atual;
    if (jog == 1)  estado->num_jogadas += 1;
}

/**
\brief Função que atualiza o estado a cada jogada.
*/
void atualiza_estado(ESTADO *estado, COORDENADA coord_mudar) 
{
    troca_posicoes(estado, coord_mudar);
    atualiza_JOGADAS(estado,coord_mudar);
    if (estado->jogador_atual == 1)  estado->jogador_atual = 2;
    else                             estado->jogador_atual = 1;
    atualiza_Num_Jogadas(estado);
    estado->num_comando +=1 ;
    estado->ultima_jogada = coord_mudar;
}

/**
\brief Função que altera o estado do jogo cosoante a jogada efetuada.
*/
int jogar(ESTADO *estado, COORDENADA coord)
{
    int resul=0;
    int pode_jogar = verifica_jogada(estado, coord);
    
    if (pode_jogar)    atualiza_estado(estado, coord);
    else
    {
        printf("\nJogada inválida.\n");
        estado->num_comando++;
    }
    resul = 1;

    return resul;
}

/// COMANDO LER ///
/// ATUALIZA EM FUNCAO DO COMANDO LER ///

/**
\brief Função que guarda as jogadas do estado.
*/
void guarda_Jogadas_2(ESTADO *estado, COORDENADA coord1, COORDENADA coord2, int  n_jogada)
{
    estado->jogadas[ n_jogada ].jogador1 = coord1;
    estado->jogadas[ n_jogada ].jogador2 = coord2;
}

/**
\brief Função que guarda as jogadas do estado.
*/
void guarda_Jogadas_1(ESTADO *estado, COORDENADA coord1, int  n_jogada)
{
    estado->jogadas[ n_jogada ].jogador1 = coord1;
}

/**
\brief Função que atualiza o estado lido através do comando ler.
*/
void atualiza_estado_comando_ler(ESTADO *estado)
{
    if ( estado->num_comando % 2 )  
    {
        estado->jogador_atual = 2;
        estado->ultima_jogada = estado->jogadas[ estado->num_jogadas - 1 ].jogador1;
    }
    else                           
    {
        estado->jogador_atual = 1; 
        estado->ultima_jogada = estado->jogadas[ estado->num_jogadas - 2 ].jogador2;
    }
}


/// INTERFACE ///


/// TABULEIRO : IMPRIME OU GUARDA ///

/**
\brief Função que que imprime apenas as pecas de um determinado tabuleiro .
*/
void mostra_tabuleiro(CASA tab[8][8],FILE *stream)
{
    int linha, coluna;
    CASA casa;
    fprintf(stream, "  abcdefgh\n");
    for (linha = 7; linha >= 0; linha--)
    {
        fprintf(stream, "%d ", linha+1);
        for (coluna = 0; coluna < 8; coluna++)
        {
            casa = tab[linha][coluna];
            fputc(casa, stream);
        }
        fprintf(stream, "\n");
    }
    fprintf(stream, "\n");
}


/**
\brief Prompt do jogo.
*/
void prompt(ESTADO *estado, FILE *stream) {  
    fprintf(stream, "# %d Player_%d Jogada_%d -> ", estado->num_comando, estado->jogador_atual, estado->num_jogadas);
}

/**
\brief Guarda no ficheiro cada linha do jogo, recorrendo à função guarda_casa.
*/
void guarda_Linha(ESTADO *estado, int linha, FILE *stream)
{
    int coluna;
    CASA casa;
    for(coluna=0; coluna<=7; coluna++)
    {
        casa = estado->tab[linha][coluna];
        fputc(casa, stream);
    }
    fprintf(stream, "\n"); 
}

/**
\brief Guarda no ficheiro o tabuleiro do jogo, recorrendo à função guarda_linha.
*/
void guarda_tabuleiro(ESTADO *estado, FILE *stream)
{
    int linha;
    if (stream == stdout) fprintf(stream,"\n  abcdefgh\n");
    
    for (linha=7; linha>=0; linha--)
    {
        if (stream == stdout) fprintf(stream, "%d ",linha+1);
        guarda_Linha( estado, linha, stream);
    }
    fprintf(stream, "\n");
}

/// !!!____COMANDOS___!!! ////
/// Comando movs ///
/**
\brief Executa o comando movs para gravar os movimentos.
*/
void comando_movs(ESTADO *estado, FILE *stream)
{
    int cont=0, num;
    int n_jogadas = estado->num_jogadas;
    int j = estado->jogador_atual;
    COORDENADA coord1 = estado->jogadas[cont].jogador1;
    COORDENADA coord2 = estado->jogadas[cont].jogador2;

    for (num = 1 ; num < n_jogadas ; num++ , cont++)
    {
        coord1 = estado->jogadas[cont].jogador1;
        coord2 = estado->jogadas[cont].jogador2;
        if (num <10)  fprintf(stream, "0%d: %c%d %c%d\n", num, coord1.coluna + 'a', coord1.linha + 1, coord2.coluna + 'a', coord2.linha + 1 );
        else          fprintf(stream, "%d: %c%d %c%d\n", num, coord1.coluna + 'a', coord1.linha + 1, coord2.coluna  + 'a', coord2.linha + 1 );
    }
    coord1 = estado->jogadas[cont].jogador1;
    coord2 = estado->jogadas[cont].jogador2;
    if (j == 2 )
    {
        if (num <10)  fprintf(stream, "0%d: %c%d\n", num, coord1.coluna + 'a', coord1.linha + 1);
        else          fprintf(stream, "%d: %c%d\n", num, coord1.coluna + 'a', coord1.linha + 1); 
    }
}

void movs(ESTADO *estado)
{
    comando_movs(estado,stdout);
    estado->num_comando++;
    guarda_tabuleiro(estado,stdout);
    prompt(estado, stdout);
}

/// COMANDO GRAVAR ///
/**
\brief Executa o comendo gr para guardar o tabuleiro do jogo no ficheiro.
*/
void comando_gr(ESTADO *estado, FILE *stream) {
    guarda_tabuleiro(estado, stream);
    comando_movs(estado, stream);
}

void gr(ESTADO *estado, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "w");

    if (fp == NULL) printf("O ficheiro não abriu.\n");
/* Grava o tabuleiro no ficheiro. */
    comando_gr(estado, fp);
    estado->num_comando++;
/* Fecha novamente o documento */
    fclose(fp);
    estado->num_comando++;  
}

/// COAMANDO LER ///

/**
\brief Função que atualiza o tabuleiro de um estado atravé de um ficheiro.
*/
void ler_linha(ESTADO *estado, char linha[], int l)
{   
    char casa;
    for(int coluna = 0; coluna < 8; coluna++) 
    { 
        casa = linha[ coluna ];
        estado->tab[ l ][ coluna ] = casa;
        if ( casa == BRANCA ) estado->num_comando++;
    } 
} 

/**
\brief Executa o comando ler, lendo o que está no ficheiro que recebe.
*/
void comando_ler(FILE *fp,ESTADO *estado)
{
    COORDENADA coord1 = {-1,-1}, coord2 = {-1,-1};
    char linha[BUF_SIZE];
    int l ;
    int n_comando_inicial = estado->num_comando;
    char col1[2], lin1[2];
    char col2[2], lin2[2];
    estado->num_comando = 0;

    for( l = 7; l >= 0; l--)
    {
        if (fgets(linha, BUF_SIZE, fp))   ler_linha(estado, linha, l);
    } 

    if (fgets(linha,BUF_SIZE, fp))
    {
        while ( fgets(linha,BUF_SIZE, fp) != NULL  )
        {
            if ( sscanf( linha , "%d: %[a-h]%[1-8] %[a-h]%[1-8]", &l, col1, lin1, col2, lin2) == 5)
            {   
                coord1.linha = *lin1 - '1' ;      coord1.coluna = *col1 - 'a';
                coord2.linha = *lin2 - '1' ;      coord2.coluna = *col2 - 'a';
                guarda_Jogadas_2(estado, coord1, coord2, l-1);
                estado->num_comando = 2*l;
            }
            else
            {
                sscanf( linha, "%d: %[a-h]%[1-8]",&l, col1, lin1);
                coord1.linha = *lin1 - '1' ;
                coord1.coluna = *col1 - 'a';
                guarda_Jogadas_1(estado, coord1, l-1);
                estado->num_comando = 2*l - 1;
            }
        }
        estado->num_jogadas = l;
        atualiza_estado_comando_ler(estado);
        estado->num_comando = n_comando_inicial+1;
    }
    else fprintf(stdout, "O coamndo ler falhou");
}

void ler(ESTADO *estado, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)    printf("O ficheiro não abriu.\n");
    else 
    {
/* Lê o tabuleiro que está no ficheiro e imprime. */
        comando_ler(fp, estado);
/* Fecha o ficheiro */
        fclose(fp);
    }
}
/// MELHOR JOGADA ///
int muda_jogador(int player)
{
    if (player ==1 ) player = 2 ;
    else player = 1;
    return player;
}

/// ESTRATEGIA MINMAX ///

/**
\brief Função que executa o MinMax, retornando o valor de uma determinada jogada.
*/
int MinMax(ESTADO *estado,COORDENADA *coord, int alpha, int betha, int nosso_jogador, int n_avaliar)
{
    ESTADO *estado_copia = cria_estado_copia(estado);

    /* atualiza estado copia */
    int x = (*coord).linha;
    int y = (*coord).coluna;
    COORDENADA coord_ = {x , y};

    // printf("coord ");
    // printf("    %d  %d\n", coord_.linha, coord_.coluna);

    atualiza_estado(estado_copia, coord_);

    /* verifica se o jogo acabou */
    int ganhou = avaliar_jogada(estado_copia, nosso_jogador);
    if (ganhou !=0) return ganhou;

    /* verifica se a rodada acaba */
    if ( n_avaliar <= 0 ) return avaliar_estado_jogo(estado, nosso_jogador);

    LISTA Lista_coords =  cria_lista_coords_possiveis(estado);

    int maxValor = -9999 , minValor = 9999;
    int valor;

    /* se formos nos a jogar */
    if (nosso_jogador == estado->jogador_atual)
    {   
        for ( ; !(lista_esta_vazia( Lista_coords ) ) ; Lista_coords = proximo( Lista_coords ))  // aquele ou este?? Lista_coords = remove_cabeca( Lista_coords ))?
        {
            valor = MinMax(estado_copia, devolve_cabeca(Lista_coords ) , alpha, betha, nosso_jogador, n_avaliar-1);
            maxValor = max(maxValor, valor);
            alpha = max(alpha, valor);
            if (betha <= alpha) break;
            //free(estado_copia);
            return maxValor;
        }
    }
    else
    {
        for ( ; !(lista_esta_vazia( Lista_coords ) ) ; Lista_coords = proximo(Lista_coords) )
        {
            valor = MinMax(estado_copia , devolve_cabeca( Lista_coords ) ,alpha, betha, nosso_jogador , n_avaliar-1 ); ///true
            minValor = min(minValor, valor);
            betha = min(betha, valor);
            if (betha <= alpha) break;
            //free(estado_copia);
            return minValor;  
        }
    } 
    return 0;
}


/**
\brief Função que inicia o MinMax, retornando a melhor COORDENADA a ser efetuada.
*/
COORDENADA *Iniciar_MinMax(ESTADO *estado)
{
    ESTADO *estado_copia = cria_estado_copia(estado);
    LISTA Lista_coords =  cria_lista_coords_possiveis(estado);
    /* valor da melhor jogada possivel */
    int best_Move;
    /* coord melhor jogada possivel */
    COORDENADA *best_Coord = devolve_cabeca( Lista_coords );
    
    /* dados auxiliares */
    int atual;

    best_Move = MinMax( estado_copia, devolve_cabeca( Lista_coords ), -99999 , 99999  , estado->jogador_atual, 10);
    best_Coord = devolve_cabeca( Lista_coords );

    for ( Lista_coords = proximo( Lista_coords ) ; !(lista_esta_vazia( Lista_coords ) ) ; Lista_coords = proximo( Lista_coords ) )
    {
        atual = MinMax( estado_copia , devolve_cabeca( Lista_coords ), -99999, 99999  , estado->jogador_atual , 10);
        //printf("\n\n%d\n\n", atual);
        if ( atual > best_Move )
        {
            best_Move = atual;
            best_Coord = devolve_cabeca( Lista_coords );
        }
    }
   // }
    /* deveria se libertar a memoria do estado copia !!!!!!!!!!!!!!!!!! */
    //free(estado_copia);
    return best_Coord ;
}

/**
\brief Função que devolve a melhor coordenada a ser efetuada pelo boot ou uma coordenada inválida se a jogada for inválida.
*/
COORDENADA jogada_boot(ESTADO *estado)
{
    COORDENADA *coord;
    COORDENADA coord_resul = { -1 , -1 };
    int ganhou = verifica_Vitoria(estado);
    if (!ganhou) 
    {
        printf("\nestou aqui inicio\n");

        coord = Iniciar_MinMax(estado);

        int x = (*coord).linha;
        int y = (*coord).coluna;
        COORDENADA coord_test = {x,y};

        printf("coord feita final\n");
        printf("coord ");
        printf("    %d  %d\n", coord_test.linha, coord_test.coluna);
        
        if ( x>=0 && x<=7 &&  y>=0 && y<=7 )
        {
            if (verifica_jogada(estado, coord_test)) coord_resul = coord_test;
        }
        else fprintf(stdout, "A coordenada obtida é invalida\n");
    }
    else fprintf(stdout, "O jogo terminou\n");

    /// caso a coordenada seja inválida posso chamar a funcao que da a coord em funcao da distancia
    /// assim o codigo mesmo q falhe irá dar algum resultado

    return coord_resul;
}


/// DA COORDENADA ALEATÓRIA ///

/**
\brief Função que devolve uma coordenada aleatória possível a ser jogada.
*/
COORDENADA da_coordenada(ESTADO *estado)
{
    COORDENADA coord = estado->ultima_jogada;
    //COORDENADA *coord_;  
    //coord_->linha = -1;  coord_->coluna  = -1;
    //LISTA lista_coords = cria_lista_coords_possiveis(estado);
    
    COORDENADA coord1 = { coord.coluna + 1 , coord.linha + 1 };
    if (verifica_coord(coord1) && verifica_jogada(estado ,coord1) &&  estado->tab[ coord1.linha ][ coord1.coluna ] != BRANCA) return coord1;
    COORDENADA coord2 = { coord.coluna + 1 , coord.linha };
    if (verifica_coord(coord2) && verifica_jogada(estado ,coord2) &&  estado->tab[ coord2.linha ][ coord2.coluna ] != BRANCA ) return coord2;
    COORDENADA coord3 = { coord.coluna + 1 , coord.linha - 1 };
    if (verifica_coord(coord3) && verifica_jogada(estado ,coord3) &&  estado->tab[ coord3.linha ][ coord3.coluna ] != BRANCA) return coord3;
    COORDENADA coord5 = { coord.coluna - 1 , coord.linha - 1 };
    if (verifica_coord(coord5) && verifica_jogada(estado ,coord5) &&  estado->tab[ coord5.linha ][ coord5.coluna ] != BRANCA) return coord5;
    COORDENADA coord6 = { coord.coluna - 1, coord.linha };
    if (verifica_coord(coord6) && verifica_jogada(estado ,coord6) &&  estado->tab[ coord6.linha ][ coord6.coluna ] != BRANCA) return coord6;
    COORDENADA coord7 = { coord.coluna - 1 , coord.linha + 1 };
    if (verifica_coord(coord7) && verifica_jogada(estado ,coord7) &&  estado->tab[ coord7.linha ][ coord7.coluna ] != BRANCA) return coord7;
    COORDENADA coord8 = { coord.coluna, coord.linha + 1 };
    if (verifica_coord(coord8) && verifica_jogada(estado ,coord8) &&  estado->tab[ coord8.linha ][ coord8.coluna ] != BRANCA) return coord8;
    COORDENADA coord4 = { coord.coluna , coord.linha- 1 };
    if (verifica_coord(coord4) && verifica_jogada(estado ,coord4) &&  estado->tab[ coord4.linha ][ coord4.coluna ] != BRANCA) return coord4;
    return coord;
}

/// COORDENADA ATRAVÉS DA MENOR DISTÃNCIA /// 

/**
\brief Função que devolve a coordenada, possível a ser jogada que se encontre a menor distância da casa do jogador.
*/
COORDENADA da_coordenada_distancia(ESTADO *estado)
{
    COORDENADA coord = estado->ultima_jogada;
    COORDENADA coord_result = coord;
    int dist_best = distancia_coord(coord, estado->jogador_atual);
    float i;

    COORDENADA coord1 = { coord.coluna + 1 , coord.linha + 1 };
    if (verifica_coord(coord1) && estado->tab[ coord1.linha ][ coord1.coluna ] != BRANCA) 
    {
        i = distancia_coord( coord1, estado->jogador_atual);
        if(  i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord1;
        }
    }
    
    COORDENADA coord2 = { coord.coluna + 1 , coord.linha };
    if (verifica_coord(coord2) && estado->tab[ coord2.linha ][ coord2.coluna ] != BRANCA)
    {
        i = distancia_coord( coord2, estado->jogador_atual);
        if( i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord2;
        }
    }

    COORDENADA coord3 = { coord.coluna + 1 , coord.linha - 1 };
    if (verifica_coord(coord3) && estado->tab[ coord3.linha ][ coord3.coluna ] != BRANCA) 
    {
        i = distancia_coord( coord3, estado->jogador_atual);
        if( i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord3;
        }
    }

    COORDENADA coord5 = { coord.coluna - 1 , coord.linha - 1 };
    if (verifica_coord(coord5) && estado->tab[ coord5.linha ][ coord5.coluna ] != BRANCA)
    {
        i = distancia_coord( coord5, estado->jogador_atual);
        if(  i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord5;
        }
    }

    COORDENADA coord6 = { coord.coluna - 1, coord.linha };
    if (verifica_coord(coord6) && estado->tab[ coord6.linha ][ coord6.coluna ] != BRANCA)
    {
        i = distancia_coord( coord6, estado->jogador_atual);
        if(  i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord6;
        }
    } 

    COORDENADA coord7 = { coord.coluna - 1 , coord.linha + 1 };
    if (verifica_coord(coord7) && estado->tab[ coord7.linha ][ coord7.coluna ] != BRANCA)
    {
        i = distancia_coord( coord7, estado->jogador_atual);
        if( i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord7;
        }
    } 

    COORDENADA coord8 = { coord.coluna , coord.linha + 1 };
    if (verifica_coord(coord8) && estado->tab[ coord8.linha ][ coord8.coluna ] != BRANCA)
    {
        i = distancia_coord( coord8, estado->jogador_atual);
        if(i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord8;
        }
    }

    COORDENADA coord4 = { coord.coluna , coord.linha - 1 };
    if (verifica_coord(coord4) && estado->tab[ coord4.linha ][ coord4.coluna ] != BRANCA ) 
    {
        i = distancia_coord( coord4, estado->jogador_atual);
        if( i<=dist_best ) 
        {
            dist_best = i;
            coord_result = coord4;
        }
    }  
    return coord_result;
}

/**
\brief Função que verifica se foi o nosso jogador a ganhar.
*/
int jogador_vencedor(ESTADO *estado, int nosso_player)
{
    if ( estado->ultima_jogada.linha == 0 && estado->ultima_jogada.coluna == 0  && nosso_player == 1 ) return 1;
    if ( estado->ultima_jogada.linha == 7 && estado->ultima_jogada.coluna == 7  && nosso_player == 2 ) return 1;
    return 0;
}

/**
\brief Função que devolve a coordenada, possível a ser jogada que se encontre a menor distância da casa do jogador.
*/
COORDENADA obtem_coord_atraves_da_distancia(ESTADO *estado)
{
    COORDENADA coord_result = estado->ultima_jogada,
               aux;
               
    COORDENADA *coord_ ;
    LISTA lista_coords = cria_lista_coords_possiveis(estado);

    int dist_best = 1000; 
    float i; 
    
    while ( !lista_esta_vazia(lista_coords) )
    {
        coord_ = devolve_cabeca(lista_coords);

        aux.linha = ((*coord_).linha) ;
        aux.coluna = ((*coord_).coluna);
        //free(coord_);
        if (verifica_coord(aux) && estado->tab[ aux.linha ][ aux.coluna ] != BRANCA ) 
        {            
            i = distancia_coord( aux , estado->jogador_atual);
            if( i <= dist_best ) 
            {
                ESTADO *estado_copia = cria_estado_copia(estado);
                atualiza_estado(estado_copia, aux);

                if ( verifica_Vitoria( estado_copia ) && jogador_vencedor(estado_copia, estado->jogador_atual) )
                {
                    dist_best = i;
                    coord_result = aux;
                }

                if ( !verifica_Vitoria( estado_copia ) )
                {
                    dist_best = i;
                    coord_result = aux;
                }
            }
        } 
        lista_coords = remove_cabeca(lista_coords); 
    } 
    return coord_result;
}

/// main ///
/**
\brief Função que atualiza o estado do jogo através da coordenada obtida.
*/
void atualiza_jogada_boot(ESTADO *estado){
    COORDENADA coord = obtem_coord_atraves_da_distancia(estado);

    if( verifica_coord(coord) && verifica_jogada(estado, coord))         
        jogar(estado, coord);
    else
    {
        coord = da_coordenada(estado);
        if( verifica_coord(coord) && verifica_jogada(estado, coord))
                jogar(estado, coord);
        else  fprintf(stdout,"O comando jogar falhou.\n");
    }
}

/**
\brief MAIN do boot.
*/
int main(int argc, char *argv[])
{    
    int resul = 1;
    ESTADO *estado;
    estado = inicializador_estado();

    if(argc == 3) 
    {
        /* le o ficheiro */
        ler(estado, argv[1]);
        /* jogada boot */
        atualiza_jogada_boot( estado );
        /*gravar ficheiro */
        gr(estado, argv[2]);
        resul = 0;
    }
    return resul;
}