#include <stdbool.h>
#include <stdio.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
  return;
}

void bubllesort(int *v, int n) {
  bool trocou = true;
  for (int i = 0; i < n && trocou; i++) {
    trocou = false;
    for (int j = 0; j < n - 1 - i; j++) {
      if (v[i] < v[j]) {
        trocou = true;
        swap(&v[i], &v[j]);
      }
    }
  }
}

// se nao trocou o vetor ja esta ordenado
// eu a cada passagem sempre empurro o maior elemento para a ultima posiçao nao
// vista ainda
