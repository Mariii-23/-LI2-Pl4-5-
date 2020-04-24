

int main(int argc, char *argv[])
{    
    if(argc == 4) 
    {
        int tarefa = atoi(argv[1]);
        int dim = atoi(argv[2]);
        int valor = atoi(argv[3]);
        auxiliar_exercicio(tarefa, dim, valor);
    }
    return 0;
}