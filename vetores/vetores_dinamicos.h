#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int*dados;
    int tamanho_atual;
    int capacidade;
}vetor;

vetor*cria_vetor(int capacidade);

vetor*destruindo_com_retorno(vetor*v);

void aumenta_vetor(vetor*v);

void diminui_vetor(vetor*v);

void destruindo_vetor_referencia(vetor**vector);

void adiciona_elemento(vetor*v,int n);

void adiciona_ordenado(vetor*v,int n);

int busca(vetor*v, int n);

int busca_ordenada(vetor*v,int inicio,int fim, int n);

void remover_sem_ordenado(vetor*v,int n);

void remover_ordenado(vetor*v,int n);

void print_vetor(vetor*v);


