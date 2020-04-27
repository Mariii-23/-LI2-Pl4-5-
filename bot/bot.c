#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BUF_SIZE 1024
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

/**
\brief Função que verifica se uma COORDENADA é válida.
*/
int verifica_coord(COORDENADA coord)
{
    int x = coord.linha;
    int y = coord.coluna;
    return ( x>=0 && x<=7 &&  y>=0 && y<=7 );
}

/// FUNCOES LISTAS ///
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
   // LISTA l = malloc(sizeof( NLista )); //LISTA l = malloc(sizeof( NLista));
   // l->valor = NULL;
    //l->next = NULL;
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
    //LISTA aux = criar_lista();
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
    //return &(*(L->valor));
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
    //LISTA aux = L;
    L = L->next;
    //free(aux);
    return L;
}

/**
\brief Função que dá o número de elementos de uma lista.
*/
int length_lista (LISTA lista)
{
    LISTA l = lista;
    int i;
    for (i=0; l != NULL ; l = l->next, i++);
    return i;
}

/// LISTA DE COORDENADAS POSSÍVEIS A SEREM EXECUTADAS ///

/**
\brief Função auxiliar que insere a coordenada na lista se esta for uma possível coordenada a ser efetuada.
*/
LISTA adiciona_lista(LISTA lista, ESTADO *estado, COORDENADA coord)
{
    COORDENADA *coord_ = (COORDENADA*)malloc(sizeof (COORDENADA)) ;
    coord_->linha = coord.linha;
    coord_->coluna = coord.coluna;

    if ( verifica_coord(coord)   &&  estado->tab[ coord.linha ][ coord.coluna ] == BRANCA )
    {    
        lista = insere_cabeca(lista, coord_); 
    }
    return lista;
}


/// ESTADO INICIAL ///

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

/// COMANDO GRAVAR ///
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
    for (int linha=7; linha>=0; linha--)   guarda_Linha( estado, linha, stream);
    fprintf(stream, "\n");
}


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

/// comando ler ///
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
    char linha[BUF_SIZE];
    COORDENADA coord1 = {-1,-1}, coord2 = {-1,-1};
    int l, n_comando_inicial = estado->num_comando, n_jogadas;
    char col1[2], lin1[2];
    char col2[2], lin2[2];
    estado->num_comando = 0;

    for( l = 7; l >= 0; l--)
    {
        fgets(linha, BUF_SIZE, fp); 
        ler_linha(estado, linha, l);
    } 
    n_jogadas = estado->num_comando  ;

    fgets(linha,BUF_SIZE, fp);
    while ( fgets(linha,BUF_SIZE, fp) != NULL  )
    {
       if ( sscanf( linha , "%d: %[a-h]%[1-8] %[a-h]%[1-8]", &l, col1, lin1, col2, lin2) == 5)
       {   
            coord1.linha = *lin1 - '1' ;        coord1.coluna = *col1 - 'a';
            coord2.linha = *lin2 - '1' ;        coord2.coluna = *col2 - 'a';
            guarda_Jogadas_2(estado, coord1, coord2, l-1);
            estado->num_comando = 2*l;
        }
        else
        {
            sscanf( linha, "%d: %[a-h]%[1-8]",&l, col1, lin1);
            coord1.linha = *lin1 - '1' ;    coord1.coluna = *col1 - 'a';
            guarda_Jogadas_1(estado, coord1, l-1);
            estado->num_comando = 2*l - 1;
        }
    }
    estado->num_jogadas = l;
    atualiza_estado_comando_ler(estado);
    estado->num_comando = n_comando_inicial+1;
}

void ler(ESTADO *estado, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)   printf("O ficheiro não abriu.\n");
    else 
    {
/* Lê o tabuleiro que está no ficheiro e imprime. */
        comando_ler(fp, estado);
/* Fecha o ficheiro */
        fclose(fp);
    }
}

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
    if (estado->jogador_atual == 1)  estado->num_jogadas += 1;
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

/**
\brief Função que devolve uma coordenada aleatória possível a ser jogada.
*/
COORDENADA da_coordenada(ESTADO *estado)
{
    COORDENADA coord = estado->ultima_jogada;
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
    return ( resul );
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

    int dist_best = 1000; //distancia_coord(coord, estado->jogador_atual);
    float i; 
    
    /* (coord_result.coluna == coord.coluna && coord_result.linha == coord.linha ) ||*/  
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
                dist_best = i;
                coord_result = aux;
            }
        } 
        lista_coords = remove_cabeca(lista_coords); 
    } 
    return coord_result;
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
        resul = 1;
    }
    return resul;
}


void atualiza_jogada_boot(ESTADO *estado){
    COORDENADA coord = obtem_coord_atraves_da_distancia(estado);
        //COORDENADA coord = da_coordenada(estado);

        /*deveria dar este */
        //COORDENADA coord = obtem_coord_atraves_da_distancia( estado );
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