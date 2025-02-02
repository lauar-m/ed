#include "consulta.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

// Construtor da classe Consulta
Consulta::Consulta(int maxVoos, std::string order, std::string expression)
    : maxVoos(maxVoos), order(order), expression(expression) {}

// Método para obter o número máximo de voos
int Consulta::getMaxVoos() const
{
    return maxVoos;
}

// Método para obter o critério de ordenação
std::string Consulta::getOrder() const
{
    return order;
}

// Método para obter a expressão de filtragem
std::string Consulta::getExpression() const
{
    return expression;
}

ListaEncad<Voo> *Consulta::evaluate(ListaEncad<Voo> *Voos)
{
    ListaEncad<Voo> *filteredVoos = new ListaEncad<Voo>();
    std::string expressaoLimpa = expression;

    // Remover espaços e parênteses da expressão
    expressaoLimpa.erase(std::remove_if(expressaoLimpa.begin(), expressaoLimpa.end(), [](char c)
                                        { return c == '(' || c == ')' || c == ' '; }),
                         expressaoLimpa.end());

    // Dividir a expressão em predicados usando '&&' como delimitador
    size_t pos = 0;
    std::string token;
    while ((pos = expressaoLimpa.find("&&")) != std::string::npos)
    {
        token = expressaoLimpa.substr(0, pos);
        expressaoLimpa.erase(0, pos + 2); // +2 para remover o '&&'
        // Filtrar os voos com base no predicado atual
        for (int i = 0; i < Voos->tamanho(); i++)
        {
            Voo *voo = Voos->get(i);
            
            if (!avaliarPredicadoSimples(voo, token))
            {
                // Remover voos que não atendem ao predicado
                Voos->retiraDaPosicao(i);
                i--;
            }
        }
    }

    // Processar o último predicado restante
    if (!expressaoLimpa.empty())
    {
        for (int i = 0; i < Voos->tamanho(); i++)
        {
            Voo *voo = Voos->get(i);
            if (!avaliarPredicadoSimples(voo, expressaoLimpa))
            {
                // Remover voos que não atendem ao predicado
                Voos->retiraDaPosicao(i);
                i--;
            }
        }
    }

    // Adicionar voos filtrados à nova lista
    for (int i = 0; i < Voos->tamanho(); i++)
    {
        filteredVoos->adiciona(Voos->get(i));
    }

    return filteredVoos;
}

// Método sortVoos: ordena os voos com bubbleSort
ListaEncad<Voo> *Consulta::sortVoos(ListaEncad<Voo> *Voos)
{
    bool trocou;
    int tamanho = Voos->tamanho();

    do
    {
        trocou = false;
        for (int i = 0; i < tamanho - 1; i++)
        {
            Voo *vooAtual = Voos->get(i);
            Voo *vooProximo = Voos->get(i + 1);
            bool deveTrocar = false;

            if (order == "psd")
            {
                // Critério de ordenação "psd" (preço, paradas, duração)
                if (vooAtual->getPreco() > vooProximo->getPreco())
                {
                    deveTrocar = true;
                }
                else if (vooAtual->getPreco() == vooProximo->getPreco())
                {
                    if (vooAtual->getParadas() > vooProximo->getParadas())
                    {
                        deveTrocar = true;
                    }
                    else if (vooAtual->getParadas() == vooProximo->getParadas())
                    {
                        if (vooAtual->getDuracao() > vooProximo->getDuracao())
                        {
                            deveTrocar = true;
                        }
                    }
                }
            }
            else if (order == "pds")
            {
                // Critério de ordenação "pds" (preço, duração, paradas)
                if (vooAtual->getPreco() > vooProximo->getPreco())
                {
                    deveTrocar = true;
                }
                else if (vooAtual->getPreco() == vooProximo->getPreco())
                {
                    if (vooAtual->getDuracao() > vooProximo->getDuracao())
                    {
                        deveTrocar = true;
                    }
                    else if (vooAtual->getDuracao() == vooProximo->getDuracao())
                    {
                        if (vooAtual->getParadas() > vooProximo->getParadas())
                        {
                            deveTrocar = true;
                        }
                    }
                }
            }
            else if (order == "spd")
            {
                // Critério de ordenação "spd" (paradas, preço, duração)
                if (vooAtual->getParadas() > vooProximo->getParadas())
                {
                    deveTrocar = true;
                }
                else if (vooAtual->getParadas() == vooProximo->getParadas())
                {
                    if (vooAtual->getPreco() > vooProximo->getPreco())
                    {
                        deveTrocar = true;
                    }
                    else if (vooAtual->getPreco() == vooProximo->getPreco())
                    {
                        if (vooAtual->getDuracao() > vooProximo->getDuracao())
                        {
                            deveTrocar = true;
                        }
                    }
                }
            }
            else if (order == "sdp")
            {
                // Critério de ordenação "sdp" (paradas, duração, preço)
                if (vooAtual->getParadas() > vooProximo->getParadas())
                {
                    deveTrocar = true;
                }
                else if (vooAtual->getParadas() == vooProximo->getParadas())
                {
                    if (vooAtual->getDuracao() > vooProximo->getDuracao())
                    {
                        deveTrocar = true;
                    }
                    else if (vooAtual->getDuracao() == vooProximo->getDuracao())
                    {
                        if (vooAtual->getPreco() > vooProximo->getPreco())
                        {
                            deveTrocar = true;
                        }
                    }
                }
            }
            else if (order == "dps")
            {
                // Critério de ordenação "dps" (duração, preço, paradas)
                if (vooAtual->getDuracao() > vooProximo->getDuracao())
                {
                    deveTrocar = true;
                }
                else if (vooAtual->getDuracao() == vooProximo->getDuracao())
                {
                    if (vooAtual->getPreco() > vooProximo->getPreco())
                    {
                        deveTrocar = true;
                    }
                    else if (vooAtual->getPreco() == vooProximo->getPreco())
                    {
                        if (vooAtual->getParadas() > vooProximo->getParadas())
                        {
                            deveTrocar = true;
                        }
                    }
                }
            }
            else if (order == "dsp")
            {
                // Critério de ordenação "dsp" (duração, paradas, preço)
                if (vooAtual->getDuracao() > vooProximo->getDuracao())
                {
                    deveTrocar = true;
                }
                else if (vooAtual->getDuracao() == vooProximo->getDuracao())
                {
                    if (vooAtual->getParadas() > vooProximo->getParadas())
                    {
                        deveTrocar = true;
                    }
                    else if (vooAtual->getParadas() == vooProximo->getParadas())
                    {
                        if (vooAtual->getPreco() > vooProximo->getPreco())
                        {
                            deveTrocar = true;
                        }
                    }
                }
            }
            else
            {
                // Caso padrão para tratar entradas inválidas
                std::cout << "Critério de ordenação inválido!" << std::endl;
            }

            // Troca os elementos se necessário
            if (deveTrocar)
            {
                Voos->retiraDaPosicao(i);
                Voos->adicionaNaPosicao(vooProximo, i);
                Voos->retiraDaPosicao(i + 1);
                Voos->adicionaNaPosicao(vooAtual, i + 1);
                trocou = true;
            }
        }
        tamanho--; // Otimização: reduz o tamanho a cada passada
    } while (trocou);

    return Voos;
}

