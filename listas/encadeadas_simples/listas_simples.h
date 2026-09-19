#include <stdlib.h>
#include <stdio.h>

typedef struct no{
    int val;
    struct no* next;
}no;

no*cria_lista();

no*cria_no(int val);

void destruir_lista(no**lista);

no*cria_no(int val);

no* adiciona_lista(no*lista,int val);

no*remove_lista_valor(no*lista,int val);

no*remove_todos(no*lista,int val);

no*remove_lista_no(no*lista,no* n);

no*busca_recursiva(no*lista,int val);

void imprime(no*lista);

void imprime_recursivo(no*lista);

no*copiar_lista_recursivo(no*lista);

no*copia_lista(no*lista);

no*inverte_lista_recursivo(no*lista);

no*concatenar_lista(no*lista1,no*lista2);

no*concatenar_lista_recursivo(no*lista1,no*lista2);


