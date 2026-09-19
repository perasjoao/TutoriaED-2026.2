# Vetor Dinâmico em C
Explicação da implementação do vetor dinamico com porque tomar as decisoes e a notação Big(O) de cada

## 1. Ideia do vetor dinâmico

Um vetor dinâmico funciona de forma parecida com um vetor comum, mas permite aumentar ou diminuir sua capacidade durante a execução.

A estrutura do vetor dinâmico:

- `dados`: endereço do bloco de memória que armazena os elementos;
- `capacidade`: quantidade de posições alocadas;
- `tamanho_atual`: quantidade de elementos realmente armazenados.

## Lógica

Primeiro é alocada memória para a própria estrutura `vetor`.

Depois é alocado o vetor de inteiros(que é somente um ponteiro para o bloco de inteiros):

```c
v->dados = calloc(capacidade, sizeof(int));
```

Como o vetor começa vazio:

```c
v->tamanho_atual = 0;
```

A capacidade vai representar quatos elementos eu posso guardar em v->dados.

### Estado inicial

Se for criado um vetor com capacidade `5`:

```text
capacidade = 5
tamanho_atual = 0

[ ][ ][ ][ ][ ]
```

## Complexidade

A criação precisa alocar espaço para `capacidade` elementos.

**Tempo:** `O(1) ou O(capacidade)` que é o bigO do proprio malloc/calloc

**Espaço:** `O(capacidade)` já que é alocado *capicidade*n espaços para inteiros na memoria

---

# 3. Destruição retornando `NULL`

```c
vetor* destruindo_com_retorno(vetor *v){
    free(v->dados);
    v->capacidade = 0;
    v->tamanho_atual = 0;
    free(v);
    return NULL;
}
```

## Lógica

A estrutura possui duas regiões de memória alocadas:

```text
v
│
└──> dados
```

Primeiro é liberado:

```c
free(v->dados);
```

Depois a própria estrutura:

```c
free(v);
```

A função retorna `NULL`, permitindo fazer:

```c
v = destruindo_com_retorno(v);
```

Assim, depois da destruição:

```text
v == NULL
```

Isso é útil para evitar que a variável continue apontando para uma região de memória que já foi liberada.

## Complexidade

O `free` das duas regiões é considerado `O(1)` em termos da operação da estrutura.

**Tempo:** `O(1)`

**Espaço adicional:** `O(1)`

---

# 4. Aumentando a capacidade

```c
void aumenta_vetor(vetor *v){
    int *save = v->dados;

    v->dados = calloc(v->capacidade * 2, sizeof(int));

    for(int i = 0; i < v->capacidade; i++)
        v->dados[i] = save[i];

    v->capacidade *= 2;
    free(save);
}
```

## Lógica

Quando o vetor está cheio:

```text
tamanho_atual == capacidade
```

não existe espaço para inserir outro elemento.

A solução é criar um novo bloco com o dobro da capacidade.

### Exemplo

Antes:

```text
capacidade = 4
tamanho_atual = 4

[10][20][30][40]
```

Depois de aumentar:

```text
capacidade = 8
tamanho_atual = 4

[10][20][30][40][ ][ ][ ][ ]
```

Para fazer isso:

1. guarda o endereço antigo em `save`;
2. aloca um novo vetor com o dobro da capacidade;
3. copia os elementos antigos;
4. atualiza a capacidade;
5. libera o vetor antigo.

## Por que dobrar?

A ideia de multiplicar a capacidade por `2` evita precisar realocar memória a cada inserção.

Se a capacidade fosse aumentada somente em `1`, várias inserções poderiam provocar muitas realocações.

Com crescimento geométrico:

```text
1 → 2 → 4 → 8 → 16 → 32 → ...
```

as inserções possuem custo amortizado baixo.

## Complexidade

A função precisa copiar todos os elementos que estavam no vetor.

Se o tamanho atual é `n`:

**Tempo:** `O(n)`

