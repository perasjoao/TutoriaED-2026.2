#include "fila_lista.h"
#include "pilha_lista.h"

int eh_palindromo(char str[]){
    pilha*p=cria_pilha();
    fila*f=cria_fila();
    int i;
    for(i=0; str[i]!='C'; i++){
        empilhar(p,str[i]);
    }
    i++;
    for(;str[i]!='\0'; i++){
        enfileira(f,str[i]);
    }
   
    while(!pilha_eh_vazia(p) && fila_eh_vazia(f)!=0){
        if(pop(p)!=densifila(f)){
            return 0;
        }
    }
    if(!pilha_eh_vazia(p) || !fila_eh_vazia(f)){
        return 0;
    }
    return 1;
}
