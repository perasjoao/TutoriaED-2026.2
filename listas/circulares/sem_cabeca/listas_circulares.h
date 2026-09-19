#include <stdlib.h>

typedef struct no{
    struct no*next;
    int val;
}no;

//a cabeça sempre sera o ultimo nó

no* cria_no(int val);

no* cria_lista();

no*add_circular(int val,no*lista);

no*remove_circular(no*lista,no*n);