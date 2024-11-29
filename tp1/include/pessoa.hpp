#ifndef PESSOA_HPP
#define PESSOA_HPP
#include <string>

// Função que armazena os dados do xcsv
struct Pessoa{
    std::string cabeçalho;
    std::string nome;
    std::string cpf;
    std::string endereco;
    std::string outros;
};

#endif