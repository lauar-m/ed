#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int *p;
    for (int i = 0; i < 100; i++) 
    {
        p = malloc(128);
        if (p == NULL) {
            fprintf(stderr, "Erro ao alocar memória\n");
            return 1;
        }
        printf("%ld\n", (long)p);
        free(p);
    }
    return 0;
}