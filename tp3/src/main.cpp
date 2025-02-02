#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "voo.hpp"
#include "consulta.hpp"
#include "listaEncad.hpp"
#include "noArvoreB.hpp"
#include "arvoreB.hpp"

// Função para dividir uma string em dados
ListaEncad<std::string> *split(const std::string &linha, char delimiter)
{
    ListaEncad<std::string> *dados = new ListaEncad<std::string>();
    std::istringstream dadostream(linha);
    std::string dado;

    while (std::getline(dadostream, dado, delimiter))
    {
        dados->adiciona(new std::string(dado));
    }
    return dados;
}

// Função para converter string para inteiro
int safe_stoi(const std::string &str)
{
    try
    {
        return std::stoi(str);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Erro ao converter string para inteiro (inválido): " << str << std::endl;
        return -1; // Retorna -1 em caso de erro
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Erro ao converter string para inteiro (fora do intervalo): " << str << std::endl;
        return -1;
    }
}

// Função para carregar os dados do CSV
void carregarCsv(const std::string &nomeArquivo, ListaEncad<Voo> *voos, ListaEncad<Consulta> *consultas)
{
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return;
    }

    std::string linha;

    // Ler a primeira linha (número de voos)
    if (!std::getline(arquivo, linha))
    {
        std::cerr << "Erro ao ler o número de voos." << std::endl;
        return;
    }

    int numVoos = safe_stoi(linha);
    if (numVoos < 0)
        return;

    // Ler os voos
    for (int i = 0; i < numVoos; i++)
    {
        if (!std::getline(arquivo, linha))
        {
            std::cerr << "Erro ao ler a linha do voo " << i + 1 << std::endl;
            return;
        }

        std::istringstream iss(linha);
        std::string org, dst, dep, arr;
        double prc;
        int sea, sto;

        if (!(iss >> org >> dst >> prc >> sea >> dep >> arr >> sto))
        {
            std::cerr << "Erro ao ler os dados do voo na linha " << i + 2 << std::endl;
            continue;
        }

        try
        {
            Voo *voo = new Voo(org, dst, prc, sea, dep, arr, sto);
            voos->adiciona(voo);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Erro ao criar voo: " << e.what() << std::endl;
        }
    }

    // Ler o número de consultas
    if (!std::getline(arquivo, linha))
    {
        std::cerr << "Erro ao ler o número de consultas." << std::endl;
        return;
    }

    int numConsultas = safe_stoi(linha);
    if (numConsultas < 0)
        return;

    // Ler as consultas
    for (int i = 0; i < numConsultas; i++)
    {
        if (!std::getline(arquivo, linha))
        {
            std::cerr << "Erro ao ler a linha da consulta " << i + 1 << std::endl;
            return;
        }

        std::istringstream issConsulta(linha);
        int maxVoos;
        std::string order;
        std::string expression;

        // Ler os dois primeiros campos (maxVoos e order)
        if (!(issConsulta >> maxVoos >> order))
        {
            std::cerr << "Erro ao ler os dados da consulta na linha " << i + 2 << std::endl;
            continue;
        }

        // O restante da linha será a expressão (incluindo espaços)
        std::getline(issConsulta, expression);
        // Remover espaços em branco iniciais da expressão, se houver
        expression.erase(0, expression.find_first_not_of(" \t"));

        try
        {
            Consulta *consulta = new Consulta(maxVoos, order, expression);
            consultas->adicionaFila(consulta);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Erro ao criar consulta: " << e.what() << std::endl;
        }
    }
}

// Função para imprimir a saída
void imprimirSaida(ListaEncad<Voo> *voos, int maxVoos)
{
    for (int i = 0; i < maxVoos; i++)
    {
        Voo *voo = voos->get(i);
        std::cout << voo->getOrigem() << " "
                  << voo->getDestino() << " "
                  << voo->getPreco() << " "
                  << voo->getAssentosDisp() << " "
                  << voo->getHoraPartida() << " "
                  << voo->getHoraChegada() << " "
                  << voo->getParadas() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Uso: " << argv[0] << " <arquivo.csv>" << std::endl;
        return 1;
    }

    std::string nomeArquivo = argv[1];
    ListaEncad<Voo> *voos = new ListaEncad<Voo>(); // Inicializa a lista de voos
    ListaEncad<Consulta> *consultas = new ListaEncad<Consulta>(); // Inicializa a lista de consultas 

    // Carregar os dados do CSV
    carregarCsv(nomeArquivo, voos, consultas);

    for (int i = 0; i < consultas->tamanho(); i++)
    {
        ListaEncad<Voo>* voosDaVez = new ListaEncad<Voo>();
        for (int i = 0; i < voos->tamanho(); i++)
        {
            Voo *voo = new Voo(voos->get(i)->getOrigem(), voos->get(i)->getDestino(), voos->get(i)->getPreco(), voos->get(i)->getAssentosDisp(), voos->get(i)->getHoraPartida(), voos->get(i)->getHoraChegada(), voos->get(i)->getParadas());
            voosDaVez->adiciona(voo);
        }

        Consulta *consulta = consultas->get(i);

        // Aplicar a filtragem
        ListaEncad<Voo> *voosFiltrados = consulta->evaluate(voosDaVez);
        
        // Verificar se a lista filtrada não está vazia
        if (voosFiltrados->tamanho() == 0)
        {
            std::cout << "Nenhum voo encontrado para a consulta: "
                      << consulta->getMaxVoos() << " "
                      << consulta->getOrder() << " "
                      << consulta->getExpression() << std::endl;
            delete voosFiltrados;
            continue;
        }

        // Aplicar a ordenação
        ListaEncad<Voo> *voosOrdenados = consulta->sortVoos(voosFiltrados);

        // Verificar se a lista ordenada não está vazia
        if (voosOrdenados->tamanho() == 0)
        {
            std::cout << "Erro ao ordenar os voos para a consulta: "
                      << consulta->getMaxVoos() << " "
                      << consulta->getOrder() << " "
                      << consulta->getExpression() << std::endl;
            delete voosOrdenados;
            continue;
        }

        // // Imprimir a saída
        std::cout << consulta->getMaxVoos() << " "
                  << consulta->getOrder() << " "
                  << consulta->getExpression() << std::endl;
        imprimirSaida(voosOrdenados, consulta->getMaxVoos());
    }
    // Liberar memória
    delete voos;
    delete consultas;

    return 0;
}
