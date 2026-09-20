#include "pilha_vetor.h"

pilha* cria_pilha(int capacidade){
    pilha*s=calloc(1,sizeof(pilha));
    s->v=calloc(capacidade,sizeof(int));
    s->capacidade=capacidade;
    return s;
}

void destroi_pilha(pilha**s_ref){
    free((*(s_ref))->v);
    free(*s_ref);
    *s_ref=NULL;
}

void empilhar(pilha*s, int val){
    if(s->topo==s->capacidade) return;
    s->v[s->topo++]=val;
}

int peek(pilha*s){
    //nao chamar vazia
    return s->v[s->topo-1];
}

int desempilhar(pilha*s){
    //nao chamar vazia
    return s->v[--s->topo];
}