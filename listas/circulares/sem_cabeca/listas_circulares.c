#include "listas_circulares.h"

no* cria_no(int val){
    no*n=calloc(1,sizeof(no));
    n->val=val;
    return n;
}

no* cria_lista(){
    return NULL;
}

no*add_circular(no*lista, int val){
    no*n=cria_no(val);
    if(lista==NULL){
        n->next=n;
        return n;
    }
    n->next=lista->next;
    lista->next=n;
    return lista;
}

no* remove_circular(no*lista, no*n){
    if(lista==NULL || n==NULL) return lista;
    if(n->next==n){
        free(n);
        return NULL;
    }
    no* ant= n;
    while(ant->next!=n){
        ant=ant->next;
    }
    if(lista==n){ // se for a cabeça precia arrumar para nao perder a referencia
        lista=ant;
    }
    ant->next=n->next;
    free(n);
    return lista;
}

void imprime_circular(no*lista){
    no*atual=lista->next;
    do{
        printf("%d\n", atual->val);
        atual=atual->next;
    }while(atual!=lista->next);
}