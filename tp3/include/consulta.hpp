#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include <string>
#include "voo.hpp"
#include "listaEncad.hpp"

class Consulta
{
public:
    Consulta(int maxVoos, std::string order, std::string expression);
    ListaEncad<Voo> *evaluate(ListaEncad<Voo> *Voos);
    ListaEncad<Voo> *sortVoos(ListaEncad<Voo> *Voos);
    int getMaxVoos() const;
    std::string getOrder() const;
    std::string getExpression() const;
    bool avaliarPredicadoSimples(Voo *voo, const std::string &predicado);

private:
    int maxVoos;            // Número máximo de voos a serem retornados
    std::string order;      // Critério de ordenação
    std::string expression; // Expressão de filtragem
};

#endif // CONSULTA_HPP
