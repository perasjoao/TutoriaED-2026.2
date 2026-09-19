#include <stdlib.h>

typedef struct no{
    int val;
    struct no*next;
}no;

//a cabeça sempre sera um no que nunca será alterado

no*cria_no(int val);

no*cria_lista();

no*adiciona_circular(no*lista,int val);

no*remove_circular(no*lista,no* n);