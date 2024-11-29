#include "heapsort.hpp"
#include <iostream>


// o modelo dessa ordenação foi inspirado no site programiz
void heapify(Pessoa* pessoas, int* indices, int n, int i, const int campo) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n){
        bool compara = false;
        if (campo == 1){
            compara = pessoas[indices[esq]].nome > pessoas[indices[maior]].nome; 
        } else if (campo == 2){
            compara = pessoas[indices[esq]].cpf > pessoas[indices[maior]].cpf; 
        } else if (campo == 3){
            compara = pessoas[indices[esq]].endereco > pessoas[indices[maior]].endereco; 
        }
        if (compara){
            maior = esq;
        }
    }


    if (dir < n){
        bool compara = false;
        if (campo == 1){
            compara = pessoas[indices[dir]].nome > pessoas[indices[maior]].nome;
        } else if (campo == 2){
            compara = pessoas[indices[dir]].cpf > pessoas[indices[maior]].cpf;
        } else if (campo == 3){
            compara = pessoas[indices[dir]].endereco > pessoas[indices[maior]].endereco;
        }
        if (compara){
            maior = dir;
        }
    }

    if (maior != i) {
        swapindices(indices, i, maior);
        heapify(pessoas, indices, n, maior, campo);
    }
}

void heapsort (Pessoa* pessoas, int* indices, int n, const int campo){
    for (int i = n / 2 - 1; i>=0; i--){
        heapify(pessoas, indices, n, i, campo);
    }

    for (int i = n - 1; i >= 0; i--){
        swapindices(indices, 0, i);
        heapify(pessoas, indices, i, 0, campo);
    }
}
