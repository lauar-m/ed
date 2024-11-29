#include "ordindireta.hpp"
#include "pessoa.hpp"

// 
int* iniciaindices(int tamanho){
    int* indices = new int[tamanho];
    for (int i = 0; i < tamanho; i++) {
        indices[i] = i;
    }
    return indices;
}

// Função pra trocar duas pessoas de lugar
void swapindices(int* indices, int i, int j){
    int temp = indices[i];
    indices[i] = indices[j];
    indices[j] = temp;
}
