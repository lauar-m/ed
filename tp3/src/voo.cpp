#include "voo.hpp"
#include <string>

Voo::Voo(std::string org, std::string dst, double prc, int sea, std::string dep, std::string arr, int sto) {
    origem = org;
    destino = dst;
    preco = prc;
    assentosDisp = sea;
    horaPartida = dep;
    horaChegada = arr;
    paradas = sto;
    duracao = 0;
}

std::string Voo::getOrigem() {
    return origem;
}

std::string Voo::getDestino() {
    return destino;
}

double Voo::getPreco() {
    return preco;
}

int Voo::getAssentosDisp() {
    return assentosDisp;
}

std::string Voo::getHoraPartida() {
    return horaPartida;
}

std::string Voo::getHoraChegada() {
    return horaChegada;
}

int Voo::getParadas() {
    return paradas;
}

int Voo::getDuracao() {
    return duracao;
}
