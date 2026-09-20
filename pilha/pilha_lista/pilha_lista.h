#include <stdlib.h>

typedef struct no{
    int val;
    struct no*next;
}no;

typedef struct pilha{
    no*topo;
}pilha;

no*create_node(int val);

pilha* cria_pilha();

void destroi_pilha(pilha**s_ref);

void empilhar(pilha*s, int val);

int peek(pilha*s);

int desempilhar(pilha*s);