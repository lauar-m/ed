#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include "pessoa.hpp"
#include <string>

int partitionNOME(Pessoa* pessoas, int* indices, int low, int high); 
int partitionCPF(Pessoa* pessoas, int* indices, int low, int high);
int partitionENDERECO(Pessoa* pessoas, int* indices, int low, int high);

void quicksortNOME(Pessoa* pessoas, int* indices, int low, int high);
void quicksortCPF(Pessoa* pessoas, int* indices, int low, int high);
void quicksortENDERECO(Pessoa* pessoas, int* indices, int low, int high);

#endif