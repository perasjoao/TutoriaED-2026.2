#include <stdlib.h>
typedef struct no{
    int val;
    struct no*next;
}no;

typedef struct pilha{
    no*topo;
}pilha;

no*create_node(int val){
    no*n=calloc(1,sizeof(no));
    n->val=val;
    return n;
}

pilha* cria_pilha(){
    pilha*s=calloc(1,sizeof(pilha));
    return s;
}

void destroi_pilha(pilha**s_ref){
    pilha*s=*s_ref;
    no*p=s->topo;
    no*aux=p;
        while(p!=NULL){
            aux=p->next;
            free(p);
            p=aux;
        }
        free(s);
        *s_ref=NULL;
}

void empilhar(pilha*s, int val){
    no*n=create_node(val);
    n->next=s->topo;
    s->topo=n;
}

int peek(pilha*s){
    if(s->topo==NULL){
        puts("pilha esta vazia!");
        return -1;
    }
    return s->topo->val;
}

int desempilhar(pilha*s){
    if(s->topo==NULL){
        puts("a pilha esta vazia!");
        return -1;
    }
    int save=s->topo->val;
    no*remove=s->topo;
    s->topo=s->topo->next;
    free(remove);
    return save;
}