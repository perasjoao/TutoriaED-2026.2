#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int val;
    int linha,coluna;
    struct no* next;
    struct no*prev;
}no;

typedef struct matriz{
    no*dummie_linha;
    no*dummie_coluna;
}matriz;

no*create_dummie_linha(){
    no*dummie=calloc(1,sizeof(no));
    dummie->linha=-1;
    return dummie;
}

no*create_dummie_coluna(){
    no*dummie=calloc(1,sizeof(no));
    dummie->coluna=-1;
    return dummie;
}

no*create_node(int linha, int coluna, int val){
    no*elemento=calloc(1,sizeof(no));
    elemento->coluna=coluna;
    elemento->linha=linha;
    elemento->val=val;
    return elemento;
}

matriz*create_matriz(int linhas, int colunas){
    matriz*m=calloc(1,sizeof(matriz));

    m->dummie_linha=create_dummie_linha();
    m->dummie_coluna=create_dummie_coluna();
    no*aux_linha=m->dummie_linha;
    no*aux_coluna=m->dummie_coluna;
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



void add_elemento(no**dummie_linha_ref, no**dummie_coluna_ref,int val,int coluna, int linha){
    no*dummie_linha=*dummie_linha_ref;
    no*dummie_coluna=*dummie_coluna_ref;


    no*elemento=create_node(linha,coluna,val);

            elemento->next=dummie_linha->prev;
            dummie_linha->prev=elemento;
            elemento->prev=dummie_coluna->prev;
            dummie_coluna->prev=elemento;
}

int acessa_elemento(matriz*m,int linha, int coluna){
    no*dummie_linha=m->dummie_linha;
    no*dummie_coluna=m->dummie_coluna;
        while(linha>0){
            dummie_linha=dummie_linha->next;
            linha--;
        }
        while(dummie_linha->coluna!=coluna){
            dummie_linha=dummie_linha->prev;
        }
        return dummie_linha->val;

        

}
