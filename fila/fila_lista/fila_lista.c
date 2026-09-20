#include "fila_lista.h";

typedef struct no{
    struct no*next;
    int val;
}no;

typedef struct{
    no*inicio;
    no*fim;
}fila;

no*cria_no(int val){
    no*n=calloc(1,sizeof(no));
    n->val=val;
    return n;
}


void enfileira(fila*f,int val){
    no*n=cria_no(val);
    if(f->inicio==NULL && f->fim==NULL){
        f->inicio=NULL;
    }
    else{
        f->fim->next=n;
    }
    f->fim=n;
}

int desenfileira(fila*f,int val){
    int save=f->inicio->val;
    no*aux=f->inicio;
    f->inicio=f->inicio->next;
    if(aux==f->fim){
        f->fim=NULL;
    }
    free(aux);
    return save;
}

fila*cria_fila(){
    fila*f=calloc(1,sizeof(fila));
    return f;
}

void destruir_fila(fila*f){
    no*p=f->inicio;
    no*aux;
    while(p!=NULL){
        aux=p->next;
        free(p);
        p=aux;
    }
    free(f);
}