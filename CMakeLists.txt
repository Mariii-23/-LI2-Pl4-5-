cmake_minimum_required(VERSION 3.15)
project(LI2-JOGO C)

set(CMAKE_C_STANDARD 99)

add_executable(LI2-JOGO main.c dados.h Logica_do_programa.c Logica_do_programa.h Interface.c Interface.h Camada_de_Dados.c Camada_de_Dados.h)
