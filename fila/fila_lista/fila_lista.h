#include <stdlib.h>

typedef struct no{
    struct no*next;
    int val;
}no;

typedef struct{
    no*inicio;
    no*fim;
}fila;

no*cria_no(int val);

fila*cria_fila();

void destruir_fila(fila*f);

fila_eh_vazia(fila*f);

void enfileira(fila*f,int val);

int desenfileira(fila*f,int val);