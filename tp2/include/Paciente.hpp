#ifndef PACIENTE_HPP
#define PACIENTE_HPP
#include <string>
#include <ctime>

struct Paciente {
    int id;  // Identificador do paciente
    int alta;  // Indica se o paciente recebeu alta
    time_t dataAdmissao;  // Data e hora de admissão
    int grauUrgencia;  // Grau de urgência do paciente
    int medidasHospitalares, testesLaboratorio, examesImagem, instrumentosMedicamentos;  // Tipos de procedimentos realizados
    float tempoEspera;  // Tempo de espera do paciente
    float tempoAtendimento;  // Tempo de atendimento do paciente
    int estado;  // Estado do paciente (1 a 14)
    
    time_t dataSaida;  // Data e hora de saída
    // hora de enttrada numa fila   
    time_t horaEntradaFila;
    // hora de saida de uma fila
    time_t horaSaidaFila;

    Paciente();  // Construtor da estrutura Paciente
    void definirPaciente(int _id, int _alta, time_t dataAdmissao,
                         int _grau, int _mh, int _tl, int _ei, int _im);  // Define os dados do paciente
};

#endif
