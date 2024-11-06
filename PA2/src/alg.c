#include "alg.h"
#include "desemp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

typedef struct sortperf{
  int cmp;
  int move;
  int calls;
} sortperf_t;


void selectionSort(int arr[], int l, int r, sortperf_t * s){
  int i, j, Min;
  inccalls(s, 1);
  for (i = 0; i < n - 1; i++){ 
    Min = i;
    for (j = i + 1 ; j < n; j++){
      inccmp(s, 1);
      if (arr[j].chave < arr[Min].chave) 
        Min = j;
    }
    incmove(s, 3);
    Troca(arr[i], arr[Min]);
  }
}

void recursiveSelectionSort(int arr[], int l, int r, sortperf_t * s)
{
    // find the minimum element in the unsorted subarray `[i…n-1]`
    // and swap it with `arr[i]`
    int min = l;
    inccalls(s,1);
    for (int j = l + 1; j <= r; j++)
    {
        // if `arr[j]` is less, then it is the new minimum
	inccmp(s,1);
        if (arr[j] < arr[min]) {
            min = j;    // update the index of minimum element
        }
    }

    // swap the minimum element in subarray `arr[i…n-1]` with `arr[i]`
    if (min!=l)
      swap(&arr[min], &arr[l], s);

    if (l + 1 < r) {
        recursiveSelectionSort(arr, l + 1, r, s);
    }
}

void insertionSort(int v[], int l, int r, sortperf_t * s){
    int i, j;
    Item aux;
    inccalls(s, 1);
  for (i = 1; i < n; i++) {
    aux = v[i];
    incmove(s, 1);
    j = i - 1;
    while (( j >= 0 ) && (aux.Chave < v[j].Chave)) {
      inccmp(s, 1);
      v[j + 1] = v[j];
      j--;
    }
    v[j + 1] = aux;
    incmove(s, 1);
  }
}

int median (int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}

// standard quicksort
void quickSort(int * A, int l, int r, sortperf_t *s){
  if (l < r){
    int i, j;
    partition(A, l, r, &i, &j, s);
    inccalls(s, 2);
    quickSort(A, l, j, s);
    quickSort(A, i, r, s);
  }
}
/*void quickSort3(int * A, int l, int r, sortperf_t *s){

}
void quickSortIns(int * A, int l, int r, sortperf_t *s){

}
void quickSort3Ins(int * A, int l, int r, sortperf_t *s){

}*/


// quicksort partition using median of 3
void partition3(int * A, int l, int r, int *i, int *j, sortperf_t *s){

}

// standard quicksort partition
void partition(int * A, int l, int r, int *i, int *j, sortperf_t *s){
    Item x, w;
    *i = l; *j = r;
    x = A[(*i + *j)/2]; /* obtem o pivo x */
      do
        { while (x.Chave > A[*i].Chave) (*i)++;
           while (x.Chave < A[*j].Chave) (*j)--;
              if (*i <= *j)
               { w = A[*i];
                 A[*i] = A[*j];
                A[*j] = w;
                (*i)++; (*j)--;
              }   
        } while (*i <= *j);
}

void shellSort(int *A, int n, sortperf_t * s){
  inccalls(s, 1);
    for (int h = n / 2; h > 0; h /= 2) {
    for (int i = h; i < n; i += 1) {
      incmove(s, 1);
      int temp = array[i];
      int j;
      for (j = i; j >= h && array[j-h] > temp; j-= h) {
        inccmp(s, 1);
        array[j] = array[j - h];
        incmove(s, 1);
      }
      array[j] = temp;
      incmove(s, 1);
    }
  }
}