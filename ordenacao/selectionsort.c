#include <stdio.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
  return;
}

void selectionsort(int *v, int n) {
  int min = 0;
  for (int i = 0; i < n; i++) {
    min = i;
    for (int j = i + 1; j < n; j++) {
      if (v[j] < min) {
        min = v[j];
      }
    }
    swap(&v[i], &min);
  }
}