std::string limparString(const std::string &str) {
    std::string resultado = str;
    resultado.erase(std::remove_if(resultado.begin(), resultado.end(), ::isspace), resultado.end());
    return resultado;
}

bool Consulta::avaliarPredicadoSimples(Voo *voo, const std::string &predicado) {
    if (predicado.find("org==") != std::string::npos) {
        std::string org = predicado.substr(5); // Extrai a origem
        org = limparString(org);
        return voo->getOrigem() == org;
    } else if (predicado.find("dst==") != std::string::npos) {
        std::string dst = predicado.substr(5); // Extrai o destino
        dst = limparString(dst);
        return voo->getDestino() == dst;
    } else if (predicado.find("prc<=") != std::string::npos) {
        double prcMax = std::stod(predicado.substr(5)); // Extrai o preço máximo
        return voo->getPreco() <= prcMax;
    } else if (predicado.find("prc>=") != std::string::npos) {
        double prcMin = std::stod(predicado.substr(5)); // Extrai o preço mínimo
        return voo->getPreco() >= prcMin;
    } else if (predicado.find("sea>=") != std::string::npos) {
        int seaMin = std::stoi(predicado.substr(5)); // Extrai o número mínimo de assentos
        return voo->getAssentosDisp() >= seaMin;
    } else if (predicado.find("sea<=") != std::string::npos) {
        int seaMax = std::stoi(predicado.substr(5)); // Extrai o número mínimo de assentos
        return voo->getAssentosDisp() <= seaMax;
    } else if (predicado.find("sea==") != std::string::npos) {
        int sea = std::stoi(predicado.substr(5)); // Extrai o número mínimo de assentos
        return voo->getAssentosDisp() == sea;
    } else if (predicado.find("dep==") != std::string::npos) {
        std::string dep = predicado.substr(5); // Extrai a data-hora de partida
        dep = limparString(dep);
        return voo->getHoraPartida() == dep;
    } else if (predicado.find("arr==") != std::string::npos) {
        std::string arr = predicado.substr(5); // Extrai a data-hora de chegada
        arr = limparString(arr);
        return voo->getHoraChegada() == arr;
    } else if (predicado.find("sto<=") != std::string::npos) {
        int stoMax = std::stoi(predicado.substr(5)); // Extrai o número máximo de paradas
        return voo->getParadas() <= stoMax;
    } else if (predicado.find("sto>=") != std::string::npos) {
        int stoMin = std::stoi(predicado.substr(5)); // Extrai o número mínimo de paradas
        return voo->getParadas() >= stoMin;
    } else if (predicado.find("sto==") != std::string::npos) {
        int sto = std::stoi(predicado.substr(5)); // Extrai o número mínimo de paradas
        return voo->getParadas() == sto;
    } else if (predicado.find("dur<=") != std::string::npos) {
        int durMax = std::stoi(predicado.substr(5)); // Extrai a duração máxima
        return voo->getDuracao() <= durMax;
    } else if (predicado.find("dur>=") != std::string::npos) {
        int durMin = std::stoi(predicado.substr(5)); // Extrai a duração mínima
        return voo->getDuracao() >= durMin;
    }

    std::cout << "Predicado inválido: " << predicado << std::endl;
    return false;
}
