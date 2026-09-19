# Algoritmos de Ordenação em C

Este documento explica a implementação de cinco algoritmos clássicos de ordenação em C (**Bubble Sort**, **Insertion Sort**, **Selection Sort**, **Quick Sort** e **Merge Sort**), detalhando a lógica de cada função, ilustrações do funcionamento, invariantes de ordenação e análise de complexidade de tempo e espaço (**Big O**).

---

## 1. Visão Geral dos Algoritmos

A tarefa de ordenação consiste em rearranjar os elementos de um vetor $v$ de tamanho $n$ de forma que:

```text
v[0] <= v[1] <= v[2] <= ... <= v[n - 1]
```

Os algoritmos abordados dividem-se em duas categorias principais:

1. **Algoritmos Elementares / Quadráticos ($O(n^2)$):**
   - *Bubble Sort*: compara e troca vizinhos adjacentes.
   - *Insertion Sort*: constrói progressivamente uma sublista ordenada à esquerda.
   - *Selection Sort*: seleciona iterativamente o menor elemento restante e o posiciona.
2. **Algoritmos por Divisão e Conquista ($O(n \log n)$):**
   - *Quick Sort*: particiona o vetor ao redor de um elemento pivô.
   - *Merge Sort*: divide o vetor ao meio recursivamente e intercala as partes ordenadas.

---

## 2. Função Auxiliar: Troca (`swap`)

Todos os algoritmos baseados em troca direta utilizam uma função auxiliar para permutar o conteúdo de dois endereços de memória.

