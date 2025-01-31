#include "consulta.hpp"

// Construtor da classe Consulta
Consulta::Consulta(int maxVoos, std::string order, std::string expression)
    : maxVoos(maxVoos), order(order), expression(expression) {}

// Método para obter o número máximo de voos
int Consulta::getMaxVoos() const {
    return maxVoos;
}

// Método para obter o critério de ordenação
std::string Consulta::getOrder() const {
    return order;
}

// Método para obter a expressão de filtragem
std::string Consulta::getExpression() const {
    return expression;
}

// Método evaluate: aplica os filtros especificados na expressão lógica
ListaEncad<Voo>* Consulta::evaluate(ListaEncad<Voo>* Voos) {
    ListaEncad<Voo>* filteredVoos = new ListaEncad<Voo>();

    for (int i = 0; i < Voos->tamanho(); i++) {
        Voo* voo = Voos->get(i);

        // Aplicar os filtros com base na expressão lógica
        if (expression.find("dur>=") != std::string::npos) {
            size_t pos = expression.find("dur>=");
            int durMin = std::stoi(expression.substr(pos + 5));
            if (voo->getDuracao() < durMin) continue;
        }
        if (expression.find("sea<=") != std::string::npos) {
            size_t pos = expression.find("sea<=");
            int seaMax = std::stoi(expression.substr(pos + 5));
            if (voo->getAssentosDisp() > seaMax) continue;
        }
        if (expression.find("sea>=") != std::string::npos) {
            size_t pos = expression.find("sea>=");
            int seaMin = std::stoi(expression.substr(pos + 5));
            if (voo->getAssentosDisp() < seaMin) continue;
        }
        if (expression.find("dst==") != std::string::npos) {
            size_t pos = expression.find("dst==");
            std::string dst = expression.substr(pos + 5, 3); // Assume que o destino tem 3 caracteres
            if (voo->getDestino() != dst) continue;
        }

        // Se o voo passar por todos os filtros, adicioná-lo à lista filtrada
        filteredVoos->adiciona(voo);
    }

    return filteredVoos;
}

// Método sortVoos: ordena os voos com base no critério especificado
ListaEncad<Voo>* Consulta::sortVoos(ListaEncad<Voo>* Voos) {
    // Implementação do Bubble Sort para ordenar a lista encadeada
    bool trocou;
    do {
        trocou = false;
        for (int i = 0; i < Voos->tamanho() - 1; i++) {
            Voo* vooAtual = Voos->get(i);
            Voo* vooProximo = Voos->get(i + 1);

            bool deveTrocar = false;

            if (order == "psd") {
                // Ordenar por preço, número de paradas e duração
                if (vooAtual->getPreco() > vooProximo->getPreco()) {
                    deveTrocar = true;
                } else if (vooAtual->getPreco() == vooProximo->getPreco()) {
                    if (vooAtual->getParadas() > vooProximo->getParadas()) {
                        deveTrocar = true;
                    } else if (vooAtual->getParadas() == vooProximo->getParadas()) {
                        if (vooAtual->getDuracao() > vooProximo->getDuracao()) {
                            deveTrocar = true;
                        }
                    }
                }
            } else if (order == "sdp") {
                // Ordenar por número de paradas, duração e preço
                if (vooAtual->getParadas() > vooProximo->getParadas()) {
                    deveTrocar = true;
                } else if (vooAtual->getParadas() == vooProximo->getParadas()) {
                    if (vooAtual->getDuracao() > vooProximo->getDuracao()) {
                        deveTrocar = true;
                    } else if (vooAtual->getDuracao() == vooProximo->getDuracao()) {
                        if (vooAtual->getPreco() > vooProximo->getPreco()) {
                            deveTrocar = true;
                        }
                    }
                }
            }

            // Trocar os voos se necessário
            if (deveTrocar) {
                Voos->retiraDaPosicao(i);
                Voos->adicionaNaPosicao(vooProximo, i);
                Voos->retiraDaPosicao(i + 1);
                Voos->adicionaNaPosicao(vooAtual, i + 1);
                trocou = true;
            }
        }
    } while (trocou);

    return Voos;
}