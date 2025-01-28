#ifndef FILA_HPP
#define FILA_HPP

#include <iostream>

// Estrutura No para representar um nó na fila
struct No {
    int dados;  // Alterado de string para int
    No* proximo;

    No(int _dados) : dados(_dados), proximo(NULL) {}
};

// Classe Fila para representar a fila
class Fila {
private:
    No* frente;
    No* tras;

public:
    Fila();
    ~Fila();
    
    bool estaVazia() const;
    void enfileirar(int dados);  
    int desenfileirar();         
    int obterFrente() const;    
    void imprimir() const;
};

#endif
