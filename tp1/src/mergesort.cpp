
#include "mergesort.hpp"
#include "pessoa.hpp"
#include <iostream>

void merge(Pessoa* pessoas, int* indices, int esquerda, int meio, int direita, const int campo){
    int tamEsq = meio - esquerda + 1; // tamanho do array esquerda
    int tamDir = direita - meio; // tamanho do array direita

    int* esquerdaIndices = new int[tamEsq]; // array para indices esquerda
    int* direitaIndices = new int[tamDir]; // array para indices direita

    for(int i = 0; i < tamEsq; i++){ // preenche array esquerda
        esquerdaIndices[i] = indices[esquerda + i];
    }
    for(int j = 0; j < tamDir; j++){ // preenche array direita
        direitaIndices[j] = indices[meio + 1 + j];
    }

    int i = 0;  
    int j = 0; 
    int k = esquerda; // k é o índice do array original 

    while (i < tamEsq && j < tamDir) {
        bool compara = false;

        if (campo == 1){
            compara = pessoas[esquerdaIndices[i]].nome <= pessoas[direitaIndices[j]].nome;
        } else if (campo == 2){
            compara = pessoas[esquerdaIndices[i]].cpf <= pessoas[direitaIndices[j]].cpf;
        } else if (campo == 3){
            compara = pessoas[esquerdaIndices[i]].endereco <= pessoas[direitaIndices[j]].endereco;
        }

        if (compara) { // comparação direta
            indices[k++] = esquerdaIndices[i++];
        } else {
            indices[k++] = direitaIndices[j++];
        }
    }

    while (i < tamEsq) { 
        indices[k++] = esquerdaIndices[i++];
    }

    while (j < tamDir) {
        indices[k++] = direitaIndices[j++];
    }

    // para liberar a memória
    delete[] esquerdaIndices;
    delete[] direitaIndices;
}

void mergesort(Pessoa* pessoas, int* indices, int esquerda, int direita, const int campo){
    if (esquerda < direita){ 
        int meio = (esquerda + direita) / 2;
        // divide
        mergesort(pessoas, indices, esquerda, meio, campo);
        mergesort(pessoas, indices, meio + 1, direita, campo);
        // combina
        merge(pessoas, indices, esquerda, meio, direita, campo);
    }
}