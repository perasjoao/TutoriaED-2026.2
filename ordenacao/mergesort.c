#include <stdlib.h>

void merge(int*v, int inicio, int fim, int meio)
{
    int *aux=calloc((fim-inicio+1),sizeof(int));
    int i=inicio; int j=meio+1; int k=0;
    while(i<=meio && j<=fim){
        if(v[i] <= v[j]){
            aux[k++]=v[i++];
        }
        else{
            aux[k++]=v[j++];
        }
    }
    while(i<=meio){
        aux[k++]=v[i++];
    }
    while(j<=fim){
        aux[k++]=v[j++];
    }
    for(int i=inicio,k=0; i<=fim; i++,k++){
        v[i]=aux[k];
    }
    free(aux);
}

void mergesort(int*v, int inicio, int fim)
{
    if(inicio < fim){
        int meio = (fim+inicio)/2; // pode dar overflow, então pode usar inicio+(fim-inicio)/2
        mergesort(v,inicio,meio);
        mergesort(v,meio+1,fim);
        merge(v,inicio,fim,meio);
    }
}
