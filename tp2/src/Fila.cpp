#include "Fila.hpp"
#include <iostream>

// Construtor da fila
Fila::Fila() : frente(NULL), tras(NULL) {}

// Destrutor da fila
Fila::~Fila() {
    while (!estaVazia()) {
        desenfileirar();
    }
}

// Verifica se a fila está vazia
bool Fila::estaVazia() const {
    return frente == NULL;
}

// Adiciona um elemento à fila (no final)
void Fila::enfileirar(int valor) {
    No* novoNo = new No{valor};
    if (estaVazia()) {
        frente = novoNo;
    } else {
        tras->proximo = novoNo;
    }
    tras = novoNo;
}

// Remove e retorna o elemento da frente da fila
int Fila::desenfileirar() {
    if (estaVazia()) {
        throw std::runtime_error("Fila vazia");
    }
    No* noRemovido = frente;
    int valor = noRemovido->dados;
    frente = frente->proximo;
    if (frente == NULL) {
        tras = NULL;
    }
    delete noRemovido;
    return valor;
}

// Retorna o elemento da frente sem removê-lo
int Fila::obterFrente() const {
    if (estaVazia()) {
        throw std::runtime_error("Fila vazia");
    }
    return frente->dados;
}

// Imprime o conteúdo da fila (para depuração)
void Fila::imprimir() const {
    No* atual = frente;
    while (atual != NULL) {
        std::cout << atual->dados << " ";
        atual = atual->proximo;
    }
    std::cout << std::endl;
}