**Espaço temporário:** `O(n)`

---

# 5. Diminuindo a capacidade

```c
void diminui_vetor(vetor *v){
    int *save = v->dados;

    v->dados = calloc(v->capacidade / 4, sizeof(int));

    for(int i = 0; i < v->tamanho_atual; i++)
        v->dados[i] = save[i];

    v->capacidade /= 4;
    free(save);
}
```

## Lógica

A ideia é liberar espaço quando o vetor estiver pouco utilizado.

No código, a capacidade é reduzida para:

```text
capacidade / 4
```

Por exemplo:

```text
capacidade = 8
tamanho_atual = 2
```

A nova capacidade será:

```text
8 / 4 = 2
```

Então:

```text
antes:

[10][20][ ][ ][ ][ ][ ][ ]
              capacidade = 8

depois:

[10][20]
capacidade = 2
```

A função copia somente os elementos que fazem parte do vetor:

```c
for(int i = 0; i < v->tamanho_atual; i++)
```

## Porque dividir o tamanho por 4 e não por 2?

Se fosse por 2, imagine um cenario que:
- Dobrar a capacidade quando o vetor estiver cheio ($1/1$).
- Reduzir a capacidade para a metade quando o vetor estiver com metade da ocupação ($1/2$)[cite: 2].
## Pior caso:
1. O vetor tem capacidade N e está totalmente cheio com N elementos.
2. **Inserção:** Ao adicionar 1 elemento, o vetor precisa de alocar espaço para 2N elementos e copiar os dados antigos, então O(N) e o vetor agora tem N+1.
3. **Remoção:** Mas depois, você remove 1 elemento, então o vetor fica agora com N elementos para uma capacidade de 2N, entao ele está **$1/2$ cheio**[cite: 2].
4. Então pelo algoritimo, o vetor vai reduiz para a capacidade N, copiando novamente os elementos, entao O(N).
5. Entao, em um cenario que eu fico removendo e adicionando somente 1 elemente repitidamente, eu irei fazer inumeras ações que custam O(N), oque iria contra eficiência do código.
6. A ideia de dividir por 4 vem justamente para evitar esse problema.

## Condição importante

A função deve ser chamada somente quando a nova capacidade continuar sendo suficiente para armazenar os elementos.

A invariável deve continuar válida:

```text
tamanho_atual <= capacidade
```

Por isso, no uso atual, ela é chamada pelas funções de remoção quando o vetor atinge o limite definido para redução.

## Complexidade

É necessário copiar os elementos existentes.

Se existem `n` elementos:

**Tempo:** `O(n)` e custo amortizado(siginifica o custo médio de cada operação) é `O(1)`, porque todas as operações de adicionar são `O(1)`, menos quando o vetor está cheio que é `O(n)`, então o custo de operações médio é `O(1)`.

**Espaço temporário:** `O(n)`

---

# 6. Destruição usando ponteiro para ponteiro

```c
void destruindo_vetor_referencia(vetor **vector){
    vetor *v = *vector;

    free(v->dados);
    free(*vector);

    *vector = NULL;
}
```

## Lógica

Aqui é utilizado um `vetor**`.

Se temos:

```c
vetor *v;
```

e queremos modificar a própria variável `v` dentro da função, precisamos passar seu endereço:

```c
destruindo_vetor_referencia(&v);
```

Assim:

```text
v
↓
[vetor]
```

A função libera a memória e faz:

```c
*vector = NULL;
```

Portanto, a variável original também passa a apontar para `NULL`.

## Complexidade

Não é necessário percorrer os elementos.

**Tempo:** `O(1)`

**Espaço adicional:** `O(1)`

---

# 7. Adicionando um elemento

```c
void adiciona_elemento(vetor *v, int n){
    if(v->tamanho_atual == v->capacidade)
        aumenta_vetor(v);

    v->dados[v->tamanho_atual] = n;
    v->tamanho_atual++;
}
```

## Lógica

