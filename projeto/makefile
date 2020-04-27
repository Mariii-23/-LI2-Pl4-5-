CFLAGS=-g
jogo.exe : main.o Logica_do_programa.o Interface.o Camada_de_Dados.o Melhor_Jogada.o listas.o
	gcc -Wall -o jogo.exe main.o Logica_do_programa.o Interface.o Camada_de_Dados.o Melhor_Jogada.o listas.o
#	gcc -std=gnu11 -Wall -Wextra -pedantic-errors -O main.o Logica_do_programa.o Interface.o Camada_de_Dados.o Melhor_Jogada.o listas.o
#	gcc -std=gnu11 -Wall -Wextra -pedantic-errors -O *.c

main.o : main.c Camada_de_Dados.h Interface.h Logica_do_programa.h dados.h

Camada_de_Dados.o : Camada_de_Dados.c  Interface.h Logica_do_programa.h dados.h

Logica_do_programa.o : Logica_do_programa.c Camada_de_Dados.h dados.h

Interface.o : Interface.c  Camada_de_Dados.h Logica_do_programa.h dados.h Melhor_Jogada.h

listas.o : listas.c dados.h Camada_de_Dados.h Logica_do_programa.h Interface.h 

Melhor_Jogada.o : Melhor_Jogada.c  dados.h Camada_de_Dados.h Logica_do_programa.h Interface.h listas.h

clean : 
	rm *.o
	rm jogo.exe