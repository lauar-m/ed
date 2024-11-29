#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "pessoa.hpp"
#include "ordindireta.hpp"
#include "quicksort.hpp"
#include "mergesort.hpp"
#include "heapsort.hpp"

// colocar o trem de marcar o tempo dos algoritmos
// relatorio

// modelo dessa função é de um carregarCsv meu do semestre passado
// função que pega os dados do xcsv
Pessoa *carregarCsv(const std::string &nomearquivo, int &tamanho){
    Pessoa *pessoas = NULL;
    tamanho = 0;
    int capacidade = 0;

    std::ifstream arquivo(nomearquivo);
    if (!arquivo.is_open()){
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        return pessoas;
    }

    std::string linha;

    // ignorar as 5 primeiras linhas
    for (int i = 0; i < 5; i++){
        getline(arquivo, linha);
    }

    // a sexta linha é a quantidade de pessoas
    if (std::getline(arquivo, linha)){
        try{
            capacidade = std::stoi(linha);
        }
        catch (...){
            std::cerr << "Erro na capacidade do arquivo." << std::endl;
            arquivo.close();
            return pessoas;
        }
    }

    // array das pessoas com a capacidade do arquivo
    pessoas = new Pessoa[capacidade];

    // lê as pessoas e seus dados
    while (std::getline(arquivo, linha) && tamanho < capacidade){
        std::istringstream ss(linha);
        Pessoa pessoa;
        std::string campo;

        if (std::getline(ss, campo, ','))
            pessoa.nome = campo;
        if (std::getline(ss, campo, ','))
            pessoa.cpf = campo;
        if (std::getline(ss, campo, ','))
            pessoa.endereco = campo;
        if (std::getline(ss, campo, ','))
            pessoa.outros = campo;

        pessoas[tamanho++] = pessoa;
    }

    arquivo.close();
    return pessoas;
}

