#include "../include/quicksort.hpp"
#include "pessoa.hpp"
#include <iostream>
#include "ordindireta.hpp"

// Função de partição para o quicksort por NOME
int partitionNOME(Pessoa* pessoas, int* indices, int low, int high){
    std::string pivot = pessoas[indices[high]].nome;
    int i = low - 1;

    for(int j = low; j < high; j++){
        if(pessoas[indices[j]].nome < pivot){ //comparação indireta nome
            i++;
            swapindices(indices, i, j);
        }
    }
    swapindices(indices, i + 1, high);
    return i + 1;
}


// Função de partição para o quicksort por CPF
int partitionCPF(Pessoa* pessoas, int* indices, int low, int high) {
    std::string pivot = pessoas[indices[high]].cpf; // Pega o CPF do índice pivô
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (pessoas[indices[j]].cpf < pivot) { // comparação indireta cpf
            i++;
            swapindices(indices, i, j); // faz a troca dos índices
        }
    }
    swapindices(indices, i + 1, high); // coloca o pivô no lugar certo
    return i + 1;
}

// Função de partição para o quicksort por ENDERECO
int partitionENDERECO(Pessoa* pessoas, int* indices, int low, int high) {
    std::string pivot = pessoas[indices[high]].endereco;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (pessoas[indices[j]].endereco <= pivot) { // comparacao indireta endereco
            i++;
            std::swap(indices[i], indices[j]); // troca indices
        }
    }
    std::swap(indices[i + 1], indices[high]); // coloca pivo no lugar certo
    return i + 1;
}


// Função de ordenação quicksort por NOME
void quicksortNOME(Pessoa* pessoas, int* indices, int low, int high){
    if(low < high){
        int pi = partitionNOME(pessoas, indices, low, high);

        quicksortNOME(pessoas, indices, low, pi - 1);
        quicksortNOME(pessoas, indices, pi + 1, high);
    }
}

// Função de ordenação quicksort por CPF
void quicksortCPF(Pessoa* pessoas, int* indices, int low, int high){
    if (low < high) {
        int pi = partitionCPF(pessoas, indices, low, high);

        quicksortCPF(pessoas, indices, low, pi - 1);
        quicksortCPF(pessoas, indices, pi + 1, high);
    }
}

// test
void quicksortENDERECO(Pessoa* pessoas, int* indices, int low, int high){
    if(low < high){
        int pi = partitionENDERECO(pessoas, indices, low, high);

        quicksortENDERECO(pessoas, indices, low, pi - 1);
        quicksortENDERECO(pessoas, indices, pi + 1, high);

    }
}