#ifndef INDEX_HPP
#define INDEX_HPP

#include "voo.hpp"
#include "listaEncad.hpp"

class Index {
public:
    Index();
    void addVoo(Voo* voo);
    ListaEncad<Voo>* searchVoos(std::string predicate);

private:
    ListaEncad<Voo>* voos;
};

#endif // INDEX_HPP