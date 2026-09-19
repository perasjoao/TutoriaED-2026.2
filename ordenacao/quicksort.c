#include <stdio.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int particiona(int *v, int inicio, int fim) {
  int pivo = v[inicio];
  int i = fim, j = fim;
  for (i = fim; i > inicio; i--) {
    if (v[i] < pivo) {
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
  return;
}
