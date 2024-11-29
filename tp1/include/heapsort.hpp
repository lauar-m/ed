#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP
#include "pessoa.hpp"
#include "ordindireta.hpp"

void heapify(Pessoa* pessoas, int* indices, int n, int i, const int campo);
void heapsort(Pessoa* pessoas, int* indices, int n, const int campo);

#endif