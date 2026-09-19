# Lista Simplesmente Encadeada em C

Este documento explica a implementação de uma **lista simplesmente encadeada** em C, detalhando a lógica de cada função, os ponteiros envolvidos, os casos base/limite e a complexidade de tempo e espaço (**Big O**).

---

## 1. Ideia da Lista Encadeada

Diferente de um vetor convencional ou dinâmico, os elementos de uma lista encadeada não ficam necessariamente todos juntos em um bloco contínuo na memória. Cada elemento fica separado em um bloco próprio chamado de **nó** (`no`), com os atributos:

- `val`: o valor que esse nó guarda;
- `next`: um ponteiro que armazena o endereço de memória do próximo nó da sequência.

A lista é acessada por um ponteiro inicial que aponta para o primeiro nó da lista,chamado de **cabeça da lista**. O último nó da lista é identificado por ter seu ponteiro `next` apontando para `NULL`.

Por exemplo:

```text
lista
  │
  ▼
┌───────┬──────┐    ┌───────┬──────┐    ┌───────┬──────┐
│ val:1 │ next ┼───>│ val:2 │ next ┼───>│ val:3 │ next ┼───> NULL
└───────┴──────┘    └───────┴──────┘    └───────┴──────┘
```

Se a lista estiver vazia:

```text
lista == NULL
```

---

# 2. Criação da Lista e Criação de Nó

```c
no* cria_lista(){
    return NULL;
}

no* cria_no(int val){
    no* n = calloc(1, sizeof(no));
    n->val = val;
    return n;
}
```

## Lógica

- **`cria_lista`**: Como uma lista encadeada sem nós é representada pela ausência de endereços e a lista é só um ponteiro para o primeiro nó, a função inicializadora simplesmente devolve `NULL`.
- **`cria_no`**: Aloca na memória heap o tamanho exato de um elemento usando a função sizeof que diz exatamente o tamanho de um tipo de dado (`sizeof(no)`). A função `calloc` zera todos os bytes alocados (garantindo que `next` comece como `NULL`) e atribui o parâmetro `val` ao campo correspondente.

### Estado após criação do nó:

```text
n
│
▼
┌─────────┬──────────┐
│ val: 42 │ next: 0x0│ (NULL)
└─────────┴──────────┘
```

## Complexidade

- **`cria_lista`**: Tempo $O(1)$, Espaço adicional $O(1)$.
- **`cria_no`**: Tempo $O(1)$, Espaço $O(1)$.

---

# 3. Adição de Elemento no Início

```c
no* adiciona_lista(no* lista, int val){
    no* n = cria_no(val);
    n->next = lista;
    return n;
}
```

## Lógica

A inserção ocorre no **início** (cabeça) da lista:

1. Cria um novo nó com o valor `val`.
2. Faz o campo `n->next` apontar para a cabeça atual da lista.
3. Retorna `n`, que passa a ser a nova cabeça, ja que a lista só guarda o primeiro nó.

### Exemplo

Inserindo `10` em uma lista que já contém `[20 -> 30]`:

```text
Passo 1: Criar novo nó
n -> [10 | NULL]

Passo 2: Ligar novo nó à cabeça antiga
n -> [10 | next] ───> [20 | next] ───> [30 | NULL]
                        ▲
                      lista

Passo 3: Retornar n como nova cabeça
```

## Complexidade

Como sempre é adicionad no início, não precisa percorrer a lista.

- **Tempo:** $O(1)$
- **Espaço adicional:** $O(1)$

---

# 4. Destruição da Lista com Ponteiro Duplo

```c
void destruir_lista(no** lista){
    no* p = *lista;
    no* aux;
    while(p != NULL){
        aux = p->next;
        free(p);
        p = aux;
    }
    *lista = NULL;
}
```

## Lógica

Usar um ponteiro auxiliar o proximo nó para não perder a referência quando desalocar o nó atual, e depois ir desalocando cada nó cade que o nó vire null, oque significa que chegou no final da lista e todos os nós foram desalocados.

A estratégia empregada utiliza dois ponteiros:
1. `p` aponta para o nó a ser desalocado no passo atual.
2. `aux` salva a referência `p->next`.
3. `free(p)` libera a memória do nó atual.
4. `p` avança recebendo `aux`.

NO final, para nao deixar um ponteiro apontando para o nada(*dangling pointers*), que não é uma boa prática, faz `*lista = NULL;`, por isso passar `ponteiro de ponteiro`.

## Complexidade

Se a lista possui `n` nós:

- **Tempo:** $O(n)$
- **Espaço adicional:** $O(1)$

---

# 5. Remoção de Nó

Existem duas maneiras de remover um nó: por **valor** e por **endereço do nó**. As duas tem a mesma ideia, só muda a forma de encontrar o elemento que vai ser removido.

