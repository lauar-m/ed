#ifndef MERGESORT_HPP
#define MERGESORT_HPP
#include "pessoa.hpp"
#include "ordindireta.hpp"

void merge(Pessoa* pessoas, int* indices, int esquerda, int direita, int meio, const int campo);
void mergesort(Pessoa* pessoas, int* indices, int esquerda, int direita, const int campo);
#endif