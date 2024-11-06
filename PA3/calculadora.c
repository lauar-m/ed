#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função recursiva para calcular o fatorial
unsigned long long factorial_recursive(int n) {
    if (n <= 1) return 1;
    return n * factorial_recursive(n - 1);
}

// Função iterativa para calcular o fatorial
unsigned long long factorial_iterative(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Função recursiva para calcular o número de Fibonacci
unsigned long long fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

// Função iterativa para calcular o número de Fibonacci
unsigned long long fibonacci_iterative(int n) {
    if (n <= 1) return n;
    unsigned long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Função para medir o tempo de execução de uma função
void measure_time(unsigned long long (*func)(int), int n) {
    clock_t start, end;
    start = clock();
    unsigned long long result = func(n);
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Resultado: %llu\n", result);
    printf("Tempo de execução: %.6f segundos\n", time_taken);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <tarefa> <metodo> <numero>\n", argv[0]);
        printf("Tarefas: fatorial, fibonacci\n");
        printf("Métodos: recursivo, iterativo\n");
        return 1;
    }

    char *task = argv[1];
    char *method = argv[2];
    int number = atoi(argv[3]);

    if (number < 0) {
        printf("O número deve ser um inteiro não negativo.\n");
        return 1;
    }

    printf("Tarefa: %s, Método: %s, Número: %d\n", task, method, number);

    if (strcmp(task, "fatorial") == 0) {
        if (strcmp(method, "recursivo") == 0) {
            measure_time(factorial_recursive, number);
        } else if (strcmp(method, "iterativo") == 0) {
            measure_time(factorial_iterative, number);
        } else {
            printf("Método não reconhecido para fatorial.\n");
            return 1;
        }
    } else if (strcmp(task, "fibonacci") == 0) {
        if (strcmp(method, "recursivo") == 0) {
            measure_time(fibonacci_recursive, number);
        } else if (strcmp(method, "iterativo") == 0) {
            measure_time(fibonacci_iterative, number);
        } else {
            printf("Método não reconhecido para Fibonacci.\n");
            return 1;
        }
    } else {
        printf("Tarefa não reconhecida.\n");
        return 1;
    }

    return 0;
}
