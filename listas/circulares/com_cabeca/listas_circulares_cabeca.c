#include "listas_circulares_cabeca.h"

//a cabeça sempre sera um no que nunca será alterado

no*cria_no(int val){
    no*n=calloc(1,sizeof(no));
    n->val=val;
    return n;
}

no*cria_lista(){
    no*cabeca=cria_no(0);
    cabeca->next=cabeca;
    return cabeca;
}

no*adiciona_circular(no*lista,int val){
    no*n=cria_no(val);
    n->next=lista->next;
    lista->next=n;
    return lista;
}

no*remove_circular(no*lista,no* n){
    if(lista==NULL || n==NULL) return lista;
    no* ant= n;
    while(ant->next!=n){
        ant=ant->next;
    }
    ant->next=n->next;
    free(n);
    return lista;
}
