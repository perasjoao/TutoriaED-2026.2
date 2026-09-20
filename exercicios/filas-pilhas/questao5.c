#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int val;
    struct node*next;
    struct node*prev;
}node;

typedef struct fila{
    node*inicio;
    node*fim;
}fila;

node*create_node(int val){
    node*n=calloc(1,sizeof(node));
    n->val=val;
    return n;
}

fila*create_fila(){
    fila*f=calloc(1,sizeof(fila));
    return f;
}

bool fila_vazia(fila*f){
    if(f->fim==NULL || f->inicio==NULL){
        return true;
    }
    return false;
}

void insere_no_inicio(fila*f, int val){
    node*n=create_node(val);
    if(fila_vazia(f)){
        f->fim=n;
    }
    else{
        f->inicio->prev=n;
    }
    n->next=f->inicio;
    f->inicio=n;
}

void insere_no_final(fila*f,int val){
    node*n=create_node(val);
    if(fila_vazia(f)){
        f->inicio=n;
    }
    else{
        f->fim->next=n;
    }
    n->prev=f->fim;
    f->fim=n;
}

int remove_inicio(fila*f){
    if(fila_vazia(f)){
        return -178;
    }
    int save=f->inicio->val;
    node*remove=f->inicio;
    f->inicio=f->inicio->next;
    free(remove);
    if(f->inicio==NULL){
        f->fim=NULL;
    }
    else{
        f->inicio->prev=NULL;
    }
    return save;
}

int remove_fim(fila*f){
    if(fila_vazia(f)){
        return -137;
    }
    int save=f->fim->val;
    node*remove=f->fim;
    f->fim=f->fim->prev;
    free(remove);
    if(f->fim==NULL){
        f->inicio=NULL;
    }
    else{
        f->fim->next=NULL;
    }
    return save;
}

void print_fila(fila*f){
    node*p=f->inicio;
    while(p!=NULL){
        printf("%d -> ", p->val);
        p=p->next;
    }
    puts("NULL");
}