```c
no* remove_lista_valor(no* lista, int val){
    no* p = lista;
    no* prev;
    while(p != NULL && p->val != val){
        prev = p;
        p = p->next;
    }
    if(p != NULL){ 
        if(p == lista){ 
            lista = lista->next;
        }
        else{
            prev->next = p->next; 
        }
        free(p);
    }
    return lista;
}
```

```c
no* remove_lista_no(no* lista, no* n){
    no* p = lista;
    no* prev;
    while(p != NULL && p != n){
        prev = p;
        p = p->next;
    }
    if(p != NULL){
        if(p == lista){
            lista = lista->next;
        }
        else{
            prev->next = p->next;
        }
        free(p);
    }
    return lista;
}
```

## Lógica

Para remover um nó da lista sem quebrar a conexão entra ponteiros:

1. O ponteiro `p` avança procurando o elemento alvo, enquanto `prev` vai sempre guardando a referência para o anterior.
2. Se quando acabar o loop `p != NULL`, o alvo foi encontrado:
   - **Caso 1 (Remoção da cabeça):** `p == lista`. Se o elemento que vai ser removido ta na cabeça, entao eu só preciso deslocar ele e retornar o proximo elemento como cabeça `lista->next`.
   - **Caso 2 (Remoção no meio ou fim):** É preciso  corrigir os ponteiros fazendo o anterior apontar para o proximo do nó que vai ser removido: `prev->next = p->next`.
3. O nó `p` é liberado com `free(p)`.

```text
Removendo nó com val: 20:

[10 | next] ───> [20 | next] ───> [30 | NULL]
     ▲                ▲
    prev              p

Ajuste do ponteiro:
prev->next = p->next:
[10 | next] ─────────────────────> [30 | NULL]
```

## Complexidade

- **Melhor caso (primeiro elemento):** $O(1)$
- **Pior caso (último elemento ou ausente):** $O(n)$

---

# 6. Busca Recursiva

```c
no* busca_recursiva(no* lista, int val){
    if(lista == NULL || lista->val == val){ return lista; }
    return busca_recursiva(lista->next, val);
}
```

## Lógica

Só tem duas  opções no algoritmo:
1. `lista == NULL`: chegou no fim da lista e não achou o valor (retorna `NULL`).
2. `lista->val == val`: o valor foi achado na lista (retorna o endereço do nó).

## Complexidade

- **Melhor caso:** $O(1)$(elemento está na cabeça)
- **Pior caso:** $O(n)$
- **Espaço de pilha:** $O(n)$ no pior caso, devido às chamadas recursivas.

---

# 7. Impressão (Iterativa e Recursiva)

```c
void imprime(no* lista){
    no* p = lista;
    while(p != NULL){
        printf("%d\n", p->val);
        p = p->next;
    }
}

void imprime_recursivo(no* lista){
    if(lista == NULL){ return; }
    printf("%d\n", lista->val);
    imprime_recursivo(lista->next);
}
```

## Lógica

- **Iterativa:** Percorre a lista com ponteiro auxiliar `p` até atingir `NULL`, imprimindo o valor de cada nó.
- **Recursiva:** Caso base `lista == NULL` significa que a lista é vazia ou chegou no final da lista. Imprime o dado da cabeça da sub-lista e chama a função com o próximo nó.

## Complexidade

- **Iterativa:** Tempo $O(n)$
- **Recursiva:** Tempo $O(n)$, Espaço de pilha $O(n)$.

---

# 8. Cópia da Lista (Iterativa e Recursiva)

```c
no* copiar_lista_recursivo(no* lista){
    if(lista == NULL){ return NULL; }
    no* copia = calloc(1, sizeof(no));
    copia->val = lista->val;
    copia->next = copiar_lista_recursivo(lista->next);
    return copia;
}

no* copia_lista(no* lista){
    if(lista == NULL){ return NULL; }
    no* copia = calloc(1, sizeof(no));
    no* save = copia;
    while(lista != NULL){
        copia->val = lista->val;
        if(lista->next != NULL){ 
            copia->next = calloc(1, sizeof(no));
            copia = copia->next;
        }
        lista = lista->next;
    }
    copia->next = NULL;
    return save;
}
```

## Lógica


- **Recursiva:** Cria o nó atual e conecta o `copia->next` ao retorno da cópia do restante da lista.
- **Iterativa:** Utiliza o ponteiro `save` para memorizar a cabeça da nova lista enquanto `copia` avança alocando novos nós. A checagem `if(lista->next != NULL)` impede a alocação de um nó extra ao término da lista.

## Complexidade

Para uma lista com $n$ elementos:

- **Versão Iterativa:** Tempo $O(n)$, Espaço $O(n)$ (novos nós alocados).
- **Versão Recursiva:** Tempo $O(n)$, Espaço $O(n)$ na heap + $O(n)$ na pilha de chamadas.

---

# 9. Inversão da Lista (Iterativa e Recursiva)

