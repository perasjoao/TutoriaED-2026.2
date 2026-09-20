#include <stdlib.h>

typedef struct{
    int*v;
    int topo;
    int capacidade; //no material nao é usado para fins didáticos
}pilha;

pilha* cria_pilha();

void destroi_pilha(pilha**s_ref);

void empilhar(pilha*s, int val);

int peek(pilha*s);

int desempilhar(pilha*s);