#include "listas_simples.h"

no* cria_lista(){
    return NULL;
}

void destruir_lista(no**lista){
    no*p=*lista;
    no*aux;
    while(p!=NULL){
        aux=p->next;
        free(p);
        p=aux;
    }
    *lista=NULL;
}

no*cria_no(int val){
    no*n = calloc(1,sizeof(no));
    n->val=val;
    return n;
}

no*adiciona_lista(no*lista,int val){
    no*n=cria_no(val);
    n->next=lista;
    return n;
}

no*remove_lista_valor(no*lista,int val){
    no*p=lista;
    no*prev;
    while(p!=NULL && p->val!=val){
        prev=p;
        p=p->next;
    }
    if(p!=NULL){ // se nao for null o elemento esta na lista
        if(p==lista){ // se for igual a lista parada free no primeiro elemento e return no segundo
            lista=lista->next;
        }
        else{
            prev->next=p->next; // se n for o primeiro ele esta no meio, ento corrige o next do anterior
        }
        free(p);
    }
    return lista;
}

no*remove_lista_no(no*lista,no* n){
    no*p=lista;
    no*prev;
    while(p!=NULL && p!=n){
        prev=p;
        p=p->next;
    }
    if(p!=NULL){
        if(p==lista){
            lista=lista->next;
        }
        else{
            prev->next=p->next;
        }
        free(p);
    }
    return lista;
}

no*busca_recursiva(no*lista,int val){
    if(lista==NULL || lista->val==val){return lista;}
    return busca_recursiva(lista->next,val);
}

void imprime(no*lista){
    no*p=lista;
    while(p!=NULL){
        printf("%d\n", p->val);
        p=p->next;
    }
}

void imprime_recursivo(no*lista){
    if(lista==NULL){ return; }
    printf("%d\n", lista->val);
    imprime_recursivo(lista->next);
}

no* copiar_lista_recursivo(no*lista){
    if(lista==NULL){return NULL;}
    no*copia=calloc(1,sizeof(no));
    copia->val=lista->val;
    copia->next=copiar_lista_recursivo(lista->next);
    return copia;
}

no* copia_lista(no*lista){
    if(lista==NULL){return NULL;}
    no*copia=calloc(1,sizeof(no));
    no*save=copia;
    while(lista!=NULL){
        copia->val=lista->val;
        if(lista->next!=NULL){ //para nao alocar o no fantasma no final da lista;
            copia->next= calloc(1,sizeof(no));
            copia=copia->next;
        }
        lista=lista->next;
    }
    copia->next=NULL;
    return save;
}

no*inverte_lista_recursivo(no*lista){
    if(lista==NULL || lista->next==NULL) return lista;
    no* nova_cabeca= inverte_lista_recursivo(lista->next);
    lista->next->next=lista; //inverte a direçao dos ponteiros;
    lista->next=NULL; //quebra a ligaçao de ponteiros atiga;
    return nova_cabeca;
}

no*inverte_lista(no*lista){
    no*atual,*ant,*invertida;
    invertida=NULL;
    atual=lista;
    while(atual != NULL){
        ant=atual;
        atual = ant->next;
        ant->next= invertida;
        invertida = ant;
    }
    return invertida;
}

no*concatenar_lista_recursivo(no*lista1,no*lista2){
    if(lista1==NULL) return lista2;
    lista1->next=concatenar_lista(lista1->next,lista2);
    return lista1;
}

no*concatenar_lista(no*lista1,no*lista2){
    if(lista1==NULL) return lista2;
    no*p=lista1;
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=lista2;
    return lista1;
}