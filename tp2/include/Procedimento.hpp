#ifndef PROCEDIMENTO_HPP
#define PROCEDIMENTO_HPP
#include <string>

class Procedimento {
public:
    Procedimento();
    Procedimento(std::string nomeProcedimento, float tempo, int capacidade);
    
    std::string getNomeProcedimento() const;

    void ocuparUnidade();
    bool temUnidadeLivre();
    void liberarUnidade();
    float getTempo() const;
    int getCapacidade() const;
    int capacidadeLivres() const;
    void imprimir() const; 

private:
    std::string nomeProcedimento;
    float tempo;
    int capacidade;
    int unidadesOcupadas;
};

#endif // PROCEDIMENTO_HPP
