jogo.exe : main.o Logica_do_programa.o Interface.o Camada_de_Dados.o
	gcc -Wall -o jogo.exe main.o Logica_do_programa.o Interface.o Camada_de_Dados.o 

main.o : main.c Camada_de_Dados.h Interface.h Logica_do_programa.h dados.h
	gcc -c main.c

Logica_do_programa.o : Logica_do_programa.c Camada_de_Dados.h dados.h
	gcc -c Logica_do_programa.c 

Interface.o : Interface.c  Camada_de_Dados.h Logica_do_programa.h dados.h
	gcc -c Interface.c 

Camada_de_Dados.o : Camada_de_Dados.c  Interface.h Logica_do_programa.h dados.h
	gcc -c Camada_de_Dados.c 

clean : 
	rm *.o
	rm jogo.exe