```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

### Lógica

Para trocar dois valores passados por referência:

1. Salva o valor apontado por `a` em uma variável temporária `temp`;
2. Sobrescreve o valor em `*a` com o valor de `*b`;
3. Atribui o valor guardado em `temp` para `*b`.

### Complexidade

- **Tempo:** $O(1)$
- **Espaço adicional:** $O(1)$

---

## 3. Bubble Sort (Ordenação por Bolha)

```c
void bubblesort(int *v, int n) {
    bool trocou = true;
    for (int i = 0; i < n && trocou; i++) {
        trocou = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                trocou = true;
                swap(&v[j], &v[j + 1]);
            }
        }
    }
}
```

> **Observação técnica sobre a implementação padrão:** O Bubble Sort clássico compara pares adjacentes `v[j]` e `v[j + 1]`. Se o elemento da esquerda for maior que o da direita, eles são trocados, fazendo com que o maior elemento "flutue" até a posição final $n - 1 - i$. A variável booleana `trocou` permite interromper a execução prematuramente caso nenhuma troca ocorra em uma passada completa.

### Exemplo

Considere o vetor inicial:

```text
[5][3][8][4][2]
```

**1ª Passada ($i = 0$):**

```text
compara 5 e 3 -> troca -> [3][5][8][4][2]
compara 5 e 8 -> mantém -> [3][5][8][4][2]
compara 8 e 4 -> troca -> [3][5][4][8][2]
compara 8 e 2 -> troca -> [3][5][4][2][8]   (maior elemento 8 fixado no fim)
```

**2ª Passada ($i = 1$):**

```text
compara 3 e 5 -> mantém -> [3][5][4][2][8]
compara 5 e 4 -> troca  -> [3][4][5][2][8]
compara 5 e 2 -> troca  -> [3][4][2][5][8]   (segundo maior 5 fixado)
```

### Complexidade

- **Melhor caso:** $O(n)$ (quando o vetor já está ordenado e o flag `trocou` encerra no primeiro laço).
- **Pior caso:** $O(n^2)$ (vetor em ordem decrescente).
- **Caso médio:** $O(n^2)$
- **Espaço adicional:** $O(1)$

---

## 4. Insertion Sort (Ordenação por Inserção)

### 4.1 Versão Tradicional com `swap`

```c
void insertionsort(int *v, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (v[j] < v[j - 1]) {
                swap(&v[j], &v[j - 1]);
            } else {
                break;
            }
        }
    }
}
```

### Lógica

O algoritmo funciona de maneira paraceida com organizar cartas na mão:

1. Sempre assume que todo subvetor atrás do elemento atual ja esta ordenado;
2. Como todo o subvetor atrás ja está ordenado, so precisamos achar o local no subvetor do elemento atual e colocar ele lá;
3. Enquanto o elemento for menor que o anterior, ele é trocado de posição até encontrar seu local correto.

---

### 4.2 Versão Otimizada por Deslocamento (`insertionsortOt`)

Em vez de realizar 3 atribuições a cada passo via `swap`, a versão otimizada guarda o elemento a ser inserido e desloca os elementos maiores uma casa para a direita.

```c
void insertionsortOt(int *v, int n) {
    int j;
    for (int i = 1; i < n; i++) {
        int t = v[i];
        for (j = i; j > 0 && t < v[j - 1]; j--) {
            v[j] = v[j - 1];
        }
        v[j] = t;
    }
}
```

> **Atenção ao loop interno:** Na versão canônica, o laço decrementa `j` (`j--`) enquanto `j > 0` e `t < v[j - 1]`.

### Exemplo de Deslocamento

Vetor com sublista ordenada à esquerda:

```text
[2][5][8][3]      (chave t = 3, comparando a partir do 8)
```

1. Compara $3 < 8$: desloca $8$ para a direita:
   ```text
   [2][5][8][8]
   ```
2. Compara $3 < 5$: desloca $5$ para a direita:
   ```text
   [2][5][5][8]
   ```
3. Compara $3 < 2$: condição falsa. O "buraco" está no índice correspondente:
   ```text
   [2][3][5][8]
   ```

### Complexidade

- **Melhor caso:** $O(n)$ (vetor já ordenado; apenas 1 comparação por elemento e nenhum deslocamento).
- **Pior caso:** $O(n^2)$ (vetor invertido; cada elemento percorre toda a sublista).
- **Caso médio:** $O(n^2)$
- **Espaço adicional:** $O(1)$

---

## 5. Selection Sort (Ordenação por Seleção)

```c
void selectionsort(int *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&v[i], &v[min_idx]);
        }
    }
}
```

> **Nota sobre o índice mínimo:** O algoritmo busca o **índice** do menor elemento (`min_idx`) na faixa `i` até `n - 1`. Ao final da busca, executa-se apenas uma troca entre `v[i]` e `v[min_idx]`.

### Exemplo

Dado o vetor:

```text
[29][10][14][37][13]
```

**Iteração 1 ($i = 0$):**
- Menor elemento entre índices $0$ e $4$: `10` (no índice 1).
- Troca `v[0]` com `v[1]`:
```text
[10] | [29][14][37][13]
```

**Iteração 2 ($i = 1$):**
- Menor elemento entre índices $1$ e $4$: `13` (no índice 4).
- Troca `v[1]` com `v[4]`:
```text
[10][13] | [14][37][29]
```

### Complexidade

O Selection Sort sempre percorre todos os pares restantes, independentemente do estado inicial do vetor.

- **Melhor caso:** $O(n^2)$
- **Pior caso:** $O(n^2)$
- **Caso médio:** $O(n^2)$
- **Espaço adicional:** $O(1)$
- **Vantagem:** Realiza no máximo $n - 1$ operações de escrita (`swap`), útil quando o custo de escrita na memória é muito elevado.

---

## 6. Quick Sort

O Quick Sort baseia-se na estratégia de **Divisão e Conquista**. Ele escolhe um elemento como **pivô** e rearranja o vetor de forma que todos os elementos menores fiquem de um lado e os maiores do outro, assim no final de cada passo um elemento vai estar na posição certa já(o elemento do meio).

```c
int particiona(int *v, int inicio, int fim) {
    int pivo = v[inicio];
    int j = fim;

    for (int i = fim; i > inicio; i--) {
        if (v[i] > pivo) {
            swap(&v[i], &v[j]);
            j--;
        }
    }
    swap(&v[inicio], &v[j]);
    return j;
}

void quicksort(int *v, int inicio, int fim) {
    if (inicio < fim) {
        int meio = particiona(v, inicio, fim);
        quicksort(v, inicio, meio - 1);
        quicksort(v, meio + 1, fim);
    }
}
```

### Esquema de Particionamento

O particionamento coloca o elemento pivô em sua posição final exata (`j`), garantindo que:

```text
v[k] <= pivo   para todo   inicio <= k < j
v[k] >= pivo   para todo   j < k <= fim
```

```text
[ Subvetor <= Pivô ]  [ PIVÔ ]  [ Subvetor >= Pivô ]
 inicio ... j - 1         j        j + 1 ... fim
