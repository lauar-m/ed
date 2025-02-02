#include "voo.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

// Construtor da classe Voo
Voo::Voo(std::string org, std::string dst, double prc, int sea, std::string dep, std::string arr, int sto)
    : origem(org), destino(dst), preco(prc), assentosDisp(sea), horaPartida(dep), horaChegada(arr), paradas(sto) {
    // Calcular a duração do voo em segundos
    int partidaSegundos = converterParaSegundos(horaPartida);
    int chegadaSegundos = converterParaSegundos(horaChegada);
    duracao = chegadaSegundos - partidaSegundos;

    // Verificar se a duração é válida
    if (duracao < 0) {
        std::cerr << "Erro: Duração negativa para o voo " << origem << "->" << destino << std::endl;
        duracao = 0;
    }
}

// Métodos getters
std::string Voo::getOrigem() { return origem; }
std::string Voo::getDestino() { return destino; }
double Voo::getPreco() { return preco; }
int Voo::getAssentosDisp() { return assentosDisp; }
std::string Voo::getHoraPartida() { return horaPartida; }
std::string Voo::getHoraChegada() { return horaChegada; }
int Voo::getParadas() { return paradas; }
int Voo::getDuracao() { return duracao; }

// Função auxiliar para converter data-hora em segundos
int Voo::converterParaSegundos(const std::string& datetime) {
    struct tm tm = {};
    std::istringstream ss(datetime);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S"); // Formato esperado: "AAAA-MM-DDTHH:MM:SS"
    if (ss.fail()) {
        std::cerr << "Erro ao converter data: " << datetime << std::endl;
        return 0;
    }
    return static_cast<int>(mktime(&tm));
}
