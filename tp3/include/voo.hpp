#ifndef VOO_H
#define VOO_H

#include <string>

class Voo {
public:
    Voo(std::string org, std::string dst, double prc, int sea, std::string dep, std::string arr, int sto);
    std::string getOrigem();
    std::string getDestino();
    double getPreco();
    int getAssentosDisp();
    std::string getHoraPartida();
    std::string getHoraChegada();
    int getParadas();
    int getDuracao();

private:
    std::string origem;
    std::string destino;
    double preco;
    int assentosDisp;
    std::string horaPartida;
    std::string horaChegada;
    int paradas;
    int duracao;
};

#endif