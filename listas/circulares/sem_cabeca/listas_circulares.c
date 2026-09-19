#include "listas_circulares.h"

no* cria_no(int val){
    no*n=calloc(1,sizeof(no));
    n->val=val;
    return n;
}

no* cria_lista(){
    return NULL;
}

no*add_circular(int val,no*lista){
    no*n=cria_no(val);
    if(lista==NULL){
        n->next=n;
        return n;
    }
    n->next=lista->next;
    lista->next=n;
    return;
}