#include "Procedimento.hpp"
#include <iostream>

Procedimento::Procedimento() : nomeProcedimento(""), tempo(0), capacidade(0), unidadesOcupadas(0){}

Procedimento::Procedimento(std::string nomeProcedimento, float tempo, int capacidade) 
    : nomeProcedimento(nomeProcedimento), tempo(tempo), capacidade(capacidade), unidadesOcupadas(0) {}

std::string Procedimento::getNomeProcedimento() const {
    return nomeProcedimento;
}

float Procedimento::getTempo() const {
    return tempo;
}

int Procedimento::getCapacidade() const {
    return capacidade;
}

void Procedimento::ocuparUnidade() {
    if (unidadesOcupadas < capacidade) {
        unidadesOcupadas++;
    } else {
        std::cerr << "Erro: tentativa de ocupar unidade além da capacidade." << std::endl;
    }
}


void Procedimento::liberarUnidade() {
    if (unidadesOcupadas > 0) {
        unidadesOcupadas--;
    }
}


bool Procedimento::temUnidadeLivre() {
    if (unidadesOcupadas < capacidade){
        return true;
    } else 
    return false;
}

int Procedimento::capacidadeLivres() const {
    return capacidade - unidadesOcupadas;
}


// Função que imprime os detalhes do procedimento
void Procedimento::imprimir() const {
    std::cout << "Procedimento: " << nomeProcedimento << ", Tempo: " << tempo << ", Capacidade: " << capacidade << std::endl;
}
