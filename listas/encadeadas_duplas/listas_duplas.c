#include "listas_duplas.h"

no* cria_no(int val){
    no*n=calloc(1,sizeof(no));
    n->val=val;
    return n;
}

lista* cria_lista(){
    lista*l=calloc(1,sizeof(lista));
    return l;
}

void insere_inicio(lista*l, int val){
    no*n=cria_no(val);
    if(l->fim==NULL && l->inicio==NULL){
        l->fim=n;
        l->inicio=n;
    }
    else{
        n->next=l->inicio;
        l->inicio->prev=n;
        l->inicio=n;
    }
}

void insere_fim(lista*l,int val){
    no*n=cria_no(val);
    if(l->fim==NULL && l->inicio==NULL){
        l->fim=n;
        l->inicio=n;
    }
    else{
        l->fim->next=n;
        n->prev=l->fim;
        l->fim=n;
    }
}

void remove_lista(lista*l,int val){
    no*p=l->inicio;
    while(p!=NULL && p->val!=val){
        p=p->next;
    }
    if(p!=NULL){
        if(p==l->fim){
            l->fim=p->prev;
        }
        if(p==l->inicio){
            l->inicio=p->next;
        }
        else{
            p->prev->next=p->next;
        }
        free(p);
    }
}