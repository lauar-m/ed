#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *buf;

int sum_to_n(int num)
{
    int i, sum = 0;
    for (i = 1; i <= num; i++)
        sum += i;
    return sum;
}

void printSum()
{
    char line[10];
    buf = malloc(20 * sizeof(char));
    if (buf == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória\n");
        exit(1);
    }

    printf("enter a number:\n");
    if (fgets(line, 10, stdin) != NULL)
    {
        strtok(line, "\n");
        sprintf(buf, "sum=%d", sum_to_n(atoi(line)));
        printf("%s\n", buf);
    }
    else
    {
        fprintf(stderr, "Erro ao ler a entrada\n");
    }

    free(buf);
}

int main(void)
{
    printSum();
    return 0;
}