```

Depois de posicionar o pivô, o algoritmo chama `quicksort` recursivamente para a metade esquerda e para a metade direita, entao em cada chama recursiva eu posiciono um elemento e no final quando eu chegar em um subvetor com 1 elemento ou um com 0 elementos, quer dizer que ele ja esta ordenado e todas as chamadas recursivas acima dele também.

### Complexidade

- **Melhor caso:** $O(n \log n)$ (as partições dividem o vetor em metades de tamanhos próximos).
- **Caso médio:** $O(n \log n)$
- **Pior caso:** $O(n^2)$ (ocorre quando o pivô escolhido é repetidamente o menor ou maior elemento, por exemplo ao escolher o primeiro elemento em um vetor já ordenado).
- **Espaço da pilha de recursão:**
  - Melhor caso: $O(\log n)$
  - Pior caso: $O(n)$

---

## 7. Merge Sort

O Merge Sort também utiliza **Divisão e Conquista**, dividindo recursivamente o vetor ao meio até subvetores unitários e depois intercalando-os em ordem, basicamente ordenando os subvetores entre si.

```c
void merge(int *v, int inicio, int fim, int meio) {
    int tamanho = fim - inicio + 1;
    int *aux = calloc(tamanho, sizeof(int));

    int i = inicio;
    int j = meio + 1;
    int k = 0;

    while (i <= meio && j <= fim) {
        if (v[i] <= v[j]) {
            aux[k++] = v[i++];
        } else {
            aux[k++] = v[j++];
        }
    }

    while (i <= meio) {
        aux[k++] = v[i++];
    }

    while (j <= fim) {
        aux[k++] = v[j++];
    }

    for (i = inicio, k = 0; i <= fim; i++, k++) {
        v[i] = aux[k];
    }

    free(aux);
}

void mergesort(int *v, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergesort(v, inicio, meio);
        mergesort(v, meio + 1, fim);
        merge(v, inicio, fim, meio);
    }
}
```

### Funcionamento da Intercalação (`merge`)

Suponha duas metades já ordenadas:

```text
Metade 1 (i): [2][6][9]     Metade 2 (j): [1][5][8]
```

1. Compara `2` e `1`: menor é `1` $\rightarrow$ `aux = [1]`
2. Compara `2` e `5`: menor é `2` $\rightarrow$ `aux = [1][2]`
3. Compara `6` e `5`: menor é `5` $\rightarrow$ `aux = [1][2][5]`
4. Compara `6` e `8`: menor é `6` $\rightarrow$ `aux = [1][2][5][6]`
5. Compara `9` e `8`: menor é `8` $\rightarrow$ `aux = [1][2][5][6][8]`
6. Resta `9`: copiado diretamente $\rightarrow$ `aux = [1][2][5][6][8][9]`
7. O vetor auxiliar é copiado de volta para `v[inicio ... fim]`.

### Prevenção de Overflow Aritmético

O cálculo do ponto médio:

```c
int meio = inicio + (fim - inicio) / 2;
```

é preferível a `(inicio + fim) / 2` porque evita estouro de capacidade de inteiros (`integer overflow`) quando `inicio + fim` ultrapassa o valor máximo de `int`.

### Complexidade

Diferente do Quick Sort, o Merge Sort divide rigorosamente o vetor ao meio em todas as etapas:

- **Melhor caso:** $O(n \log n)$
- **Pior caso:** $O(n \log n)$
- **Caso médio:** $O(n \log n)$
- **Espaço adicional:** $O(n)$ (necessita alocar o vetor auxiliar temporário).

---

## 8. Resumo Comparativo das Complexidades

| Algoritmo | Melhor Caso | Caso Médio | Pior Caso | Espaço Adicional | Estabilidade |
|---|---:|---:|---:|---:|:---:|
| **Bubble Sort** | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Estável |
| **Insertion Sort** | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Estável |
| **Selection Sort** | $O(n^2)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Não Estável |
| **Quick Sort** | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$ | $O(\log n)$ | Não Estável |
| **Merge Sort** | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ | Estável |

> **Conceito de Estabilidade:** Um algoritmo de ordenação é considerado **estável** se ele preserva a ordem relativa de elementos que possuem chaves iguais.

---

## 9. Quando Usar Cada Algoritmo?

1. **Insertion Sort:**
   - Excelente para vetores pequenos (frequentemente usado em bibliotecas padrão como caso base de algoritmos híbridos como Timsort e Introsort).
   - Ideal quando o vetor já está quase todo ordenado.

2. **Bubble Sort / Selection Sort:**
   - Possuem finalidade predominantemente didática.
   - O Selection Sort pode ter utilidade pontual quando a escrita na memória for excessivamente cara (mínimo de trocas).

3. **Quick Sort:**
   - É geralmente o algoritmo mais rápido na prática para propósito geral em memória principal, devido à excelente localidade de referência para o cache da CPU e baixo overhead de memória ($O(\log n)$).

4. **Merge Sort:**
   - Escolha recomendada quando se exige garantia estrita de tempo $O(n \log n)$ em todos os cenários.
   - Muito utilizado na ordenação de listas encadeadas (onde a alocação de vetor contíguo extra não é obrigatória) e ordenação externa (arquivos em disco).