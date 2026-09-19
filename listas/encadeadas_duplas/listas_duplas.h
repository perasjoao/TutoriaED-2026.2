#include <stdlib.h>

typedef struct no{
    int val;
    struct no*next;
    struct no*prev;
}no;

typedef struct lista{
    no*inicio;
    no*fim;
}lista;

no* cria_no(int val);

lista* cria_lista();

void insere_inicio(lista*l, int val);

void insere_fim(lista*l,int val);

void remove_lista(lista*l,int val);