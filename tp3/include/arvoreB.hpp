#ifndef ARVOREB_HPP
#define ARVOREB_HPP

#include "noArvoreB.hpp"
#include "listaEncad.hpp"
#include "voo.hpp"

class ArvoreB {
public:
    ArvoreB(int t);
    void insert(Voo* voo, const std::string& key);
    ListaEncad<Voo>* search(const std::string& key);

private:
    noArvoreB* root;  // Raiz da árvore
    int t;  // Grau mínimo da árvore
};

#endif 