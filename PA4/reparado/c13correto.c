#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *p;

  p = (char *) malloc(19);
  if (p == NULL) {
      fprintf(stderr, "Erro ao alocar memória\n");
      return 1;
  }
  free(p); 

  p = (char *) malloc(12);
  if (p == NULL) {
      fprintf(stderr, "Erro ao alocar memória\n");
      return 1;
  }
  free(p); 

  p = (char *) malloc(16);
  if (p == NULL) {
      fprintf(stderr, "Erro ao alocar memória\n");
      return 1;
  }

  free(p);
  return 0;
}