```c
no* inverte_lista(no* lista){
    no *atual, *ant, *invertida;
    invertida = NULL;
    atual = lista;
    while(atual != NULL){
        ant = atual;
        atual = ant->next;
        ant->next = invertida;
        invertida = ant;
    }
    return invertida;
}

no* inverte_lista_recursivo(no* lista){
    if(lista == NULL || lista->next == NULL) return lista;
    no* nova_cabeca = inverte_lista_recursivo(lista->next);
    lista->next->next = lista; 
    lista->next = NULL; 
    return nova_cabeca;
}
```

## Lógica Iterativa

Redireciona os ponteiros `next` em tempo real para o nó anterior:
1. `ant` isola o nó atual.
2. `atual` avança para o próximo.
3. `ant->next` aponta para a sublista já invertida (`invertida`).
4. `invertida` é atualizada para o nó recém-deslocado.

```text
Estado inicial:
[1] ───> [2] ───> [3] ───> NULL
invertida = NULL

Após 1ª iteração:
NULL <─── [1]          [2] ───> [3] ───> NULL
           ▲            ▲
       invertida      atual
```

## Lógica Recursiva

A inversão recursiva avança até o último nó (que será a `nova_cabeca`). Na volta das chamadas recursivas:

```text
lista: [A] ───> [B] ───> NULL
```

1. A linha `lista->next->next = lista;` inverte a ordem dos ponteiros `A->B` para `A<-B`, assim na volta das chamadas recursivas o ponteiro de todos os nós vai se invertendo.
2. A linha `lista->next = NULL;` remove a ligação original `A->B` para deixar só `A<-B` e para não formar ciclos (*loops* infinitos).

## Complexidade

- **Iterativa:** Tempo $O(n)$, Espaço adicional $O(1)$.
- **Recursiva:** Tempo $O(n)$, Espaço de pilha $O(n)$.

---

# 10. Concatenação de Listas

```c
no* concatenar_lista(no* lista1, no* lista2){
    if(lista1 == NULL) return lista2;
    no* p = lista1;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = lista2;
    return lista1;
}

no* concatenar_lista_recursivo(no* lista1, no* lista2){
    if(lista1 == NULL) return lista2;
    lista1->next = concatenar_lista(lista1->next, lista2);
    return lista1;
}
```

## Lógica

Une o final da `lista1` ao início da `lista2`.

1. Se `lista1` for vazia, a concatenação é a própria `lista2`.
2. Percorrer a `lista1` até o último elemento (onde `p->next == NULL`).
3. O ponteiro final passa a apontar para o primeiro nó de `lista2`.


## Complexidade

Depende do número de elementos da primeira lista (n):

- **Tempo:** $O(n)$
- **Espaço adicional:** $O(1)$ na iterativa; $O(n)$ na recursiva (pilha).

---

# 11. Resumo das Complexidades

| Operação | Tempo (Melhor) | Tempo (Pior) | Espaço Adicional | Tipo |
|---|---:|---:|---:|---|
| `cria_lista` | $O(1)$ | $O(1)$ | $O(1)$ | Direto |
| `cria_no` | $O(1)$ | $O(1)$ | $O(1)$ | Alocação |
| `adiciona_lista` | $O(1)$ | $O(1)$ | $O(1)$ | Inserção no início |
| `destruir_lista` | $O(n)$ | $O(n)$ | $O(1)$ | Liberação total |
| `remove_lista_valor` | $O(1)$ | $O(n)$ | $O(1)$ | Busca e religamento |
| `remove_lista_no` | $O(1)$ | $O(n)$ | $O(1)$ | Busca e religamento |
| `busca_recursiva` | $O(1)$ | $O(n)$ | $O(n)$ | Recursivo (pilha) |
| `imprime` | $O(n)$ | $O(n)$ | $O(1)$ | Iterativo |
| `imprime_recursivo` | $O(n)$ | $O(n)$ | $O(n)$ | Recursivo (pilha) |
| `copia_lista` | $O(n)$ | $O(n)$ | $O(n)$ | Deep copy iterativo |
| `copiar_lista_recursivo` | $O(n)$ | $O(n)$ | $O(n)$ | Deep copy recursivo |
| `inverte_lista` | $O(n)$ | $O(n)$ | $O(1)$ | Manipulação *in-place* |
| `inverte_lista_recursivo`| $O(n)$ | $O(n)$ | $O(n)$ | *In-place* via pilha |
| `concatenar_lista` | $O(1)$ | $O(n_1)$ | $O(1)$ | Ajuste de cauda |

---

# 12. Invariantes da Lista Simplesmente Encadeada

Durante toda a execução do programa, as seguintes propriedades devem ser mantidas:

1. **Condição de Término:** O último nó da cadeia deve conter `next == NULL`. A quebra desta regra cria listas circulares acidentais e loops infinitos.
2. **Integridade da Cabeça:** A referência para a cabeça não pode ser perdida,  podendo gerar vazamento de memória (*memory leak*).
3. **Casos de Ponteiro Nulo:** Funções que recebem listas devem sempre tratar `lista == NULL` como caso base antes de tentar desreferenciar membros (`lista->val` ou `lista->next`).