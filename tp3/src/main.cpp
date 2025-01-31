#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "voo.hpp"
#include "consulta.hpp"
#include "index.hpp"
#include "listaEncad.hpp"

// Função para converter data-hora em segundos
int convertToSeconds(const std::string& datetime) {
    struct tm tm = {};
    strptime(datetime.c_str(), "%Y-%m-%dT%H:%M:%S", &tm);
    return mktime(&tm);
}

// Função para dividir uma string em dados
std::string* split(const std::string& linha, char delimiter, int& count) {
    count = 0;
    for (char ch : linha) {
        if (ch == delimiter) count++;
    }
    count++;
    std::string* dados = new std::string[count];
    std::istringstream dadostream(linha);
    std::string token;
    int i = 0;
    while (std::getline(dadostream, token, delimiter)) {
        dados[i++] = token;
    }
    return dados;
}

// Função para carregar os dados do CSV
void carregarCsv(const std::string& nomeArquivo, ListaEncad<Voo>* voos, ListaEncad<Consulta>* consultas) {
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    // Ler a primeira linha (número de voos)
    std::getline(arquivo, linha);
    int numVoos = std::stoi(linha);

    // Ler os voos
    for (int i = 0; i < numVoos; i++) {
        std::getline(arquivo, linha);
        int count;
        std::string* dados = split(linha, ' ', count);
        Voo* voo = new Voo(dados[0], dados[1], std::stod(dados[2]), std::stoi(dados[3]), dados[4], dados[5], std::stoi(dados[6]));
        voos->adiciona(voo);
        delete[] dados;
    }

    // Ler a próxima linha (número de consultas)
    std::getline(arquivo, linha);
    int numConsultas = std::stoi(linha);

    // Ler as consultas
    for (int i = 0; i < numConsultas; i++) {
        std::getline(arquivo, linha);
        int count;
        std::string* dados = split(linha, ' ', count);
        Consulta* consulta = new Consulta(std::stoi(dados[0]), dados[1], dados[2]);
        consultas->adiciona(consulta);
        delete[] dados;
    }
}

// Função para imprimir a saída
void imprimirSaida(ListaEncad<Voo>* voos) {
    for (int i = 0; i < voos->tamanho(); i++) {
        Voo* voo = voos->get(i);
        std::cout << voo->getOrigem() << " "
                  << voo->getDestino() << " "
                  << voo->getPreco() << " "
                  << voo->getAssentosDisp() << " "
                  << voo->getHoraPartida() << " "
                  << voo->getHoraChegada() << " "
                  << voo->getParadas() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.csv>" << std::endl;
        return 1;
    }
    std::string nomeArquivo = argv[1];
    ListaEncad<Voo>* voos = new ListaEncad<Voo>();
    ListaEncad<Consulta>* consultas = new ListaEncad<Consulta>();

    // Carregar os dados do CSV
    carregarCsv(nomeArquivo, voos, consultas);

    Index index;
    for (int i = 0; i < voos->tamanho(); i++) {
        index.addVoo(voos->get(i));
    }

    for (int i = 0; i < consultas->tamanho(); i++) {
        Consulta* consulta = consultas->get(i);

        // Aplicar a filtragem
        ListaEncad<Voo>* voosFiltrados = consulta->evaluate(voos);

        // Verificar se a lista filtrada não está vazia
        if (voosFiltrados->tamanho() == 0) {
            std::cout << "Nenhum voo encontrado para a consulta: "
                      << consulta->getMaxVoos() << " "
                      << consulta->getOrder() << " "
                      << consulta->getExpression() << std::endl;
            delete voosFiltrados;
            continue;
        }

        // Aplicar a ordenação
        ListaEncad<Voo>* voosOrdenados = consulta->sortVoos(voosFiltrados);

        // Verificar se a lista ordenada não está vazia
        if (voosOrdenados->tamanho() == 0) {
            std::cout << "Erro ao ordenar os voos para a consulta: "
                      << consulta->getMaxVoos() << " "
                      << consulta->getOrder() << " "
                      << consulta->getExpression() << std::endl;
            delete voosOrdenados;
            continue;
        }

        // Imprimir a saída
        std::cout << consulta->getMaxVoos() << " "
                  << consulta->getOrder() << " "
                  << consulta->getExpression() << std::endl;
        imprimirSaida(voosOrdenados);

        // Liberar memória
        delete voosFiltrados;
        delete voosOrdenados;
    }

    // Liberar memória
    delete voos;
    delete consultas;

    return 0;
}