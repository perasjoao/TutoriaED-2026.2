#include "fila_vetor.h"

fila*cria_fila(int capacidade){
    fila*f=calloc(1,sizeof(fila));
    f->v=calloc(capacidade,sizeof(int));
    f->capacidade=capacidade;
    return f;
}

void enfileira(fila*f,int val){
    f->v[f->fim]=val;
    f->fim=(f->fim+1)%f->capacidade;
    f->tamanho++;
}

int desenfileira(fila*f,int val){
    int save=f->v[f->inicio];
    f->inicio=(f->inicio+1)%f->capacidade;
    f->tamanho--;
    return save;
}