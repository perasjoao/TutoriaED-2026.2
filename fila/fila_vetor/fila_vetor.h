#include <stdlib.h>

typedef struct{
    int*v;
    int inicio,fim,capacidade,tamanho;
}fila;

fila*cria_fila(int capacidade);

void enfileira(int val);

int desenfileira(fila*f,int val);
