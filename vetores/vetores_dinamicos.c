#include "vetores_dinamicos.h";

vetor*cria_vetor(int capacidade){
    vetor*v= calloc(1,sizeof(vetor));
    v->dados= calloc(capacidade,sizeof(int));
    v->capacidade=capacidade;
    v->tamanho_atual=0;
    return v;
}

vetor*destruindo_com_retorno(vetor*v){
    free(v->dados);
    v->capacidade=0;
    v->tamanho_atual=0;
    free(v);
    return NULL;
}

void aumenta_vetor(vetor*v){
    int*save=v->dados;
    v->dados=calloc(v->capacidade*2,sizeof(int));
    for(int i=0; i<v->capacidade; i++) v->dados[i]=save[i];
    v->capacidade*=2;
    free(save);
    return;
}

void diminui_vetor(vetor*v){
    int*save=v->dados;
    v->dados= calloc(v->capacidade/4,sizeof(int));
    for(int i=0; i<v->tamanho_atual; i++) v->dados[i]=save[i];
    v->capacidade/=4;
    free(save);
    return;
}


void destruindo_vetor_referencia(vetor**vector){
    vetor*v=*vector;
    free(v->dados);
    free(*vector);
    *vector=NULL;
    return;
}

void adiciona_elemento(vetor*v,int n){
    if(v->tamanho_atual==v->capacidade) aumenta_vetor(v);
    v->dados[v->tamanho_atual]=n;
    v->tamanho_atual++;
    return;
}

void adiciona_ordenado(vetor*v,int n){
    if(v->tamanho_atual==v->capacidade) aumenta_vetor(v);
    int i;
    for(i=v->tamanho_atual-1; i>=0 && n < v->dados[i]; i--){
        v->dados[i+1]=v->dados[i];
    }
    v->dados[i+1]=n;
    v->tamanho_atual++;
    return;
}

int busca(vetor*v, int n){
    int i;
    for(i=0; i<v->tamanho_atual; i++){
        if(v->dados[i]==n) return i;
    }
    return -1;
}

int busca_ordenada(vetor*v,int inicio, int fim, int n){
    if(inicio > fim) return -1;
    int meio= inicio+(fim-inicio)/2;
    if(v->dados[meio] > n) return busca_ordenada(v,inicio,meio-1,n);
    if(v->dados[meio] < n) return busca_ordenada(v,meio+1,fim,n);
    return meio;
}

void remover_sem_ordenado(vetor*v,int n){
    if(v->tamanho_atual==0) return;
    v->dados[n]=v->dados[v->tamanho_atual-1];
    v->tamanho_atual--;
    if(v->tamanho_atual==v->capacidade/4) diminui_vetor(v);
    return;
}


void remover_ordenado(vetor*v,int n){
    if(v->tamanho_atual==0) return;
    for(int i=n; i< v->tamanho_atual-1;i++){
        v->dados[i]=v->dados[i+1];
    }
    v->tamanho_atual--;
    if(v->tamanho_atual <= v->capacidade/4) diminui_vetor(v);
    return;
}

void print_vetor(vetor*v){
    printf("[ ");
    int i;
    for(i=0; i<v->tamanho_atual; i++){
        printf("%d ", v->dados[i]);
    }
    puts("]");
}

