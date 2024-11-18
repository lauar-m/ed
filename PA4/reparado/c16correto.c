#include <stdio.h>
#include <stdlib.h>

int actual_calc(int a, int b){
  if (b == 0) {
    fprintf(stderr, "Erro: divisão por zero\n");
    return -1; 
  }
  int c;
  c = a / b;
  return c;
}

int calc(){
  int a;
  int b;
  a = 13;
  b = 0;
  int result = actual_calc(a, b);
  if (result == -1) {
    return -1; 
  }
  return 0;
}

int main(){
  if (calc() == -1) {
    return 1;
  }
  return 0;
}