// funcao para rodar tods os arquivos de uma so vez
void todosarquivos(const std::string &nomearquivo){
    int tamanho = 0;
    Pessoa *pessoas = carregarCsv(nomearquivo, tamanho);
    int *indices = iniciaindices(tamanho);

    if (pessoas == NULL){
        std::cerr << "Erro ao carregar o arquivo" << std::endl;
        return;
    }

    // Ordenar por nome indiretamente
    quicksortNOME(pessoas, indices, 0, tamanho - 1);
    // mostra as linhas ignoradas do arquivo
    std::cout << "4\nname,s\nid,s\naddress,s\npayload,s" << std::endl;
    // mostra quantas pessoas tem
    std::cout << tamanho << std::endl;
    // mostra as pessoas
    for (int i = 0; i < tamanho; i++){
        int idx = indices[i];
        std::cout << pessoas[idx].nome << ", " << pessoas[idx].cpf << ", " << pessoas[idx].endereco << /*", " << pessoas[idx].outros << */ std::endl;
    }

    // Ordenar por cpf indiretamente
    quicksortCPF(pessoas, indices, 0, tamanho - 1);
    // mostra as linhas ignoradas do arquivo
    std::cout << "4\nname,s\nid,s\naddress,s\npayload,s" << std::endl;
    // mostra quantas pessoas tem
    std::cout << tamanho << std::endl;
    // mostra as pessoas
    for (int i = 0; i < tamanho; i++){
        int idx = indices[i];
        std::cout << pessoas[idx].nome << ", " << pessoas[idx].cpf << ", " << pessoas[idx].endereco << /*", " << pessoas[idx].outros << */ std::endl;
    }

    // Ordenar por endereco indiretamente
    quicksortENDERECO(pessoas, indices, 0, tamanho - 1);
    // mostra as linhas ignoradas do arquivo
    std::cout << "4\nname,s\nid,s\naddress,s\npayload,s" << std::endl;
    // mostra quantas pessoas tem
    std::cout << tamanho << std::endl;
    // mostra as pessoas
    for (int i = 0; i < tamanho; i++){
        int idx = indices[i];
        std::cout << pessoas[idx].nome << ", " << pessoas[idx].cpf << ", " << pessoas[idx].endereco << /*", " << pessoas[idx].outros << */ std::endl;
    }

    mergesort(pessoas, indices, 0, tamanho - 1, 1);
    // mostra as linhas ignoradas do arquivo
    std::cout << "4\nname,s\nid,s\naddress,s\npayload,s" << std::endl;
    // mostra quantas pessoas tem
    std::cout << tamanho << std::endl;
    for (int i = 0; i < tamanho; i++){
        int idx = indices[i];
        std::cout << pessoas[idx].nome << ", " << pessoas[idx].cpf << ", " << pessoas[idx].endereco << std::endl;
    }

    mergesort(pessoas, indices, 0, tamanho - 1, 2);
    // mostra as linhas ignoradas do arquivo
    std::cout << "4\nname,s\nid,s\naddress,s\npayload,s" << std::endl;
    // mostra quantas pessoas tem
    std::cout << tamanho << std::endl;
    for (int i = 0; i < tamanho; i++){
        int idx = indices[i];
        std::cout << pessoas[idx].nome << ", " << pessoas[idx].cpf << ", " << pessoas[idx].endereco << std::endl;
    }

    mergesort(pessoas, indices, 0, tamanho - 1, 3);
    // mostra as linhas ignoradas do arquivo
    std::cout << "4\nname,s\nid,s\naddress,s\npayload,s" << std::endl;
    // mostra quantas pessoas tem
    std::cout << tamanho << std::endl;
    for (int i = 0; i < tamanho; i++){
        int idx = indices[i];
        std::cout << pessoas[idx].nome << ", " << pessoas[idx].cpf << ", " << pessoas[idx].endereco << std::endl;
    }
    // Ordenar por nome indiretamente
    heapsort(pessoas, indices, tamanho, 1);
    // mostra as linhas ignoradas do arquivo
    std::cout << "4\nname,s\nid,s\naddress,s\npayload,s" << std::endl;
    // mostra quantas pessoas tem
    std::cout << tamanho << std::endl;
    for (int i = 0; i < tamanho; i++){
        int idx = indices[i];
        std::cout << pessoas[idx].nome << ", " << pessoas[idx].cpf << ", " << pessoas[idx].endereco << std::endl;
    }
    // Ordenar por cpf indiretamente
    heapsort(pessoas, indices, tamanho, 2);
    // mostra as linhas ignoradas do arquivo
    std::cout << "4\nname,s\nid,s\naddress,s\npayload,s" << std::endl;
    // mostra quantas pessoas tem
    std::cout << tamanho << std::endl;
    for (int i = 0; i < tamanho; i++){
        int idx = indices[i];
        std::cout << pessoas[idx].nome << ", " << pessoas[idx].cpf << ", " << pessoas[idx].endereco << std::endl;
    }
    // Ordenar por endereco indiretamente
    heapsort(pessoas, indices, tamanho, 3);
    // mostra as linhas ignoradas do arquivo
    std::cout << "4\nname,s\nid,s\naddress,s\npayload,s" << std::endl;
    // mostra quantas pessoas tem
    std::cout << tamanho << std::endl;
    for (int i = 0; i < tamanho; i++){
        int idx = indices[i];
        std::cout << pessoas[idx].nome << ", " << pessoas[idx].cpf << ", " << pessoas[idx].endereco << std::endl;
    }

    delete[] pessoas; // libera memoria
    delete[] indices; // libera memoria
}

int main()
{
    std::string nomearquivo[] = {
        //"src/test.xcsv",
        //"src/test2.xcsv"
        "bin/cad.r1000.p1000.xcsv",
        "bin/cad.r1000.p5000.xcsv",
        "bin/cad.r5000.p1000.xcsv",
        "bin/cad.r5000.p5000.xcsv"
    };

    for (const std::string &nomearquivo : nomearquivo){
        todosarquivos(nomearquivo);
    }

    return 0;
}