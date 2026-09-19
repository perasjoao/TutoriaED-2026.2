#include <listas_simples.h>

no*insere_ordenado(no*lista, int val){
    no*n=cria_no(val);
    no*p=lista;
    no*aux=lista;
        if(lista==NULL){
            return n;
        }
        while(p->val<=val && p!=NULL){
            aux=p;
            p=p->next;
        }
        if(p==NULL){
            aux->next=n;
            return lista;
        }
        if(p==lista){
            n->next=p;
            return n;
        }
        n->next=p;
        aux->next=n;
        return lista;
}

no*junta_lista_ordenado(no*lista1,no*lista2){
    no*p1=lista1;
    no*p2=lista2;
    no*nova_lista=cria_lista();
    while(p1!=NULL && p2!=NULL){
        if(p1->val <= p2->val){
            nova_lista=adiciona_lista(nova_lista,p1->val);
        }
        else{
            nova_lista=adiciona_lista(nova_lista,p2->val);
        }
    }

    while(p1!=NULL){
        nova_lista=adiciona_lista(nova_lista,p1->val);
    }
    while(p2!=NULL){
        nova_lista=adiciona_lista(nova_lista,p2->val);
    }
    return nova_lista;
}

no*junta_lista(no*lista1,no*lista2){
    if(lista1==NULL) return lista2;
    lista1->next=concatenar_lista(lista1->next,lista2);
    return lista1;
}