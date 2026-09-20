#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
    char*str;
    int chegada;
    struct node*next;
}node;

typedef struct fila{
    node*inicio;
    node*fim;
}fila;

node*create_node(char str[], int chegada){
    node*n=calloc(1,sizeof(node));
    n->chegada=chegada;
    n->str=strdup(str); // pega a string original duplica ela na heap e retorna o ponteiro
    //impede a string se perder dpois da funçao
    return n;
}

fila*create_fila(){
    fila*f=calloc(1,sizeof(fila));
    return f;
}

bool fila_vazia(fila*f){
    if(f->inicio==NULL){
        return true;
    }
    return false;
}

void enqueue(fila*f,char str[], int chegada){
    node*n=create_node(str, chegada);

    if(fila_vazia(f)){
        f->inicio=n;
        f->fim=n;
        return;
    }
    else{
        f->fim->next=n;
        f->fim=n;
    }
}

int dequeue(fila*f){
    if(fila_vazia(f)){
        return -137;
    }
    int save=f->inicio->chegada;
    node*remove=f->inicio;
    f->inicio=f->inicio->next;
    free(remove);
    if(f->inicio==NULL){
        f->fim=NULL;
    }
    return save;
}

fila* le_fila(){
    fila*banco=create_fila();
    int i=1;
        while(1){
            char str[100];
            scanf("%s", str);
            getchar();
            if(!strcmp(str,"0")){
                break;
            }
            enqueue(banco,str, i);
            i++;
        }
        return banco;
}

void print_fila(fila*f){
    node*p=f->inicio;
    while(p!=NULL){
        printf("%s -> ", p->str);
        p=p->next;
    }
    puts("NULL");
}

void ajeita_fila(fila*f){
    fila*idosos=create_fila();
    fila*geral=create_fila();
    node*p=f->inicio;
    int cont=0;
        while(p!=NULL){
            if(!strcmp(p->str,"idoso")){
                enqueue(idosos,p->str,p->chegada);
            }
            else{
                enqueue(geral,p->str,p->chegada);
            }
            p=p->next;
        }
        while(!fila_vazia(idosos)){
            int ordem=dequeue(idosos);
            printf("%d ", ordem);
            cont++;
            if(cont==2){
                cont=0;
                while(cont!=2 && !fila_vazia(geral)){
                    ordem=dequeue(geral);
                    printf("%d ", ordem);
                    cont++;
                }
            }
        }
        while(!fila_vazia(geral)){
            int ordem = dequeue(geral);
            printf("%d ", ordem);
        }
}



int main(){
fila*banco=le_fila(7);
    ajeita_fila(banco);
    return 0;
}