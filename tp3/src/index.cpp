#include "index.hpp"

Index::Index() {
    voos = new ListaEncad<Voo>();
}

void Index::addVoo(Voo* voo) {
    voos->adiciona(voo);
}

ListaEncad<Voo>* Index::searchVoos(std::string predicate) {
    // Implementar a lógica de busca com base no predicado
    return voos;
}