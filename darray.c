#include "utils.c"
#include <stdio.h>
#include <stdlib.h>

// dynamic array
// Vector like implementation of arrays, but in C
// to initialize the vector, here darray,
// call the initDarray(), it returns an empty darr* type

// ---------- main logic -----------------------
typedef struct DArray {
  int *arr; // currentlty limiting to int, might change to void* later, TODO
  int size;
  int capacity;
} *darr;

// initializing the darray, an empty darray
darr initDArray() {
  darr d = (darr)malloc(sizeof(struct DArray));
  d->size = 0;
  d->capacity = 2;
  d->arr = (int *)malloc(sizeof(int) * d->capacity);
  return d;
}

// resizing function for the int array
// TODO: make it generic
void resize(darr d) {
  d->capacity *= 2;
  d->arr = (int *)realloc(d->arr, sizeof(int) * d->capacity);
}

// pushback function for the darray
// Time Complexity: O(1)*
void pb(darr d, int val) {
  d->size++;
  if (d->size > d->capacity)
    resize(d);
  d->arr[d->size - 1] = val;
}

// insert val at index i in darray arr
// if i goes out of bound, it is clipped at 0 and size
// Time Complexity: O(n)
void insert(darr arr, int val, int i) {
  if (i < 0)
    i = 0;
  if (i > arr->size)
    i = arr->size;
  arr->size++;
  if (arr->size > arr->capacity)
    resize(arr);
  for (int ind = arr->size - 1; ind > i; ind--) {
    arr->arr[ind] = arr->arr[ind - 1];
  }
  arr->arr[i] = val;
  return;
}

// Function to acces the value at index i in the darray arr
// make sure to follow 0 indexing
// ERROR: if index out of range then flushes out the error to stdout and return
// -1
// Time Complexity: O(1), due to inner implementation of pointers using hash map
int at(darr arr, unsigned int i) {
  if (i >= arr->size) {
    ERROR("Index out of range, Exitting...");
    fprintf(stderr, "Index: %d, Size: %d\n", i, arr->size);
    exit(1);
  }
  return arr->arr[i];
}

// find the val in darray arr
// return the index if found
// else return -1
// Time Complexity: O(n)
int find(darr arr, int val) {
  int n = arr->size;
  for (int i = 0; i < n; i++) {
    if (arr->arr[i] == val)
      return i;
  }
  return -1;
}

// deletion at index i from darray arr
// Time Complexity: O(n)
void deleteAt(darr arr, unsigned int i) {
  int n = arr->size; // defining the size of the array as n, cuz why not
  if (i >= n) {
    ERROR("Index out of range, Exitting...");
    exit(1);
  }
  for (int ind = i; ind < n - 1; ind++) {
    arr->arr[ind] = arr->arr[ind + 1];
  }
  arr->size--;
}

// delete the value val from darray arr
// warns the user if val not found in arr and does nothing
// Time Complexity: O(n)
void delete(darr arr, int val) {
  unsigned int ind = find(arr, val);
  if (ind == -1) {
    WARN("Value not found in the darray");
    return;
  }
  deleteAt(arr, ind);
}

// clearing the darray
// Time Complexity: O(1)
void clear(darr arr) { arr->size = 0; }

// adding two darrays
// concatenates the darrays
// returns a new arr = arr1 + arr2, + here means concatenates
// arr1 and arr2 remains intact
// Time Complexity: O(m+n)
darr add(darr arr1, darr arr2) {
  darr ndarr = initDArray(); // i have an idea to do this in O(min(m,n)), but
                             // SOLVED: not possible, might be another way to
                             // do? I might as well research on it
  for (int i = 0; i < arr1->size; i++) {
    pb(ndarr, arr1->arr[i]);
  }

  for (int i = 0; i < arr2->size; i++) {
    pb(ndarr, arr2->arr[i]);
  }

  return ndarr;
}

// ---------------- GENERIC FUNCTIONS -------------------

// A Function to print the dynamic array, done in O(n)
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

// int main() {
//   // main
//   darr arr;
//   arr = initDArray();
//   pr(arr);
//   pb(arr, 1);
//   pb(arr, 3);
//   pb(arr, 2);
//   pr(arr);
//   // at(arr, 3);
//   insert(arr, 69, 0);
//   pr(arr);
//   insert(arr, 69, 69);
//   pr(arr);
//   insert(arr, 420, 420);
//   pr(arr);
//   insert(arr, 33, 3);
//   pr(arr);
// }
