#include "utils.c"
#include <stdio.h>
#include <stdlib.h>

// dynamic array
// Vector like implementation of arrays, but in C

// ---------- main logic -----------------------
typedef struct DArray {
  int *arr; // currentlty limiting to int, might change to void* later, TODO
  int size;
  int capacity;
} *darr;

// resizing function for the int array
// TODO: make it generic
void resize(darr d) {
  d->capacity *= 2;
  d->arr = (int *)realloc(d->arr, sizeof(int) * d->capacity);
}

// pushback function for the darray
void pb(darr d, int val) {
  d->size++;
  if (d->size > d->capacity)
    resize(d);
  d->arr[d->size - 1] = val;
}

// Function to acces the value at index i in the darray arr
// make sure to follow 0 indexing
// ERROR: if index out of range then flushes out the error to stdout and return
// -1
int at(darr arr, unsigned int i) {
  if (i >= arr->size) {
    ERROR("Index out of range");
    fprintf(stderr, "Index: %d, Size: %d\n", i, arr->size);
    return -1;
  }
  return arr->arr[i];
}

// initializing the darray, an empty darray
darr initDArray() {
  darr d = (darr)malloc(sizeof(struct DArray));
  d->size = 0;
  d->capacity = 2;
  d->arr = (int *)malloc(sizeof(int) * d->capacity);
  return d;
}

// ---------------- GENERIC FUNCTIONS -------------------

// A Function to print the dynamic array
void pr(darr d) {
  int n = d->size;
  printf("Array: { ");
  for (int i = 0; i < n; i++) {
    if (i == n - 1)
      printf("%d", d->arr[i]);
    else
      printf("%d, ", d->arr[i]);
  }
  printf(" }\n");
  return;
}

int main() {
  // main
  darr arr;
  arr = initDArray();
  pr(arr);
  pb(arr, 1);
  pb(arr, 3);
  pb(arr, 2);
  pr(arr);
  at(arr, 3);
  printf("%d\n", at(arr, 2));
}