Primeiro verifica se o vetor está cheio:

```c
v->tamanho_atual == v->capacidade
```

Se estiver, aumenta a capacidade.

Depois coloca o elemento na primeira posição livre:

```c
v->dados[v->tamanho_atual] = n;
```

Finalmente:

```c
v->tamanho_atual++;
```

### Exemplo

```text
antes:

[10][20][30][ ][ ]
             ↑
        tamanho = 3
```

Adicionando `40`:

```text
[10][20][30][40][ ]
                  ↑
             tamanho = 4
```

## Complexidade

Na maioria das inserções não é necessário mover elementos.

**Caso normal:** `O(1)`

Quando ocorre aumento da capacidade:

**Pior caso:** `O(n)`

Considerando muitas inserções ao longo do tempo, o custo da realocação é amortizado, fazendo a inserção ter custo amortizado:

**Custo amortizado:** `O(1)`

---

# 8. Adicionando um elemento mantendo a ordem

```c
void adiciona_ordenado(vetor *v, int n){
    if(v->tamanho_atual == v->capacidade)
        aumenta_vetor(v);

    int i;

    for(i = v->tamanho_atual - 1;
        i >= 0 && n < v->dados[i];
        i--){

        v->dados[i + 1] = v->dados[i];
    }

    v->dados[i + 1] = n;
    v->tamanho_atual++;
}
```

## Lógica

Essa função pressupõe que o vetor já está ordenado em ordem crescente.

Exemplo:

```text
[2][5][8][10]
```

Queremos inserir:

```text
6
```

Primeiro comparamos `6` com `10`.

Como:

```text
6 < 10
```

movemos `10` para a direita:

```text
[2][5][8][10][10]
```

Depois comparamos com `8`:

```text
6 < 8
```

Movemos `8`:

```text
[2][5][8][8][10]
```

Agora `6` não é menor que `5`.

Então inserimos:

```text
[2][5][6][8][10]
```

Então a ideia é sair "empurrando" os elementos para frente ate achar um menor, assim ali vai ter um "espaço livre" e vai ser a posição correta onde o elemento tem que ser inserido.

## Complexidade

No melhor caso, o elemento já deve ficar no final e praticamente nenhum elemento precisa ser deslocado.

**Melhor caso:** `O(1)`

No pior caso, o elemento deve ser colocado no começo e todos os elementos precisam ser deslocados.

**Pior caso:** `O(n)`

---

# 9. Busca linear

```c
int busca(vetor *v, int n){
    int i;
    for(i=0; i<v->tamanho_atual; i++){
        if(v->dados[i]==n) return i;
    }
    return -1;
}
```

A ideia da busca linear é verificar os elementos um por um.


A lógica da busca é:

```text
[10][20][30][40][50]
 ↑
não é 40

[10][20][30][40][50]
     ↑
não é 40

[10][20][30][40][50]
         ↑
não é 40

[10][20][30][40][50]
             ↑
encontrou
```

A função deve retornar o índice do elemento quando ele for encontrado e `-1` caso não seja encontrado.

## Complexidade

### Melhor caso

O elemento está na primeira posição:

**O(1)**

### Pior caso

O elemento está na última posição ou não existe:

**O(n)**

---

# 10. Busca binária

```c
int busca_ordenada(vetor *v, int inicio, int fim, int n){
    if(inicio > fim)
        return -1;

    int meio = inicio + (fim - inicio) / 2;

    if(v->dados[meio] > n)
        return busca_ordenada(v, inicio, meio - 1, n);

    if(v->dados[meio] < n)
        return busca_ordenada(v, meio + 1, fim, n);

    return meio;
}
```

## Pré-condição

O vetor precisa estar ordenado.

Por exemplo:

```text
[2][5][8][12][15][20][30]
```

Queremos procurar `15`.

Calculamos o meio:

```text
[2][5][8][12][15][20][30]
          ↑
        meio
```

