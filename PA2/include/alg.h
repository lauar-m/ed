#ifndef IMPLEMENT_H
#define IMPLEMENT_H

typedef struct alg{
  int num;
  char * name;
} alg_t;

alg_t algvet[]={
  {ALGINSERTION,"i"},
  {ALGSELECTION,"s"},
  {ALGQSORT,"q"},
  {ALGQSORT3,"q3"},
  {ALGQSORTINS,"qi"},
  {ALGQSORT3INS,"q3i"},
  {ALGSHELLSORT,"h"},
  {ALGRECSEL,"rs"},
  {0,0}
};

int name2num(char * name){
  int i=0;
  while (algvet[i].num){
    if (!strcmp(algvet[i].name,name)) return algvet[i].num;
    i++;
  }
  return 0;
}

char * num2name(int num){
  int i=0;
  while (algvet[i].num){
    if (algvet[i].num==num) return algvet[i].name;
    i++;
  }
  return 0;
}

void selectionSort(int arr[], int l, int r, sortperf_t * s);
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t * s)

void insertionSort(int v[], int l, int r, sortperf_t * s);

int median (int a, int b, int c);

void quickSort(int * A, int l, int r, sortperf_t *s);
void quickSort3(int * A, int l, int r, sortperf_t *s);
void quickSortIns(int * A, int l, int r, sortperf_t *s);
void quickSort3Ins(int * A, int l, int r, sortperf_t *s);

void partition3(int * A, int l, int r, int *i, int *j, sortperf_t *s);
void partition(int * A, int l, int r, int *i, int *j, sortperf_t *s);

void shellSort(int *A, int n, sortperf_t * s);

#endif