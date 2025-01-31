#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include <string>
#include "voo.hpp"
#include "listaEncad.hpp"

class Consulta {
public:
    Consulta(int maxVoos, std::string order, std::string expression);
    ListaEncad<Voo>* evaluate(ListaEncad<Voo>* Voos);
    ListaEncad<Voo>* sortVoos(ListaEncad<Voo>* Voos);

    // Métodos para acessar os atributos privados
    int getMaxVoos() const;
    std::string getOrder() const;
    std::string getExpression() const;

private:
    int maxVoos;
    std::string order;
    std::string expression;
};

#endif // CONSULTA_HPP