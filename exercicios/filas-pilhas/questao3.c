#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int val;
    int max_atual;
    struct no* next;
}no;


typedef struct pilha{
    no*top;
}pilha;

no*cria_no(int val){
    no*n=calloc(1,sizeof(no));
    n->val=val;
    return n;
}

pilha*cria_pilha(){
    pilha*p=calloc(1,sizeof(pilha));
    return p;
}

void push(pilha*p, int val){
    no*n=cria_no(val);
    if(p->top==NULL){
        p->top=n;
        n->max_atual=n->val;
        return;
    }
    n->next=p->top;
    p->top=n;
    if(n->val > n->next->max_atual){
        n->max_atual=n;
        return;
    }
    n->max_atual=n->next->max_atual;
}

int pop(pilha*p){
    int save=p->top->val;
    no*aux=p->top;
    p->top=p->top->next;
    free(aux);
    return save;
}

int Max(pilha*p){
    return p->top->max_atual;
}

int peek(pilha*p){
    return p->top->val;
}