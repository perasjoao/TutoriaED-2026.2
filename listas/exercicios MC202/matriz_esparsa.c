#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    int linha,coluna;
    struct node* next;
    struct node*prev;
}node;

typedef struct matriz{
    node*dummie_linha;
    node*dummie_coluna;
}matriz;

node*create_dummie_linha(){
    node*dummie=calloc(1,sizeof(node));
    dummie->linha=-1;
    return dummie;
}

node*create_dummie_coluna(){
    node*dummie=calloc(1,sizeof(node));
    dummie->coluna=-1;
    return dummie;
}

node*create_node(int linha, int coluna, int val){
    node*elemento=calloc(1,sizeof(node));
    elemento->coluna=coluna;
    elemento->linha=linha;
    elemento->val=val;
    return elemento;
}

matriz*create_matriz(int linhas, int colunas){
    matriz*m=calloc(1,sizeof(matriz));

    m->dummie_linha=create_dummie_linha();
    m->dummie_coluna=create_dummie_coluna();
    node*aux_linha=m->dummie_linha;
    node*aux_coluna=m->dummie_coluna;
        while(linhas>1){
            aux_linha->next=create_dummie_linha();
            aux_linha=aux_linha->next;
            linhas--;
        }
        while(colunas>1){
            aux_coluna->next=create_dummie_coluna();
            aux_coluna=aux_coluna->next;
            colunas--;
        }

        return m;
}



void add_elemento(node**dummie_linha_ref, node**dummie_coluna_ref,int val,int coluna, int linha){
    node*dummie_linha=*dummie_linha_ref;
    node*dummie_coluna=*dummie_coluna_ref;


    node*elemento=create_node(linha,coluna,val);

            elemento->next=dummie_linha->prev;
            dummie_linha->prev=elemento;
            elemento->prev=dummie_coluna->prev;
            dummie_coluna->prev=elemento;
}

int acessa_elemento(matriz*m,int linha, int coluna){
    node*dummie_linha=m->dummie_linha;
    node*dummie_coluna=m->dummie_coluna;
        while(linha>0){
            dummie_linha=dummie_linha->next;
            linha--;
        }
        while(dummie_linha->coluna!=coluna){
            dummie_linha=dummie_linha->prev;
        }
        return dummie_linha->val;

        

}
