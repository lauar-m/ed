#ifndef NOARVOREB_HPP
#define NOARVOREB_HPP

#include "listaEncad.hpp"
#include "voo.hpp"
#include <string>

class noArvoreB {
public:
    noArvoreB(int t, bool leaf);
    void insertNonFull(Voo* voo, const std::string& key);
    void splitChild(int i, noArvoreB* y);
    ListaEncad<Voo>* search(const std::string& key);

private:
    int t;  // Grau mínimo da árvore
    bool leaf;  // Indica se o nó é folha
    int n;  // Número atual de chaves
    std::string* keys;  // Array de chaves
    ListaEncad<Voo>** voos;  // Array de listas encadeadas de voos
    noArvoreB** C;  // Array de ponteiros para filhos

    friend class ArvoreB;  // Permite que a classe BTree acesse membros privados
};

#endif