#ifndef DESEMP_H
#define DESEMP_H

#define ALGINSERTION 1
#define ALGSELECTION 2
#define ALGQSORT     3
#define ALGQSORT3    4
#define ALGQSORTINS  5
#define ALGQSORT3INS 6
#define ALGSHELLSORT 7
#define ALGRECSEL    8

typedef struct sortperf{
  int cmp;
  int move;
  int calls;
} sortperf_t;

void resetcounter(sortperf_t * s);
void inccmp(sortperf_t * s, int num);
void incmove(sortperf_t * s, int num);
void inccalls(sortperf_t * s, int num);
char * printsortperf(sortperf_t * s, char * str, char * pref);

typedef struct opt {
    int size;
    int seed;
    int alg;
} opt_t;

void initVector(int *vet, int size);
void printVector(int *vet, int size);
void clkDiff(struct timespec t1, struct timespec t2, struct timespec *res);
void parse_args(int argc, char **argv, opt_t *opt);


#endif