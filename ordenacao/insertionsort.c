#include <stdio.h>

// o algoritimo se baseia em um iserçao ordenada
// o vetor atras do meu elemento sempre vai estar ordenada
// entao eu so preciso achar o lugar do elemento no vetor de tras;

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
  return;
}

void insertionsortOt(int *v, int n) {
  int j;
  for (int i = 1; i < n; i++) {
    int t = v[i];
    for (j = i; j > 0; i++) {
      if (t < v[j - 1]) {
        v[j] = v[j - 1];
      }
    }
    v[j] = t;
  }
}

// a otimizaçao é para diminuir o numero de atribuiçoes
// eu guardo o elemento q eu vou comparar trocar
// eu vou so empurrando os elemento para frente, e quando a comparaçao
// der falsa vai ter um "buraco" em j e eu coloco a variavel ali

void insertionsort(int *v, int n) {
  for (int i = 1; i < n; i++) {
    for (int j = i; j >= 0; j--) {
      if (v[j] < v[j - 1]) {
        swap(&v[j], &v[j - 1]);
      }
    }
  }
}
