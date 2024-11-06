#include "desemp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void resetcounter(sortperf_t * s){
// Descricao: inicializa estrutura
// Entrada: 
// Saida: s
  s->cmp = 0;
  s->move = 0;
  s->calls = 0;
}

void inccmp(sortperf_t * s, int num){
// Descricao: incrementa o numero de comparacoes em num 
// Entrada: s, num
// Saida: s
  s->cmp += num;
}

void incmove(sortperf_t * s, int num){
// Descricao: incrementa o numero de movimentacoes de dados em num 
// Entrada: s, num
// Saida: s
  s->move += num;
}

void inccalls(sortperf_t * s, int num){
// Descricao: incrementa o numero de chamadas de função em num 
// Entrada: s, num
// Saida: s
  s->calls += num;
}

char * printsortperf(sortperf_t * s, char * str, char * pref){
// Descricao: gera string com valores de sortperf 
// Entrada: s, pref
// Saida: str

 sprintf(str,"%s cmp %d move %d calls %d", pref, s->cmp, s->move, s->calls); 
 return str;
}

void initVector(int *vet, int size) {
    for (int i = 0; i < size; i++) {
        vet[i] = (int)(drand48() * size);
    }
}

void printVector(int *vet, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void clkDiff(struct timespec t1, struct timespec t2, struct timespec *res) {
    if (t2.tv_nsec < t1.tv_nsec) {
        res->tv_nsec = 1000000000 + t2.tv_nsec - t1.tv_nsec;
        res->tv_sec = t2.tv_sec - t1.tv_sec - 1;
    } else {
        res->tv_nsec = t2.tv_nsec - t1.tv_nsec;
        res->tv_sec = t2.tv_sec - t1.tv_sec;
    }
}

void parse_args(int argc, char **argv, opt_t *opt) {
    extern char *optarg;
    extern int optind;
    int c;

    opt->seed = 1;
    opt->size = 10;
    opt->alg = 1;

    while ((c = getopt(argc, argv, "z:s:a:h")) != EOF) {
        switch (c) {
            case 'z':
                opt->size = atoi(optarg);
                break;
            case 's':
                opt->seed = atoi(optarg);
                break;
            case 'a':
                opt->alg = name2num(optarg);
                break;
            case 'h':
            default:
                uso();
                exit(1);
        }
    }
}