Como `12 < 15`, sabemos que `15` só pode estar na metade direita.

Então descartamos a metade esquerda.

```text
[15][20][30]
 ↑
```

Encontramos `15`.

## Por que é mais rápida?

A busca binária descarta aproximadamente metade das possibilidades a cada chamada:

```text
n
↓
n/2
↓
n/4
↓
n/8
↓
...
```

Por isso sua complexidade é logarítmica.

## Complexidade

**Melhor caso:** `O(1)`

**Pior caso:** `O(log n)`

**Espaço da recursão:** `O(log n)`

---

# 11. Remoção sem preservar a ordem

```c
void remover_sem_ordenado(vetor *v, int n){
    if(v->tamanho_atual == 0)
        return;

    if(v->tamanho_atual == v->capacidade / 4)
        diminui_vetor(v);

    v->dados[n] = v->dados[v->tamanho_atual - 1];
    v->tamanho_atual--;
}
```

## Lógica

Nesse tipo de remoção, não queremos gastar tempo deslocando todos os elementos.

Suponha:

```text
[10][20][30][40][50]
```

Queremos remover o índice `1`:

```text
20
```

Pegamos o último elemento:

```text
50
```

e colocamos na posição removida:

```text
[10][50][30][40][50]
```

Depois diminuímos:

```text
tamanho_atual--
```

O vetor passa logicamente a ser:

```text
[10][50][30][40]
```

A ordem original foi perdida, mas não foi necessário deslocar vários elementos.

## Complexidade

A troca com o último elemento é direta.

**Tempo:** `O(1)`

Caso ocorra `diminui_vetor`, haverá a cópia dos elementos:

**Pior caso:** `O(n)`

---

# 12. Remoção mantendo a ordem

```c
void remover_ordenado(vetor *v, int n){
    if(v->tamanho_atual == 0)
        return;

    if(v->tamanho_atual == v->capacidade / 4)
        diminui_vetor(v);

    for(int i = n; i < v->tamanho_atual - 1; i++){
        v->dados[i] = v->dados[i + 1];
    }

    v->tamanho_atual--;
}
```

## Lógica

Aqui a ordem precisa ser preservada.

Considere:

```text
[10][20][30][40][50]
```

Removendo o índice `2`:

```text
30
```

Os elementos seguintes precisam andar uma posição para a esquerda:

```text
40 → posição 2
50 → posição 3
```

Resultado:

```text
[10][20][40][50]
```

O `for` realiza exatamente esses deslocamentos.

## Complexidade

### Melhor caso

Se o elemento removido estiver no final, praticamente nenhum elemento precisa ser deslocado.

**O(1)**

### Pior caso

Se o elemento estiver no início, todos os outros elementos precisam ser deslocados.

**O(n)**

Se também houver redução da capacidade:

**Pior caso:** `O(n)`

---

# 13. Resumo das complexidades

| Operação | Melhor caso | Pior caso | Observação |
|---|---:|---:|---|
| `cria_vetor` | `O(n)` | `O(n)` | Aloca `n` posições |
| `destruindo_com_retorno` | `O(1)` | `O(1)` | Libera memória |
| `aumenta_vetor` | `O(n)` | `O(n)` | Precisa copiar elementos |
| `diminui_vetor` | `O(n)` | `O(n)` | Precisa copiar elementos |
| `destruindo_vetor_referencia` | `O(1)` | `O(1)` | Libera memória |
| `adiciona_elemento` | `O(1)` | `O(n)` | `O(1)` amortizado |
| `adiciona_ordenado` | `O(1)` | `O(n)` | Pode deslocar elementos |
| `busca` | `O(1)` | `O(n)` | Busca linear |
| `busca_ordenada` | `O(1)` | `O(log n)` | Busca binária |
| `remover_sem_ordenado` | `O(1)` | `O(n)` | `O(n)` se houver redução |
| `remover_ordenado` | `O(1)` | `O(n)` | Pode deslocar elementos |

