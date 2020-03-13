# LI2-JOGO

Laboratórios de Informática || [MIEINF]
Universidade do Minho
Turno: PL4
Grupo: 5
Jéssica Macedo Fernandes - a93318
Mariana Dinis Rodrigues - a93229
Vasco Oliveira Matos - a93206

Para o início do trabalho seguimos os passos do "Guião aula 5" disponiblizad pelos docentes de LI2.
Assim, criamos os várias camadas, "camada de dados", "Interface" e "lógica do programa".
Na parte da "camada de dados" está definida a estrutura de dados do programa, onde é definido o conceito
de "CASA"(cada local do jogo onde as peças se podem movimetar), a "CORDENADA" (que serve para localizar
cada peça na sua casa), entre outros dados essenciais.
Na parte "Lógica do programa" estão presentes as funções que vão efetuar altreções no estado do jogo,
nomeadamente na troca do estado das peças, e alterar a casa da peça em que estava, colocando uma peça branca
na nova localização e uma preta na localização anterior(usando como auxiliar a função altera_estado_peca).
Estas duas funções vão ser usadas na função "jogar" que aplica a jogada caso esta seja válida, ou retorna 
"Jogada Inválida" no caso de não ser.
Na parte da "Interface" tempos presente uma função que desenha o estado do jogo "imprimindo" o tabuleiro
por linha e por coluna(ao "imprimir" a linha, é "imprimido" cada elemento das colunas que intersetam essa linha).
Na "main" do nosso programa é inicializado o jogo, e é chamada a funçao "interpertador" com o argumento "estado"
afim de a camada de "Interface" imprimir o tabuleiro e trabalhar com as restantes funções do programa produzindo
o jogo Rastos, posteriormente funcional.